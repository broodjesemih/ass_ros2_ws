#include <rclcpp/rclcpp.hpp>
#include <fstream>
#include <random>
#include <chrono>
#include <unordered_set>
#include "g1_interface_pkg/msg/tentamen.hpp"
#include "g1_interface_pkg/msg/student.hpp"
#include "database.cpp"

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

class TentamenResultGenerator : public rclcpp::Node
{
public:
    TentamenResultGenerator() : Node("tentamen_result_generator")
    {
        publisher_ = this->create_publisher<g1_interface_pkg::msg::Tentamen>("tentamen_results", 10);
        student_control_sub_ = this->create_subscription<g1_interface_pkg::msg::Student>(
            "student_control", 10,
            std::bind(&TentamenResultGenerator::student_control_callback, this, std::placeholders::_1));
        timer_ = this->create_wall_timer(
            std::chrono::seconds(2),
            std::bind(&TentamenResultGenerator::publish_random_result, this));
        load_student_course_combinations();
    }


private:
    std::unordered_set<StudentCourseKey> active_combinations_;
    rclcpp::Publisher<g1_interface_pkg::msg::Tentamen>::SharedPtr publisher_;
    rclcpp::Subscription<g1_interface_pkg::msg::Student>::SharedPtr student_control_sub_;
    rclcpp::TimerBase::SharedPtr timer_;

    void load_student_course_combinations()
    {

        if (!Database::open())
        {
            std::cerr << "Could not open database!\n";
        }

        auto records = Database::getWithoutFinalResult();
        for (const auto &r : records)
        {
            active_combinations_.insert(StudentCourseKey{r.student_name, r.course});
        }
    }

    void publish_random_result()
    {
        if (active_combinations_.empty())
            return;
        auto it = active_combinations_.begin();
        std::advance(it, rand() % active_combinations_.size());
        auto key = *it;

        g1_interface_pkg::msg::Tentamen msg;
        msg.stamp = this->now();
        msg.student_name = key.student;
        msg.course_name = key.course;
        msg.tentamen_cijfer = 10 + (rand() % 91); // 10-100

        publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Published tentamen for %s/%s: %d", key.student.c_str(), key.course.c_str(), msg.tentamen_cijfer);
    }

    void student_control_callback(const g1_interface_pkg::msg::Student::SharedPtr msg)
    {
        StudentCourseKey key{msg->name, msg->course};
        if (msg->command == "stop")
        {
            active_combinations_.erase(key);
            RCLCPP_INFO(this->get_logger(), "Stopped generating for %s/%s", msg->name.c_str(), msg->course.c_str());
        }
        else if (msg->command == "again")
        {
            active_combinations_.insert(key);
            RCLCPP_INFO(this->get_logger(), "Resumed generating for %s/%s", msg->name.c_str(), msg->course.c_str());
        }
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("tentamen_result_generator"), "[!] Starting tentamen_result_generator node");
    rclcpp::spin(std::make_shared<TentamenResultGenerator>());
    rclcpp::shutdown();
    return 0;
}
