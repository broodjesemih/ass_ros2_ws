#include <rclcpp/rclcpp.hpp>
#include <fstream>
#include <random>
#include <chrono>
#include <unordered_set>
#include "g1_interface_pkg/msg/tentamen.hpp"
#include "g1_interface_pkg/msg/student.hpp"

struct StudentCourseKey {
    std::string student;
    std::string course;
    bool operator==(const StudentCourseKey& other) const {
        return student == other.student && course == other.course;
    }
};
namespace std {
    template <>
    struct hash<StudentCourseKey> {
        std::size_t operator()(const StudentCourseKey& k) const {
            return std::hash<std::string>()(k.student) ^ std::hash<std::string>()(k.course);
        }
    };
}

class TentamenResultGenerator : public rclcpp::Node {
public:
    TentamenResultGenerator() : Node("tentamen_result_generator") {
        publisher_ = this->create_publisher<g1_interface_pkg::msg::Tentamen>("tentamen_results", 10);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(2),
            std::bind(&TentamenResultGenerator::publish_random_result, this));
        load_student_course_combinations();
    }

    // Add/remove student/course combinations via service or topic (not implemented here for brevity)

private:
    std::unordered_set<StudentCourseKey> active_combinations_;
    rclcpp::Publisher<g1_interface_pkg::msg::Tentamen>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    void load_student_course_combinations() {
        std::ifstream db("/home/broodjesemih/ass_ros2_ws/database.csv");
        std::string line;
        while (std::getline(db, line)) {
            std::istringstream iss(line);
            std::string student, course, exams, final_result, timestamp;
            std::getline(iss, student, ',');
            std::getline(iss, course, ',');
            std::getline(iss, exams, ',');
            std::getline(iss, final_result, ',');
            std::getline(iss, timestamp, ',');
            if (final_result.empty()) { // Only add if no final result
                active_combinations_.insert({student, course});
            }
        }
    }

    void publish_random_result() {
        if (active_combinations_.empty()) return;
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
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TentamenResultGenerator>());
    rclcpp::shutdown();
    return 0;
}