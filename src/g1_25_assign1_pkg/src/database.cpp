/* 
 * POSTGRESQL DATABASE ABSTRACTION LAYER - ROS2 Grade Calculator System
 *
 * PURPOSE: Comprehensive database connectivity and operations for student grade management
 * ROLE: Central data persistence layer supporting all ROS2 grade calculation nodes
 *
 * FEATURES:
 * - Multi-method connection fallback system (15 different connection attempts)
 * - Intelligent upsert operations for gradual grade accumulation
 * - Thread-safe CRUD operations with atomic transactions
 * - Automatic schema initialization and data seeding
 * - Robust error handling with graceful degradation
 *
 * DATABASE DESIGN:
 * - PostgreSQL backend with libpqxx C++ client library
 * - Flexible schema supporting NULL final_result during exam accumulation
 * - Composite key support for student/course combinations
 * - Timestamp tracking for audit trails and temporal queries
 *
 * INTEGRATION: Used by all ROS2 nodes for persistent grade storage and retrieval
 *
 * Coded by: Semih, Nout, Tycho
 * Last modified: October 9, 2025
 */

#include <pqxx/pqxx>         // PostgreSQL C++ client library for database operations
#include <string>            // String manipulation for connection strings and data
#include <vector>            // Container for multiple records and connection attempts
#include <iostream>          // Console output for debugging and status messages
#include <filesystem>        // File system operations (unused but available)
#include <memory>            // Smart pointers for safe memory management

// Data structure representing a student's grade record in the database
// Maps directly to the PostgreSQL table schema for easy serialization/deserialization
struct StudentRecord
{
    std::string student_name;   // Student identifier (e.g., "Wessel Tip")
    std::string course;         // Course name (e.g., "ROS2", "Programmeren")
    int number_of_exams;        // Count of exams taken for this course
    double final_result;        // Calculated final grade (NULL during accumulation, 0.0 represents NULL)
    long timestamp;             // Unix timestamp of last record update
};

// Database namespace containing all PostgreSQL operations
// Provides a singleton-style interface with global connection management
// Thread-safe operations are handled by the calling code (mutex in nodes)
namespace Database
{
    // Global database connection handle using RAII smart pointer
    // Automatically manages connection lifecycle and prevents memory leaks
    std::unique_ptr<pqxx::connection> db = nullptr;

    // Primary connection establishment function with comprehensive fallback system
    // Attempts multiple connection methods to ensure maximum compatibility across environments
    // Returns: true if connection successful, false otherwise
    bool open()
    {
        try 
        {
            // Connection string will be set by successful attempt
            std::string connection_string;
            
            // Auto-detect current system user for socket-based connections
            // Fallback to "postgres" if USER environment variable not set
            std::string current_user = getenv("USER") ? getenv("USER") : "postgres";
            
            // Comprehensive connection fallback system - attempts 10 different methods
            // Ordered by preference: most common/reliable methods first, fallbacks last
            // Covers TCP connections, Unix sockets, different ports, and authentication methods
            std::vector<std::string> connection_attempts = {
                // PRIMARY: TCP connections with explicit authentication (most reliable)
                "host=localhost port=5432 dbname=student_grades user=postgres password=password sslmode=disable",  // Standard PostgreSQL port with password
                "host=localhost port=5433 dbname=student_grades user=postgres password=password sslmode=disable",  // Alternative port (common in multi-instance setups)
                
                // SECONDARY: Socket connections with current system user (common in development)
                "dbname=student_grades user=" + current_user,                                    // Auto-detect port with current user
                "host=/var/run/postgresql dbname=student_grades user=" + current_user,          // Debian/Ubuntu socket location
                "host=/tmp dbname=student_grades user=" + current_user,                         // Alternative socket location  
                "host=/run/postgresql dbname=student_grades user=" + current_user,              // Arch Linux/Fedora socket location
                
                // TERTIARY: URI format connections with current user
                "postgresql://" + current_user + "@localhost:5432/student_grades",              // URI format (port 5432)
                "postgresql://" + current_user + "@localhost:5433/student_grades",              // URI format (port 5433)
                
                // QUATERNARY: Socket connections with postgres system user
                "host=/var/run/postgresql dbname=student_grades user=postgres",                 // Debian/Ubuntu with postgres user
                "host=/tmp dbname=student_grades user=postgres",                                // Alternative socket with postgres user
                "host=/run/postgresql dbname=student_grades user=postgres",                     // Arch/Fedora with postgres user
                
                // FALLBACK: Simple connections (rely on system defaults)
                "postgresql://postgres:password@localhost:5432/student_grades?sslmode=disable", // TCP URI with explicit auth (port 5432)
                "postgresql://postgres:password@localhost:5433/student_grades?sslmode=disable", // TCP URI with explicit auth (port 5433)
                "dbname=student_grades",                                                         // Minimal connection (uses pg_service.conf or environment)
                "postgresql:///student_grades"                                                   // Minimal URI (auto-detect all parameters)
            };
            
            // Connection attempt loop with intelligent error handling and user feedback
            bool connected = false;
            std::cout << "[Database] Searching for PostgreSQL connection..." << std::endl;
            
            // Iterate through all connection methods until one succeeds
            for (size_t i = 0; i < connection_attempts.size(); i++) {
                try {
                    connection_string = connection_attempts[i];
                    
                    // Create new connection using current attempt string
                    db = std::make_unique<pqxx::connection>(connection_string);
                    
                    // Verify connection is actually established
                    if (db->is_open()) {
                        std::cout << "[Database] Connected successfully!" << std::endl;
                        std::cout << "[Database] Using: " << connection_string << std::endl;
                        connected = true;
                        break;  // Exit loop on first successful connection
                    }
                } catch (const std::exception& e) {
                    // Reset connection pointer to prevent dangling references
                    db = nullptr;
                    
                    // Provide informative error messages for primary connection methods
                    // Avoid spam by only showing errors for first few critical attempts
                    if (i < 3) {
                        std::string error_msg = e.what();
                        if (error_msg.find("Connection refused") != std::string::npos) {
                            std::cout << "[Database]  Port " << (i == 0 ? "5432" : "5433") << " not available, trying alternatives..." << std::endl;
                        } else if (error_msg.find("authentication failed") != std::string::npos) {
                            std::cout << "[Database]  Password auth failed on port " << (i == 0 ? "5432" : "5433") << ", trying socket connections..." << std::endl;
                        }
                    }
                    // Continue to next connection method
                }
            }
            
            // Handle complete connection failure with user-friendly error messages
            if (!connected) {
                std::cerr << "[Database]  Could not establish database connection!" << std::endl;
                std::cerr << "[Database]  Quick fixes:" << std::endl;
                std::cerr << "[Database]    • Check PostgreSQL: sudo systemctl status postgresql" << std::endl;
                std::cerr << "[Database]    • Start PostgreSQL: sudo systemctl start postgresql" << std::endl;
                std::cerr << "[Database]    • Run auto-setup: ./complete_setup.sh" << std::endl;
                
                // Ensure db pointer is null to prevent segmentation faults in subsequent operations
                db = nullptr;
                return false;
            }

            // DATABASE SCHEMA INITIALIZATION
            // Create transaction for atomic schema setup (rollback on failure)
            pqxx::work txn(*db);

            // Create the main student_results table if it doesn't exist
            // Schema designed for flexible grade tracking with nullable final_result for gradual accumulation
            const char *createSQL = R"(
                CREATE TABLE IF NOT EXISTS student_results (
                    id SERIAL PRIMARY KEY,                    -- Auto-incrementing unique identifier
                    student_name VARCHAR(255) NOT NULL,      -- Student identifier (supports full names)
                    course VARCHAR(255) NOT NULL,            -- Course name identifier
                    number_of_exams INTEGER,                 -- Count of exams taken (for progress tracking)
                    final_result REAL,                       -- Final calculated grade (NULL during accumulation)
                    timestamp BIGINT                         -- Unix timestamp for audit trails
                );
            )";

            txn.exec(createSQL);

            // INITIAL DATA SEEDING
            // Check if database is empty and populate with TI Minor student roster
            pqxx::result count_result = txn.exec("SELECT COUNT(*) FROM student_results;");
            int count = count_result[0][0].as<int>();
            
            // Populate database with initial student/course combinations if empty
            if (count == 0)
            {
                std::cout << "[Database] Table empty, inserting initial TI Minor student roster...\n";
                // Insert comprehensive student/course matrix for demonstration and testing
                // Each student gets enrolled in all 6 courses with initial state (0 exams, no final result)
                const char *insertSQL = R"(
                    INSERT INTO student_results (student_name, course, number_of_exams, final_result, timestamp)
                    VALUES
                        ('Semih Karakoc', 'Integreren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Semih Karakoc', 'Differentieren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Semih Karakoc', 'ROS2', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Semih Karakoc', 'Natuurkunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Semih Karakoc', 'Scheikunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Semih Karakoc', 'Programmeren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tilmann Koster', 'Integreren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tilmann Koster', 'Differentieren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tilmann Koster', 'ROS2', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tilmann Koster', 'Natuurkunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tilmann Koster', 'Scheikunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tilmann Koster', 'Programmeren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Wessel Tip', 'Integreren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Wessel Tip', 'Differentieren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Wessel Tip', 'ROS2', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Wessel Tip', 'Natuurkunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Wessel Tip', 'Scheikunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Wessel Tip', 'Programmeren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Vincent Winter', 'Integreren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Vincent Winter', 'Differentieren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Vincent Winter', 'ROS2', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Vincent Winter', 'Natuurkunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Vincent Winter', 'Scheikunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Vincent Winter', 'Programmeren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tycho Mallee', 'Integreren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tycho Mallee', 'Differentieren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tycho Mallee', 'ROS2', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tycho Mallee', 'Natuurkunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tycho Mallee', 'Scheikunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Tycho Mallee', 'Programmeren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Nout Mulder', 'Integreren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Nout Mulder', 'Differentieren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Nout Mulder', 'ROS2', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Nout Mulder', 'Natuurkunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Nout Mulder', 'Scheikunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Nout Mulder', 'Programmeren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Burhan Topaloglu', 'Integreren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Burhan Topaloglu', 'Differentieren', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Burhan Topaloglu', 'ROS2', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Burhan Topaloglu', 'Natuurkunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Burhan Topaloglu', 'Scheikunde', 0, NULL, EXTRACT(EPOCH FROM NOW())),
                        ('Burhan Topaloglu', 'Programmeren', 0, NULL, EXTRACT(EPOCH FROM NOW()));
                )";
                txn.exec(insertSQL);
            }
            
            txn.commit();
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Database connection error: " << e.what() << std::endl;
            db = nullptr;
            return false;
        }
    }

    // Clean connection closure with safety checks
    // Ensures proper resource cleanup and prevents connection leaks
    void close()
    {
        // Check connection exists and is open before attempting to close
        if (db && db->is_open())
        {
            db->close();
        }
        // Reset pointer to null for subsequent safety checks
        db = nullptr;
    }

    // CORE DATABASE OPERATION: Insert or Update Student Record
    // Implements sophisticated upsert logic for grade accumulation and finalization
    // Handles both gradual score accumulation (NULL final_result) and final grade storage
    bool insert(const StudentRecord &record)
    {
        // Pre-condition check: ensure valid database connection exists
        if (!db || !db->is_open()) return false;

        try 
        {
            // Create transaction for atomic operation (all-or-nothing)
            pqxx::work txn(*db);

        // PHASE 1: Check for existing incomplete record (gradual score accumulation)
        // Look for existing student/course combination that hasn't been finalized yet
        pqxx::result select_result = txn.exec_params(
            "SELECT id FROM student_results WHERE student_name = $1 AND course = $2 AND final_result IS NULL LIMIT 1;",
            record.student_name, record.course
        );

        if (!select_result.empty()) 
        {
            // CASE A: Update existing incomplete record (exam accumulation or finalization)
            int rowId = select_result[0][0].as<int>();
            
            if (record.final_result == 0.0) 
            {
                // Sub-case A1: Still accumulating exams (update exam count, keep final_result NULL)
                txn.exec_params(
                    "UPDATE student_results SET number_of_exams = $1, final_result = NULL, timestamp = $2 WHERE id = $3;",
                    record.number_of_exams, record.timestamp, rowId
                );
            } 
            else 
            {
                // Sub-case A2: Finalize record (set final grade, complete the record)
                txn.exec_params(
                    "UPDATE student_results SET number_of_exams = $1, final_result = $2, timestamp = $3 WHERE id = $4;",
                    record.number_of_exams, record.final_result, record.timestamp, rowId
                );
            }
        } 
        else 
        {
            // CASE B: Insert new record (no existing incomplete record found)
            if (record.final_result == 0.0) 
            {
                // Sub-case B1: New incomplete record (start exam accumulation)
                txn.exec_params(
                    "INSERT INTO student_results (student_name, course, number_of_exams, final_result, timestamp) VALUES ($1, $2, $3, NULL, $4);",
                    record.student_name, record.course, record.number_of_exams, record.timestamp
                );
            } 
            else 
            {
                // Sub-case B2: New complete record (direct final grade insertion, e.g., retakes)
                txn.exec_params(
                    "INSERT INTO student_results (student_name, course, number_of_exams, final_result, timestamp) VALUES ($1, $2, $3, $4, $5);",
                    record.student_name, record.course, record.number_of_exams, record.final_result, record.timestamp
                );
            }
        }

        txn.commit();
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Database insert/update error: " << e.what() << std::endl;
        return false;
    }
}


    /**
     * CRUD OPERATION: Retrieve all student records
     * 
     * PURPOSE: Fetch complete dataset for reporting, analysis, and administrative overview
     * USE CASES: Grade reports, student performance analysis, administrative dashboards
     * 
     * RETURN FORMAT: Vector of StudentRecord structs with all database entries
     * PERFORMANCE: Uses non-transactional read for optimal SELECT performance
     */
    std::vector<StudentRecord> getAll()
    {
        // Initialize empty result vector for safe return in all cases
        std::vector<StudentRecord> results;
        
        // CONNECTION SAFETY: Verify database connection before proceeding
        if (!db || !db->is_open())
            return results; // Return empty vector if no valid connection

        try 
        {
            // Use non-transactional read for better SELECT performance
            // No need for transaction overhead since we're only reading data
            pqxx::nontransaction txn(*db);
            
            // QUERY: Select all records without filtering
            // Returns complete dataset ordered by natural database order
            pqxx::result select_result = txn.exec(
                "SELECT student_name, course, number_of_exams, final_result, timestamp FROM student_results;"
            );

            // RESULT PROCESSING: Convert PostgreSQL result set to C++ objects
            for (const auto &row : select_result)
            {
                // Create new StudentRecord for each database row
                StudentRecord record;
                // MAP DATABASE COLUMNS TO STRUCT FIELDS
                record.student_name = row[0].as<std::string>();        // Column 1: Student identifier
                record.course = row[1].as<std::string>();              // Column 2: Course name
                record.number_of_exams = row[2].as<int>();             // Column 3: Exam count (for tracking progress)
                // HANDLE NULL VALUES: Convert SQL NULL to 0.0 for incomplete records
                record.final_result = row[3].is_null() ? 0.0 : row[3].as<double>(); // Column 4: Final grade or 0.0
                record.timestamp = row[4].as<long>();                  // Column 5: Last update time
                
                // Add populated record to results vector
                results.push_back(record);
            }
        }
        catch (const std::exception &e)
        {
            // ERROR HANDLING: Log database errors but continue execution
            // Returns partial results if query partially succeeded
            std::cerr << "Database select error: " << e.what() << std::endl;
        }

        // Return complete result set (empty if connection failed or query error)
        return results;
    }

    /**
     * CRUD OPERATION: Retrieve incomplete student records (for exam scheduling)
     * 
     * PURPOSE: Find students who need additional exams or final grade determination
     * USE CASES: Exam scheduling, progress tracking, pending grade notifications
     * 
     * FILTER CRITERIA: WHERE final_result IS NULL (incomplete records only)
     * BUSINESS LOGIC: Records with NULL final_result need further processing
     */
    std::vector<StudentRecord> getWithoutFinalResult()
    {
        // Initialize empty result vector for safe return in all cases
        std::vector<StudentRecord> results;
        
        // CONNECTION SAFETY: Verify database connection before proceeding
        if (!db || !db->is_open())
            return results; // Return empty vector if no valid connection

        try 
        {
            // Use non-transactional read for optimal SELECT performance
            pqxx::nontransaction txn(*db);
            
            // FILTERED QUERY: Select only incomplete records (NULL final_result)
            // This finds students who are still accumulating exam scores
            // Used by scheduler nodes to determine who needs more exams
            pqxx::result select_result = txn.exec(
                "SELECT student_name, course, number_of_exams, final_result, timestamp FROM student_results WHERE final_result IS NULL;"
            );

            // RESULT PROCESSING: Convert filtered PostgreSQL results to C++ objects
            for (const auto &row : select_result)
            {
                // Create new StudentRecord for each incomplete database row
                StudentRecord record;
                // MAP DATABASE COLUMNS TO STRUCT FIELDS (incomplete records only)
                record.student_name = row[0].as<std::string>();        // Student requiring more exams
                record.course = row[1].as<std::string>();              // Course needing completion
                record.number_of_exams = row[2].as<int>();             // Current exam count (progress indicator)
                record.final_result = 0.0;                            // Hardcode 0.0 since final_result IS NULL
                record.timestamp = row[4].as<long>();                  // Last activity timestamp
                
                // Add incomplete record to results for further processing
                results.push_back(record);
            }
        }
        catch (const std::exception &e)
        {
            // ERROR HANDLING: Log database errors but continue execution
            // Returns partial results if query partially succeeded
            std::cerr << "Database select error: " << e.what() << std::endl;
        }

        // Return filtered result set (incomplete records only)
        return results;
    }

} // namespace Database
// END OF FILE: Complete PostgreSQL abstraction layer for ROS2 grade calculator system
