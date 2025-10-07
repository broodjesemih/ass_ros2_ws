#include <rclcpp/rclcpp.hpp>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "g1_interface_pkg/msg/tentamen.hpp"
#include "g1_interface_pkg/msg/student.hpp"
#include "g1_interface_pkg/srv/tentamens.hpp"
#include "database.h"

struct StudentCourseKey
{
    std::string student;
    std::string course;
    bool operator==(const StudentCourseKey &other) const
    {
        return student == other.student && course == other.course;
    }
};
namespace std
{
    template <>
    struct hash<StudentCourseKey>
    {
        std::size_t operator()(const StudentCourseKey &k) const
        {
            return std::hash<std::string>()(k.student) ^ std::hash<std::string>()(k.course);
        }
    };
}

class FinalCijferDeterminator : public rclcpp::Node
{
public:
    FinalCijferDeterminator() : Node("final_cijfer_determinator")
    {
        RCLCPP_INFO(this->get_logger(), "final_cijfer_determinator gestart!");
        tentamen_sub_ = this->create_subscription<g1_interface_pkg::msg::Tentamen>(
            "tentamen_results", 10, std::bind(&FinalCijferDeterminator::tentamen_callback, this, std::placeholders::_1));
        cijfer_client_ = this->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");
    }

private:
    std::unordered_map<StudentCourseKey, std::vector<int>> tentamen_map_;
    rclcpp::Subscription<g1_interface_pkg::msg::Tentamen>::SharedPtr tentamen_sub_;
    rclcpp::Client<g1_interface_pkg::srv::Tentamens>::SharedPtr cijfer_client_;

    void tentamen_callback(const g1_interface_pkg::msg::Tentamen::SharedPtr msg)
    {
        StudentCourseKey key{msg->student_name, msg->course_name};
        tentamen_map_[key].push_back(msg->tentamen_cijfer);

        RCLCPP_INFO(this->get_logger(), "Ontvangen tentamen: %s/%s %d", msg->student_name.c_str(), msg->course_name.c_str(), msg->tentamen_cijfer);

        // Check if we have enough results (simulate: 3 tentamens per course)
        if (tentamen_map_[key].size() >= 3)
        {
            Database db;

            auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
            request->student_name = key.student;
            request->course_name = key.course;
            request->tentamen_cijfers = tentamen_map_[key];

            // Gebruik een lambda als callback voor async_send_request
            auto response_callback = [this, key](rclcpp::Client<g1_interface_pkg::srv::Tentamens>::SharedFuture result_future)
            {
                auto response = result_future.get();

                RCLCPP_INFO(this->get_logger(),
                            "Schrijf naar database: %s,%s,%zu,%d,%s",
                            key.student.c_str(),
                            key.course.c_str(),
                            tentamen_map_[key].size(),
                            response->final_cijfer,
                            std::to_string(this->now().seconds()).c_str());

                if (!db.connect())
                {
                    std::cerr << "Could not open database!\n";
                }

                // Prepare the record
                StudentRecord record;
                record.student_name = key.student;
                record.course = key.course;
                record.number_of_exams = static_cast<int>(tentamen_map_[key].size());
                record.final_result = response->final_cijfer;
                record.timestamp = this->now().seconds();

                // Insert into PostgreSQL
                std::cout << "🔄 Attempting to save: " << record.student_name << "/" << record.course << " = " << record.final_result << std::endl;
                if (!db.saveFinalResult(record.student_name, record.course, record.final_result))
                {
                    std::cerr << "❌ Failed to save record to database\n";
                }
                else
                {
                    std::cout << "✅ Successfully saved to database!\n";
                }

                RCLCPP_INFO(this->get_logger(), "Final cijfer for %s/%s: %d", key.student.c_str(), key.course.c_str(), response->final_cijfer);

                tentamen_map_.erase(key);
            };

            cijfer_client_->async_send_request(request, response_callback);
        }
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("final_cijfer_determinator"), "[!] Starting final_cijfer_determinator node");
    rclcpp::spin(std::make_shared<FinalCijferDeterminator>());
    rclcpp::shutdown();
    return 0;
}