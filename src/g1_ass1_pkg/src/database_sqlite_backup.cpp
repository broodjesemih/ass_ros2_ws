#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

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

    sqlite3 *db = nullptr;

    bool open()
    {
        // build absolute path in the current working directory
        std::string db_path = (std::filesystem::current_path() / "database.sqlite").string();

        int rc = sqlite3_open(db_path.c_str(), &db);
        if (rc)
        {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            db = nullptr;
            return false;
        }

        const char *createSQL = R"(
            CREATE TABLE IF NOT EXISTS student_results (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                student_name TEXT NOT NULL,
                course TEXT NOT NULL,
                number_of_exams INTEGER,
                final_result REAL,
                timestamp INTEGER
            );
        )";

        char *errMsg = nullptr;
        rc = sqlite3_exec(db, createSQL, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK)
        {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            return false;
        }

        // --- NEW: check if table is empty ---
        const char *countSQL = "SELECT COUNT(*) FROM student_results;";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, countSQL, -1, &stmt, nullptr);
        if (rc == SQLITE_OK)
        {
            if (sqlite3_step(stmt) == SQLITE_ROW)
            {
                int count = sqlite3_column_int(stmt, 0);
                if (count == 0)
                {
                    std::cout << "[Database] Table empty, inserting initial values...\n";
                    const char *insertSQL = R"(
                    INSERT INTO student_results (student_name, course, number_of_exams, final_result, timestamp)
                    VALUES
                        ('Alice', 'Math', 0, NULL, strftime('%s','now')),
                        ('Bob', 'Physics', 0, NULL, strftime('%s','now')),
                        ('Charlie', 'Chemistry', 0, NULL, strftime('%s','now'));
                )";
                    rc = sqlite3_exec(db, insertSQL, nullptr, nullptr, &errMsg);
                    if (rc != SQLITE_OK)
                    {
                        std::cerr << "Insert error: " << errMsg << std::endl;
                        sqlite3_free(errMsg);
                    }
                }
            }
            sqlite3_finalize(stmt);
        }
        else
        {
            std::cerr << "Failed to prepare count query: " << sqlite3_errmsg(db) << std::endl;
        }

        return true;
    }

    void close()
    {
        if (db)
            sqlite3_close(db);
        db = nullptr;
    }
bool insert(const StudentRecord &record)
{
    if (!db) return false;

    // First check if there is an unfinished row (final_result IS NULL)
    const char *selectSQL = R"(
        SELECT id FROM student_results
        WHERE student_name = ? AND course = ? AND final_result IS NULL
        LIMIT 1;
    )";

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, record.student_name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, record.course.c_str(), -1, SQLITE_TRANSIENT);

    int rowId = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        rowId = sqlite3_column_int(stmt, 0); // unfinished row found
    }
    sqlite3_finalize(stmt);

    if (rowId != -1) {
        // --- Update unfinished row ---
        const char *updateSQL = R"(
            UPDATE student_results
            SET number_of_exams = ?, final_result = ?, timestamp = ?
            WHERE id = ?;
        )";

        rc = sqlite3_prepare_v2(db, updateSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Prepare update failed: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        sqlite3_bind_int(stmt, 1, record.number_of_exams);
        if (record.final_result == 0.0) {
            sqlite3_bind_null(stmt, 2);
        } else {
            sqlite3_bind_double(stmt, 2, record.final_result);
        }
        sqlite3_bind_int64(stmt, 3, record.timestamp);
        sqlite3_bind_int(stmt, 4, rowId);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            std::cerr << "Update failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
    } else {
        // --- Insert new row ---
        const char *insertSQL = R"(
            INSERT INTO student_results (student_name, course, number_of_exams, final_result, timestamp)
            VALUES (?, ?, ?, ?, ?);
        )";

        rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Prepare insert failed: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        sqlite3_bind_text(stmt, 1, record.student_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, record.course.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, record.number_of_exams);

        if (record.final_result == 0.0) {
            sqlite3_bind_null(stmt, 4);
        } else {
            sqlite3_bind_double(stmt, 4, record.final_result);
        }
        sqlite3_bind_int64(stmt, 5, record.timestamp);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
    }

    return true;
}


    std::vector<StudentRecord> getAll()
    {
        std::vector<StudentRecord> results;
        if (!db)
            return results;

        const char *selectSQL =
            "SELECT student_name, course, number_of_exams, final_result, timestamp "
            "FROM student_results;";

        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Select failed: " << sqlite3_errmsg(db) << std::endl;
            return results;
        }

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            StudentRecord record;
            record.student_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            record.course = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            record.number_of_exams = sqlite3_column_int(stmt, 2);
            record.final_result = sqlite3_column_double(stmt, 3);
            record.timestamp = sqlite3_column_int64(stmt, 4);
            results.push_back(record);
        }

        sqlite3_finalize(stmt);
        return results;
    }
    std::vector<StudentRecord> getWithoutFinalResult()
    {
        std::vector<StudentRecord> results;
        if (!db)
            return results;

        const char *selectSQL =
            "SELECT student_name, course, number_of_exams, final_result, timestamp "
            "FROM student_results WHERE final_result IS NULL;";

        sqlite3_stmt *stmt;
        int rc = sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK)
        {
            std::cerr << "Select failed: " << sqlite3_errmsg(db) << std::endl;
            return results;
        }

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            StudentRecord record;
            record.student_name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            record.course = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            record.number_of_exams = sqlite3_column_int(stmt, 2);
            record.final_result = sqlite3_column_double(stmt, 3);
            record.timestamp = sqlite3_column_int64(stmt, 4);
            results.push_back(record);
        }

        sqlite3_finalize(stmt);
        return results;
    }

} // namespace Database
