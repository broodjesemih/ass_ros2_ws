#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

struct StudentRecord
{
    std::string student_name;
    std::string course;
    int number_of_exams;
    double final_result;
    long timestamp;
};

class Database
{
public:
    static bool connect();
    static void disconnect();
    static bool saveFinalResult(const std::string& student_name, const std::string& course, int final_result);
    static bool saveHerkansingsResult(const std::string& student_name, const std::string& course, int final_result);
    static std::vector<StudentRecord> getFailedStudents();
    static std::vector<StudentRecord> getStudentsWithoutExams(); // New function
    static void printAllResults();
};
