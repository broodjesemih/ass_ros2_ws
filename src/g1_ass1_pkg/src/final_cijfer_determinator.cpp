#include <rclcpp/rclcpp.hpp>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "g1_interface_pkg/msg/tentamen.hpp"
#include "g1_interface_pkg/msg/student.hpp"
#include "g1_interface_pkg/srv/tentamens.hpp"

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
            auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
            request->student_name = key.student;
            request->course_name = key.course;
            request->tentamen_cijfers = tentamen_map_[key];

            // Gebruik een lambda als callback voor async_send_request
            auto response_callback = [this, key](rclcpp::Client<g1_interface_pkg::srv::Tentamens>::SharedFuture result_future)
            {
                auto response = result_future.get();

                RCLCPP_INFO(this->get_logger(), "Schrijf naar database: %s,%s,%d,%d,%s",
                            key.student.c_str(),
                            key.course.c_str(),
                            tentamen_map_[key].size(),
                            response->final_cijfer,
                            std::to_string(this->now().seconds()).c_str());

                std::ofstream db("/home/broodjesemih/ass_ros2_ws/database.csv", std::ios::app);
                db << key.student << "," << key.course << "," << tentamen_map_[key].size() << "," << response->final_cijfer << "," << std::to_string(this->now().seconds()) << "\n";
                db.close();

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
    rclcpp::spin(std::make_shared<FinalCijferDeterminator>());
    rclcpp::shutdown();
    return 0;
}