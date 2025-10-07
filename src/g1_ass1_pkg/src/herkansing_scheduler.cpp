#include <rclcpp/rclcpp.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "g1_interface_pkg/action/herkanser.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "database.h"


class HerkansingSchedulerNode : public rclcpp::Node
{
public:
    using Herkanser = g1_interface_pkg::action::Herkanser;
    HerkansingSchedulerNode() : Node("herkansing_scheduler")
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
        if (!Database::connect())
        {
            std::cerr << "Could not open database!\n";
        }
        // Get all rows from the database
        auto records = Database::getAll();

        for (const auto &r : records)
        {
            int cijfer = static_cast<int>(r.final_result);

            if (cijfer >= 10 && cijfer <= 54)
            {
                auto goal_msg = Herkanser::Goal();
                goal_msg.student_name = r.student_name;
                goal_msg.course_name = r.course;
                action_client_->async_send_goal(goal_msg);

                RCLCPP_INFO(this->get_logger(),
                            "Requested herkansing for %s/%s",
                            r.student_name.c_str(), r.course.c_str());
            }
        }
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("herkansing_scheduler"), "[!] Starting herkansing_scheduler node");
    rclcpp::spin(std::make_shared<HerkansingSchedulerNode>());
    rclcpp::shutdown();
    return 0;
}