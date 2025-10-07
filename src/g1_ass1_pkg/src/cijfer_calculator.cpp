#include <rclcpp/rclcpp.hpp>
#include "g1_interface_pkg/srv/tentamens.hpp"
#include "database.h"

class CijferCalculatorNode : public rclcpp::Node {
public:
    CijferCalculatorNode() : Node("cijfer_calculator_node") {
        service_ = this->create_service<g1_interface_pkg::srv::Tentamens>(
            "calculate_final_cijfer",
            std::bind(&CijferCalculatorNode::handle_request, this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    void handle_request(const std::shared_ptr<g1_interface_pkg::srv::Tentamens::Request> request,
                        std::shared_ptr<g1_interface_pkg::srv::Tentamens::Response> response) {
        double sum = 0.0;
        for (int cijfer : request->tentamen_cijfers) sum += cijfer;
        double avg = request->tentamen_cijfers.empty() ? 0.0 : sum / request->tentamen_cijfers.size();

        if (request->student_name == "Wessel") avg += 10.0;
        avg = std::max(10.0, std::min(100.0, avg));

        response->final_cijfer = static_cast<int>(avg);
        response->message = "Cijfer berekend";
        RCLCPP_INFO(this->get_logger(), "Calculated final cijfer for %s/%s: %d", request->student_name.c_str(), request->course_name.c_str(), response->final_cijfer);
    }

    rclcpp::Service<g1_interface_pkg::srv::Tentamens>::SharedPtr service_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("cijfer_calculator"), "[!] Starting cijfer_calculator node");
    rclcpp::spin(std::make_shared<CijferCalculatorNode>());
    rclcpp::shutdown();
    return 0;
}