#include <rclcpp/rclcpp.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "g1_interface_pkg/action/herkanser.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

class HerkansingSchedulerNode : public rclcpp::Node {
public:
  using Herkanser = g1_interface_pkg::action::Herkanser;
  HerkansingSchedulerNode()
  : Node("herkansing_scheduler")
  {
    action_client_ = rclcpp_action::create_client<Herkanser>(this, "herkanser");
    timer_ = this->create_wall_timer(
            std::chrono::seconds(10),
            std::bind(&HerkansingSchedulerNode::check_failed_students, this));
  }

private:
  rclcpp_action::Client<Herkanser>::SharedPtr action_client_;
  rclcpp::TimerBase::SharedPtr timer_;

  void check_failed_students()
  {
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

      int cijfer = final_result.empty() ? 0 : std::stoi(final_result);
      if (cijfer >= 10 && cijfer <= 54) {
        auto goal_msg = Herkanser::Goal();
        goal_msg.student_name = student;
        goal_msg.course_name = course;
        action_client_->async_send_goal(goal_msg);
        RCLCPP_INFO(this->get_logger(), "Requested herkansing for %s/%s", student.c_str(),
          course.c_str());
      }
    }
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<HerkansingSchedulerNode>());
  rclcpp::shutdown();
  return 0;
}
