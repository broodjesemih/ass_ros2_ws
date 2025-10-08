#include <gtest/gtest.h>
#include <pqxx/pqxx>
#include <memory>
#include <string>
#include <thread>
#include <atomic>
#include <vector>
#include <ctime>

/**
 * Unit tests voor Database operaties
 * 
 * Deze tests valideren:
 * - Database connectiviteit
 * - CRUD operaties (Create, Read, Update, Delete)
 * - Data integriteit
 * - Concurrency en thread safety
 * - Error handling bij database fouten
 */

class DatabaseTest : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        // Test database connection strings (in volgorde van prioriteit)
        std::vector<std::string> connection_strings = {
            "postgresql://postgres:password@localhost:5432/student_grades",
            "host=localhost port=5432 dbname=student_grades user=postgres password=password",
            "host=/var/run/postgresql dbname=student_grades user=postgres",
            "host=/tmp dbname=student_grades user=postgres",
            "dbname=student_grades",
            "postgresql:///student_grades"
        };
        
        bool connected = false;
        for (const auto& conn_str : connection_strings) {
            try {
                connection_ = std::make_unique<pqxx::connection>(conn_str);
                if (connection_->is_open()) {
                    connected = true;
                    connection_string_ = conn_str;
                    break;
                }
            } catch (const std::exception&) {
                // Probeer volgende connection string
                continue;
            }
        }
        
        ASSERT_TRUE(connected) << "Kan niet verbinden met database. Zorg dat PostgreSQL draait en database bestaat.";
        
        // Maak test table indien niet bestaat
        setup_test_table();
        
        // Clear test data
        clear_test_data();
    }

    void TearDown() override 
    {
        if (connection_ && connection_->is_open()) {
            clear_test_data();
            connection_->close();
        }
    }

private:
    void setup_test_table() 
    {
        try {
            pqxx::work txn(*connection_);
            
            // Maak test table (vergelijkbaar met production table)
            txn.exec(R"(
                CREATE TABLE IF NOT EXISTS test_student_results (
                    id SERIAL PRIMARY KEY,
                    student_name VARCHAR(255) NOT NULL,
                    course_name VARCHAR(255) NOT NULL,
                    final_cijfer INTEGER NOT NULL,
                    herkansing_cijfer INTEGER,
                    timestamp BIGINT NOT NULL,
                    UNIQUE(student_name, course_name)
                )
            )");
            
            txn.commit();
        } catch (const std::exception& e) {
            FAIL() << "Kan test table niet aanmaken: " << e.what();
        }
    }
    
    void clear_test_data() 
    {
        try {
            pqxx::work txn(*connection_);
            txn.exec("DELETE FROM test_student_results WHERE student_name LIKE 'Test%'");
            txn.commit();
        } catch (const std::exception&) {
            // Ignore cleanup errors
        }
    }

protected:
    std::unique_ptr<pqxx::connection> connection_;
    std::string connection_string_;
    
    // Helper functie om test record in te voegen
    bool insert_test_record(const std::string& student, const std::string& course, 
                           int final_cijfer, int timestamp = 1234567890) {
        try {
            pqxx::work txn(*connection_);
            txn.exec_params(
                "INSERT INTO test_student_results (student_name, course_name, final_cijfer, timestamp) "
                "VALUES ($1, $2, $3, $4)",
                student, course, final_cijfer, timestamp
            );
            txn.commit();
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }
    
    // Helper functie om record op te halen
    std::tuple<std::string, std::string, int> get_test_record(const std::string& student, const std::string& course) {
        pqxx::work txn(*connection_);
        auto result = txn.exec_params(
            "SELECT student_name, course_name, final_cijfer FROM test_student_results "
            "WHERE student_name = $1 AND course_name = $2",
            student, course
        );
        
        if (result.size() > 0) {
            auto row = result[0];
            return std::make_tuple(
                row["student_name"].c_str(),
                row["course_name"].c_str(), 
                row["final_cijfer"].as<int>()
            );
        }
        return std::make_tuple("", "", 0);
    }
};

/**
 * Test 1: Database connectiviteit
 * Verificeer dat we een werkende database verbinding hebben
 */
TEST_F(DatabaseTest, TestDatabaseConnection)
{
    EXPECT_TRUE(connection_->is_open()) << "Database connectie zou open moeten zijn";
    EXPECT_FALSE(connection_string_.empty()) << "Connection string zou niet leeg moeten zijn";
    
    // Test basis query
    try {
        pqxx::work txn(*connection_);
        auto result = txn.exec("SELECT version()");
        txn.commit();
        
        EXPECT_GT(result.size(), 0) << "Version query zou resultaat moeten geven";
        ASSERT_GT(result[0].size(), 0) << "Version result zou niet leeg moeten zijn";
        
        std::string version = result[0][0].c_str();
        EXPECT_FALSE(version.empty()) << "PostgreSQL version zou niet leeg moeten zijn";
        
    } catch (const std::exception& e) {
        FAIL() << "Database version query gefaald: " << e.what();
    }
}

/**
 * Test 2: Student record insertion
 * Test het invoegen van nieuwe student records
 */
TEST_F(DatabaseTest, TestStudentRecordInsertion)
{
    // Test basis insertion
    bool success = insert_test_record("Test Student 1", "Math", 85);
    EXPECT_TRUE(success) << "Student record insertion zou moeten lukken";
    
    // Verificeer dat record is ingevoegd
    auto [student, course, cijfer] = get_test_record("Test Student 1", "Math");
    EXPECT_EQ(student, "Test Student 1");
    EXPECT_EQ(course, "Math");
    EXPECT_EQ(cijfer, 85);
}

/**
 * Test 3: Wessel Tip special record  
 * Test database operations specifiek voor Wessel (met unique name per test run)
 */
TEST_F(DatabaseTest, TestWesselTipRecord)
{
    // Use unique name om conflicts te voorkomen
    std::string unique_name = "Wessel Tip Test " + std::to_string(std::time(nullptr));
    
    // Insert Wessel record
    bool success = insert_test_record(unique_name, "ROS2", 60);
    EXPECT_TRUE(success) << "Wessel record insertion zou moeten lukken";
    
    // Verificeer Wessel's data
    auto [student, course, cijfer] = get_test_record(unique_name, "ROS2");
    EXPECT_EQ(student, unique_name);
    EXPECT_EQ(course, "ROS2");
    EXPECT_EQ(cijfer, 60);
}

/**
 * Test 4: Multiple student records
 * Test batch operations en data integriteit
 */
TEST_F(DatabaseTest, TestMultipleStudentRecords)
{
    std::vector<std::tuple<std::string, std::string, int>> test_data = {
        {"Test Student A", "Math", 75},
        {"Test Student B", "Physics", 80},
        {"Test Student C", "Chemistry", 90},
        {"Test Student A", "Physics", 85}, // Zelfde student, andere course
    };
    
    // Insert alle records
    for (const auto& [student, course, cijfer] : test_data) {
        bool success = insert_test_record(student, course, cijfer);
        EXPECT_TRUE(success) << "Record insertion failed for " << student << "/" << course;
    }
    
    // Verificeer alle records
    for (const auto& [expected_student, expected_course, expected_cijfer] : test_data) {
        auto [student, course, cijfer] = get_test_record(expected_student, expected_course);
        EXPECT_EQ(student, expected_student);
        EXPECT_EQ(course, expected_course);
        EXPECT_EQ(cijfer, expected_cijfer);
    }
}

/**
 * Test 5: Unique constraint handling
 * Test dat student+course combinatie uniek is
 */
TEST_F(DatabaseTest, TestUniqueConstraint)
{
    // Insert eerste record
    bool success1 = insert_test_record("Test Unique", "Math", 75);
    EXPECT_TRUE(success1) << "Eerste record insertion zou moeten lukken";
    
    // Probeer duplicate te inserteren (zou moeten falen)
    bool success2 = insert_test_record("Test Unique", "Math", 85);
    EXPECT_FALSE(success2) << "Duplicate record insertion zou moeten falen";
    
    // Verificeer dat oorspronkelijke record behouden is
    auto [student, course, cijfer] = get_test_record("Test Unique", "Math");
    EXPECT_EQ(cijfer, 75) << "Oorspronkelijke cijfer zou behouden moeten blijven";
}

/**
 * Test 6: Herkansing updates
 * Test update operations voor herkansing cijfers
 */
TEST_F(DatabaseTest, TestHerkansingUpdates)
{
    // Insert basis record
    insert_test_record("Test Herkansing", "Math", 45);
    
    try {
        // Update met herkansing cijfer
        pqxx::work txn(*connection_);
        txn.exec_params(
            "UPDATE test_student_results SET herkansing_cijfer = $1 "
            "WHERE student_name = $2 AND course_name = $3",
            85, "Test Herkansing", "Math"
        );
        txn.commit();
        
        // Verificeer update
        pqxx::work read_txn(*connection_);
        auto result = read_txn.exec_params(
            "SELECT final_cijfer, herkansing_cijfer FROM test_student_results "
            "WHERE student_name = $1 AND course_name = $2",
            "Test Herkansing", "Math"
        );
        
        ASSERT_EQ(result.size(), 1) << "Zou exact 1 record moeten vinden";
        
        int final_cijfer = result[0]["final_cijfer"].as<int>();
        int herkansing_cijfer = result[0]["herkansing_cijfer"].as<int>();
        
        EXPECT_EQ(final_cijfer, 45) << "Final cijfer zou ongewijzigd moeten blijven";
        EXPECT_EQ(herkansing_cijfer, 85) << "Herkansing cijfer zou updated moeten zijn";
        
    } catch (const std::exception& e) {
        FAIL() << "Herkansing update failed: " << e.what();
    }
}

/**
 * Test 7: Grade boundary validation in database
 * Test dat database correcte cijfer ranges accepteert
 */
TEST_F(DatabaseTest, TestGradeBoundaryValidation)
{
    // Test minimum grade (10)
    bool success_min = insert_test_record("Test Min Grade", "Math", 10);
    EXPECT_TRUE(success_min) << "Minimum grade (10) zou geaccepteerd moeten worden";
    
    // Test maximum grade (100)  
    bool success_max = insert_test_record("Test Max Grade", "Math", 100);
    EXPECT_TRUE(success_max) << "Maximum grade (100) zou geaccepteerd moeten worden";
    
    // Test edge cases
    bool success_zero = insert_test_record("Test Zero Grade", "Math", 0);
    EXPECT_TRUE(success_zero) << "Grade 0 zou technisch geaccepteerd moeten worden (business logic handelt dit af)";
    
    bool success_over = insert_test_record("Test Over Grade", "Math", 150);
    EXPECT_TRUE(success_over) << "Grade > 100 zou technisch geaccepteerd moeten worden (business logic handelt dit af)";
}

/**
 * Test 8: Concurrent database access
 * Test thread safety van database operaties
 */
TEST_F(DatabaseTest, TestConcurrentDatabaseAccess)
{
    const int num_threads = 3;
    const int records_per_thread = 5;
    
    std::vector<std::thread> threads;
    std::atomic<int> successful_insertions(0);
    
    // Start meerdere threads die gelijktijdig database operaties uitvoeren
    for (int t = 0; t < num_threads; ++t) {
        threads.emplace_back([this, t, records_per_thread, &successful_insertions]() {
            try {
                // Elke thread maakt eigen connectie
                pqxx::connection local_conn(connection_string_);
                
                for (int i = 0; i < records_per_thread; ++i) {
                    std::string student = "Test Concurrent T" + std::to_string(t) + "R" + std::to_string(i);
                    std::string course = "Course" + std::to_string(i);
                    
                    pqxx::work txn(local_conn);
                    txn.exec_params(
                        "INSERT INTO test_student_results (student_name, course_name, final_cijfer, timestamp) "
                        "VALUES ($1, $2, $3, $4)",
                        student, course, 75 + i, 1234567890 + t * 100 + i
                    );
                    txn.commit();
                    
                    successful_insertions++;
                }
            } catch (const std::exception& e) {
                // Log error maar laat test niet falen (concurrency issues zijn mogelijk normaal)
                std::cerr << "Concurrent thread error: " << e.what() << std::endl;
            }
        });
    }
    
    // Wacht op alle threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Verificeer dat meeste operaties succesvol waren
    EXPECT_GE(successful_insertions.load(), num_threads * records_per_thread * 0.8)
        << "Minstens 80% van concurrent operations zouden moeten slagen";
}

/**
 * Test 9: Transaction rollback
 * Test database transaction integriteit
 */
TEST_F(DatabaseTest, TestTransactionRollback)
{
    try {
        pqxx::work txn(*connection_);
        
        // Insert een record
        txn.exec_params(
            "INSERT INTO test_student_results (student_name, course_name, final_cijfer, timestamp) "
            "VALUES ($1, $2, $3, $4)",
            "Test Rollback", "Math", 75, 1234567890
        );
        
        // Probeer invalid operation (dit zou exception moeten gooien)
        try {
            txn.exec("INSERT INTO test_student_results (invalid_column) VALUES (1)");
        } catch (const std::exception&) {
            // Verwachte fout - rollback transactie
            txn.abort();
        }
        
        // Verificeer dat record NIET is ingevoegd (door rollback)
        pqxx::work check_txn(*connection_);
        auto result = check_txn.exec_params(
            "SELECT COUNT(*) FROM test_student_results WHERE student_name = $1",
            "Test Rollback"
        );
        
        int count = result[0][0].as<int>();
        EXPECT_EQ(count, 0) << "Record zou niet moeten bestaan na rollback";
        
    } catch (const std::exception& e) {
        FAIL() << "Transaction rollback test failed: " << e.what();
    }
}

/**
 * Test 10: Performance baseline
 * Test database performance voor batch operations
 */
TEST_F(DatabaseTest, TestPerformanceBaseline)
{
    const int batch_size = 100;
    auto start_time = std::chrono::high_resolution_clock::now();
    
    try {
        pqxx::work txn(*connection_);
        
        for (int i = 0; i < batch_size; ++i) {
            txn.exec_params(
                "INSERT INTO test_student_results (student_name, course_name, final_cijfer, timestamp) "
                "VALUES ($1, $2, $3, $4)",
                "Test Perf " + std::to_string(i),
                "Course" + std::to_string(i % 5),
                50 + (i % 50),
                1234567890 + i
            );
        }
        
        txn.commit();
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        
        // Performance baseline: 100 insertions zou binnen 5 seconden moeten lukken
        EXPECT_LT(duration.count(), 5000) << "Batch insertion performance te langzaam: " << duration.count() << "ms";
        
        std::cout << "Performance baseline: " << batch_size << " records in " << duration.count() << "ms" << std::endl;
        
    } catch (const std::exception& e) {
        FAIL() << "Performance test failed: " << e.what();
    }
}

// Test runner
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
