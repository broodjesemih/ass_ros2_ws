#include <libpq-fe.h>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "database.h"

class Database
{
public:
    Database()
    {
        conn_ = PQconnectdb(conninfo.c_str());
    }
    ~Database()
    {
        if (conn_)
            PQfinish(conn_);
    }

    bool connect()
    {
        // Connection parameters - can be configured via environment variables
        const char *host = std::getenv("POSTGRES_HOST") ? std::getenv("POSTGRES_HOST") : "localhost";
        const char *port = std::getenv("POSTGRES_PORT") ? std::getenv("POSTGRES_PORT") : "5432";
        const char *dbname = std::getenv("POSTGRES_DB") ? std::getenv("POSTGRES_DB") : "cijfer_generator";
        const char *user = std::getenv("POSTGRES_USER") ? std::getenv("POSTGRES_USER") : "postgres";
        const char *password = std::getenv("POSTGRES_PASSWORD") ? std::getenv("POSTGRES_PASSWORD") : "password";

        // Build connection string
        std::string conninfo = "host=" + std::string(host) +
                               " port=" + std::string(port) +
                               " dbname=" + std::string(dbname) +
                               " user=" + std::string(user) +
                               " password=" + std::string(password);

        // Connect to database
        conn = PQconnectdb(conninfo.c_str());

        if (PQstatus(conn) != CONNECTION_OK)
        {
            std::cerr << "Connection failed: " << PQerrorMessage(conn) << std::endl;
            PQfinish(conn);
            conn = nullptr;
            return false;
        }

        std::cout << "✅ Connected to PostgreSQL database: " << dbname << std::endl;

        // Create table if it doesn't exist
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

        PGresult *res = PQexec(conn, createSQL);
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            std::cerr << "CREATE TABLE failed: " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            return false;
        }
        PQclear(res);

        // Insert some initial data if table is empty
        const char *checkSQL = "SELECT COUNT(*) FROM student_results;";
        res = PQexec(conn, checkSQL);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            return false;
        }

        int count = std::atoi(PQgetvalue(res, 0, 0));
        PQclear(res);

        if (count == 0)
        {
            std::cout << "Database is empty, inserting initial student/course combinations..." << std::endl;

            std::vector<std::pair<std::string, std::string>> initial_data = {
                {"Alice", "Mathematics"},
                {"Bob", "Physics"},
                {"Charlie", "Chemistry"},
                {"Diana", "Biology"},
                {"Eve", "Computer Science"},
                {"Frank", "Mathematics"},
                {"Grace", "Physics"},
                {"Henry", "Chemistry"},
                {"Ivy", "Biology"},
                {"Jack", "Computer Science"},
                {"Wessel", "Advanced Mathematics"} // Special student with bonus
            };

            for (const auto &[student, course] : initial_data)
            {
                std::string insertSQL = "INSERT INTO student_results (student_name, course, number_of_exams, final_result, timestamp) VALUES ('" +
                                        student + "', '" + course + "', 0, 0, " + std::to_string(time(nullptr)) + ");";

                PGresult *insert_res = PQexec(conn, insertSQL.c_str());
                if (PQresultStatus(insert_res) != PGRES_COMMAND_OK)
                {
                    std::cerr << "INSERT failed for " << student << ": " << PQerrorMessage(conn) << std::endl;
                }
                PQclear(insert_res);
            }
        }

        return true;
    }

    void disconnect()
    {
        if (conn)
        {
            PQfinish(conn);
            conn = nullptr;
            std::cout << "Database connection closed." << std::endl;
        }
    }

    std::vector<std::pair<std::string, std::string>> getUnfinishedCombinations()
    {
        std::vector<std::pair<std::string, std::string>> combinations;

        if (!conn)
            return combinations;

        const char *sql = "SELECT student_name, course FROM student_results WHERE number_of_exams < 3;";

        PGresult *res = PQexec(conn, sql);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            return combinations;
        }

        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++)
        {
            std::string student = PQgetvalue(res, i, 0);
            std::string course = PQgetvalue(res, i, 1);
            combinations.emplace_back(student, course);
        }

        PQclear(res);
        return combinations;
    }

    bool saveFinalResult(const std::string &student_name, const std::string &course, int final_result)
    {
        if (!conn)
            return false;

        // Escape single quotes in student names and courses
        std::string escaped_student = student_name;
        std::string escaped_course = course;

        // Simple escape - replace ' with ''
        size_t pos = 0;
        while ((pos = escaped_student.find("'", pos)) != std::string::npos)
        {
            escaped_student.replace(pos, 1, "''");
            pos += 2;
        }
        pos = 0;
        while ((pos = escaped_course.find("'", pos)) != std::string::npos)
        {
            escaped_course.replace(pos, 1, "''");
            pos += 2;
        }

        std::string sql = "UPDATE student_results SET number_of_exams = 3, final_result = " +
                          std::to_string(final_result) + ", timestamp = " + std::to_string(time(nullptr)) +
                          " WHERE student_name = '" + escaped_student + "' AND course = '" + escaped_course + "';";

        PGresult *res = PQexec(conn, sql.c_str());

        bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);

        if (!success)
        {
            std::cerr << "❌ UPDATE failed: " << PQerrorMessage(conn) << std::endl;
            std::cerr << "SQL was: " << sql << std::endl;
        }
        else
        {
            std::cout << "✅ SAVED final result for " << student_name << " in " << course << ": " << final_result << std::endl;
        }

        PQclear(res);
        return success;
    }

    std::vector<StudentRecord> getFailedStudents()
    {
        std::vector<StudentRecord> failed_students;

        if (!conn)
            return failed_students;

        const char *sql = "SELECT student_name, course, number_of_exams, final_result, timestamp FROM student_results WHERE final_result > 0 AND final_result < 55;";

        PGresult *res = PQexec(conn, sql);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            return failed_students;
        }

        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++)
        {
            StudentRecord record;
            record.student_name = PQgetvalue(res, i, 0);
            record.course = PQgetvalue(res, i, 1);
            record.number_of_exams = std::atoi(PQgetvalue(res, i, 2));
            record.final_result = std::atof(PQgetvalue(res, i, 3));
            record.timestamp = std::atol(PQgetvalue(res, i, 4));
            failed_students.push_back(record);
        }

        PQclear(res);
        return failed_students;
    }

    std::vector<StudentRecord> getStudentsWithoutExams()
    {
        std::vector<StudentRecord> students_without_exams;

        if (!conn)
            return students_without_exams;

        const char *sql = "SELECT student_name, course, number_of_exams, final_result, timestamp FROM student_results WHERE number_of_exams = 0;";

        PGresult *res = PQexec(conn, sql);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            std::cerr << "SELECT students without exams failed: " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            return students_without_exams;
        }

        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++)
        {
            StudentRecord record;
            record.student_name = PQgetvalue(res, i, 0);
            record.course = PQgetvalue(res, i, 1);
            record.number_of_exams = std::atoi(PQgetvalue(res, i, 2));
            record.final_result = std::atof(PQgetvalue(res, i, 3));
            record.timestamp = std::atol(PQgetvalue(res, i, 4));
            students_without_exams.push_back(record);
        }

        PQclear(res);
        return students_without_exams;
    }

    bool saveHerkansingsResult(const std::string &student_name, const std::string &course, int final_result)
    {
        if (!conn)
            return false;

        // Escape single quotes
        std::string escaped_student = student_name;
        std::string escaped_course = course;

        size_t pos = 0;
        while ((pos = escaped_student.find("'", pos)) != std::string::npos)
        {
            escaped_student.replace(pos, 1, "''");
            pos += 2;
        }
        pos = 0;
        while ((pos = escaped_course.find("'", pos)) != std::string::npos)
        {
            escaped_course.replace(pos, 1, "''");
            pos += 2;
        }

        // Insert new herkansing result (keep old result for history)
        std::string sql = "INSERT INTO student_results (student_name, course, number_of_exams, final_result, timestamp) VALUES ('" +
                          escaped_student + "', '" + escaped_course + "', 3, " + std::to_string(final_result) +
                          ", " + std::to_string(time(nullptr)) + ");";

        PGresult *res = PQexec(conn, sql.c_str());
        bool success = (PQresultStatus(res) == PGRES_COMMAND_OK);

        if (!success)
        {
            std::cerr << "INSERT herkansing failed: " << PQerrorMessage(conn) << std::endl;
        }
        else
        {
            std::cout << "Saved herkansing result for " << student_name << " in " << course << ": " << final_result << std::endl;
        }

        PQclear(res);
        return success;
    }

    void printAllResults()
    {
        if (!conn)
            return;

        const char *sql = "SELECT student_name, course, number_of_exams, final_result, timestamp FROM student_results ORDER BY timestamp DESC;";

        PGresult *res = PQexec(conn, sql);
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            return;
        }

        std::cout << "\n=== All Student Results ===" << std::endl;
        std::cout << std::left << std::setw(15) << "Student" << std::setw(20) << "Course"
                  << std::setw(10) << "Exams" << std::setw(12) << "Final Grade"
                  << std::setw(15) << "Timestamp" << std::endl;
        std::cout << std::string(75, '-') << std::endl;

        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++)
        {
            std::cout << std::left << std::setw(15) << PQgetvalue(res, i, 0)
                      << std::setw(20) << PQgetvalue(res, i, 1)
                      << std::setw(10) << PQgetvalue(res, i, 2)
                      << std::setw(12) << PQgetvalue(res, i, 3)
                      << std::setw(15) << PQgetvalue(res, i, 4) << std::endl;
        }

        PQclear(res);
        std::cout << "========================\n"
                  << std::endl;
    }

    // Test database connection
    bool testConnection()
    {
        if (!conn)
            return false;

        PGresult *res = PQexec(conn, "SELECT version();");
        bool success = (PQresultStatus(res) == PGRES_TUPLES_OK);

        if (success)
        {
            std::cout << "PostgreSQL version: " << PQgetvalue(res, 0, 0) << std::endl;
        }

        PQclear(res);
        return success;
    }

private:
    PGconn *conn_;
};