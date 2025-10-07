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
    Database();
    ~Database();
    bool connect();
    void disconnect();
    bool saveFinalResult(const std::string &student_name, const std::string &course, int final_result);
    bool saveHerkansingsResult(const std::string &student_name, const std::string &course, int final_result);
    std::vector<StudentRecord> getFailedStudents();
    std::vector<StudentRecord> getStudentsWithoutExams(); // New function
    void printAllResults();
};
