#include <rclcpp/rclcpp.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include "g1_interface_pkg/action/herkanser.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "database.cpp"


class HerkansingSchedulerNode : public rclcpp::Node
{
public:
    using Herkanser = g1_interface_pkg::action::Herkanser;
    HerkansingSchedulerNode() : Node("herkansing_scheduler")
    {
        action_client_ = rclcpp_action::create_client<Herkanser>(this, "herkanser");
        timer_ = this->create_wall_timer(
            std::chrono::seconds(30), // Reduced frequency to 30 seconds
            std::bind(&HerkansingSchedulerNode::check_failed_students, this));
    }

private:
    rclcpp_action::Client<Herkanser>::SharedPtr action_client_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::set<std::string> processed_herkansingen_; // Track processed requests

    void check_failed_students()
    {
        if (!Database::open())
        {
            std::cerr << "Could not open database!\n";
            return;
        }
        
        // Get all rows from the database
        auto records = Database::getAll();
        int new_herkansingen = 0;

        for (const auto &r : records)
        {
            int cijfer = static_cast<int>(r.final_result);

            if (cijfer >= 10 && cijfer <= 54)
            {
                // Create unique identifier for this student/course combination
                std::string key = r.student_name + "/" + r.course;
                
                // Only process if we haven't already requested herkansing for this combination
                if (processed_herkansingen_.find(key) == processed_herkansingen_.end())
                {
                    auto goal_msg = Herkanser::Goal();
                    goal_msg.student_name = r.student_name;
                    goal_msg.course_name = r.course;
                    action_client_->async_send_goal(goal_msg);

                    processed_herkansingen_.insert(key);
                    new_herkansingen++;

                    RCLCPP_INFO(this->get_logger(),
                                "Requested herkansing for %s/%s (cijfer: %d)",
                                r.student_name.c_str(), r.course.c_str(), cijfer);
                }
            }
        }
        
        if (new_herkansingen == 0)
        {
            RCLCPP_INFO(this->get_logger(), "No new herkansingen needed (checked %zu records)", records.size());
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "Scheduled %d new herkansingen", new_herkansingen);
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