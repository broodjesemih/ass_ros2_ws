#include <pqxx/pqxx>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <memory>

struct StudentRecord
{
    std::string student_name;
    std::string course;
    int number_of_exams;
    double final_result;
    long timestamp;
};

namespace Database
{

    std::unique_ptr<pqxx::connection> db = nullptr;

    bool open()
    {
        try 
        {
            // Connect to PostgreSQL database with fallback options
            std::string connection_string;
            
            // Try different connection methods in order of preference
            std::vector<std::string> connection_attempts = {
                "postgresql://postgres:password@localhost:5432/student_grades",  // TCP with explicit port
                "host=localhost port=5432 dbname=student_grades user=postgres password=password",  // libpq format
                "host=/var/run/postgresql dbname=student_grades user=postgres",  // Unix socket with user
                "host=/tmp dbname=student_grades user=postgres",  // Alternative socket location
                "dbname=student_grades",  // Simple local connection (current user)
                "postgresql:///student_grades"  // URI format with current user
            };
            
            bool connected = false;
            for (size_t i = 0; i < connection_attempts.size(); i++) {
                try {
                    connection_string = connection_attempts[i];
                    std::cout << "[Database] Attempt " << (i+1) << "/" << connection_attempts.size() 
                              << ": " << connection_string << std::endl;
                    
                    db = std::make_unique<pqxx::connection>(connection_string);
                    
                    if (db->is_open()) {
                        std::cout << "[Database] ✅ Connected successfully using method " << (i+1) << "!" << std::endl;
                        connected = true;
                        break;
                    }
                } catch (const std::exception& e) {
                    std::cout << "[Database] ❌ Method " << (i+1) << " failed: " << e.what() << std::endl;
                    db = nullptr;
                    
                    // Add specific hints for common errors
                    std::string error_msg = e.what();
                    if (error_msg.find("No such file or directory") != std::string::npos) {
                        std::cout << "[Database] 💡 Hint: PostgreSQL socket file not found. Is PostgreSQL running?" << std::endl;
                    } else if (error_msg.find("Connection refused") != std::string::npos) {
                        std::cout << "[Database] 💡 Hint: PostgreSQL server not accepting connections. Check if it's running on the correct port." << std::endl;
                    } else if (error_msg.find("authentication failed") != std::string::npos) {
                        std::cout << "[Database] 💡 Hint: Authentication failed. Check username/password or pg_hba.conf." << std::endl;
                    }
                }
            }
            
            if (!connected) {
                std::cerr << "[Database] ❌ All connection attempts failed!" << std::endl;
                std::cerr << "[Database] 🔧 Troubleshooting steps:" << std::endl;
                std::cerr << "[Database]    1. Check if PostgreSQL is running: sudo systemctl status postgresql" << std::endl;
                std::cerr << "[Database]    2. Start PostgreSQL: sudo systemctl start postgresql" << std::endl;
                std::cerr << "[Database]    3. Run setup script: ./setup_postgresql.sh" << std::endl;
                std::cerr << "[Database]    4. Check debug info: ./debug_postgres.sh" << std::endl;
                return false;
            }

            pqxx::work txn(*db);

            const char *createSQL = R"(
                CREATE TABLE IF NOT EXISTS student_results (
                    id SERIAL PRIMARY KEY,
                    student_name VARCHAR(255) NOT NULL,
                    course VARCHAR(255) NOT NULL,
                    number_of_exams INTEGER,
                    final_result REAL,
                    timestamp BIGINT
                );
            )";

            txn.exec(createSQL);

            // Check if table is empty
            pqxx::result count_result = txn.exec("SELECT COUNT(*) FROM student_results;");
            int count = count_result[0][0].as<int>();
            
            if (count == 0)
            {
                std::cout << "[Database] Table empty, inserting initial values...\n";
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

    void close()
    {
        if (db && db->is_open())
        {
            db->close();
        }
        db = nullptr;
    }
bool insert(const StudentRecord &record)
{
    if (!db || !db->is_open()) return false;

    try 
    {
        pqxx::work txn(*db);

        // First check if there is an unfinished row (final_result IS NULL)
        pqxx::result select_result = txn.exec_params(
            "SELECT id FROM student_results WHERE student_name = $1 AND course = $2 AND final_result IS NULL LIMIT 1;",
            record.student_name, record.course
        );

        if (!select_result.empty()) 
        {
            // Update unfinished row
            int rowId = select_result[0][0].as<int>();
            
            if (record.final_result == 0.0) 
            {
                txn.exec_params(
                    "UPDATE student_results SET number_of_exams = $1, final_result = NULL, timestamp = $2 WHERE id = $3;",
                    record.number_of_exams, record.timestamp, rowId
                );
            } 
            else 
            {
                txn.exec_params(
                    "UPDATE student_results SET number_of_exams = $1, final_result = $2, timestamp = $3 WHERE id = $4;",
                    record.number_of_exams, record.final_result, record.timestamp, rowId
                );
            }
        } 
        else 
        {
            // Insert new row
            if (record.final_result == 0.0) 
            {
                txn.exec_params(
                    "INSERT INTO student_results (student_name, course, number_of_exams, final_result, timestamp) VALUES ($1, $2, $3, NULL, $4);",
                    record.student_name, record.course, record.number_of_exams, record.timestamp
                );
            } 
            else 
            {
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


    std::vector<StudentRecord> getAll()
    {
        std::vector<StudentRecord> results;
        if (!db || !db->is_open())
            return results;

        try 
        {
            pqxx::nontransaction txn(*db);
            
            pqxx::result select_result = txn.exec(
                "SELECT student_name, course, number_of_exams, final_result, timestamp FROM student_results;"
            );

            for (const auto &row : select_result)
            {
                StudentRecord record;
                record.student_name = row[0].as<std::string>();
                record.course = row[1].as<std::string>();
                record.number_of_exams = row[2].as<int>();
                record.final_result = row[3].is_null() ? 0.0 : row[3].as<double>();
                record.timestamp = row[4].as<long>();
                results.push_back(record);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Database select error: " << e.what() << std::endl;
        }

        return results;
    }
    std::vector<StudentRecord> getWithoutFinalResult()
    {
        std::vector<StudentRecord> results;
        if (!db || !db->is_open())
            return results;

        try 
        {
            pqxx::nontransaction txn(*db);
            
            pqxx::result select_result = txn.exec(
                "SELECT student_name, course, number_of_exams, final_result, timestamp FROM student_results WHERE final_result IS NULL;"
            );

            for (const auto &row : select_result)
            {
                StudentRecord record;
                record.student_name = row[0].as<std::string>();
                record.course = row[1].as<std::string>();
                record.number_of_exams = row[2].as<int>();
                record.final_result = 0.0; // NULL values
                record.timestamp = row[4].as<long>();
                results.push_back(record);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Database select error: " << e.what() << std::endl;
        }

        return results;
    }

} // namespace Database
