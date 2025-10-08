/* 
 * GRADE CALCULATOR SERVICE NODE - ROS2 Grade Calculator System
 *
 * PURPOSE: Central grade calculation service implementing Dutch academic grading algorithms
 * ROLE: Synchronous service provider for final grade computation based on multiple exam scores
 *
 * BUSINESS LOGIC:
 * - Arithmetic mean calculation from multiple exam scores
 * - Special "Wessel Bonus" (+10 points for student named "Wessel")
 * - Dutch grading system enforcement (10-100 scale with boundaries)
 * - Integer grade conversion for standardized output
 *
 * SERVICE INTERFACE:
 * - Service Name: "calculate_final_cijfer"
 * - Input: Student name, course name, array of exam scores
 * - Output: Calculated final grade (integer) and status message
 *
 * INTEGRATION: Called by final_cijfer_determinator and herkansing_cijfer_determinator
 * RELIABILITY: Synchronous processing ensures immediate grade availability
 *
 * Coded by: Semih, Nout, Tycho
 * Last modified: October 9, 2025
 */

#include <rclcpp/rclcpp.hpp>                        // ROS2 C++ client library
#include "g1_interface_pkg/srv/tentamens.hpp"       // Custom service definition for grade calculation
#include "database.cpp"                             // Database abstraction layer (header-only inclusion)

// Grade Calculator Service Node Class
// Provides synchronous grade calculation service with business logic implementation
class CijferCalculatorNode : public rclcpp::Node {
public:
    // Constructor: Initialize the ROS2 node and create the grade calculation service
    CijferCalculatorNode() : Node("cijfer_calculator_node") {
        // Create the service server for grade calculation requests
        // Service name: "calculate_final_cijfer" - called by other nodes for grade computation
        // Callback: handle_request - processes incoming calculation requests
        service_ = this->create_service<g1_interface_pkg::srv::Tentamens>(
            "calculate_final_cijfer",
            std::bind(&CijferCalculatorNode::handle_request, this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    // Service callback function: Processes grade calculation requests
    // Input: Request containing student name, course name, and array of exam scores
    // Output: Response containing calculated final grade and status message
    void handle_request(const std::shared_ptr<g1_interface_pkg::srv::Tentamens::Request> request,
                        std::shared_ptr<g1_interface_pkg::srv::Tentamens::Response> response) {
        
        // STEP 1: Calculate average from all exam scores
        double sum = 0.0;
        // Sum all individual exam grades from the request
        for (int cijfer : request->tentamen_cijfers) {
            sum += cijfer;
        }
        // Calculate arithmetic mean, handle empty array case
        double avg = request->tentamen_cijfers.empty() ? 0.0 : sum / request->tentamen_cijfers.size();

        // STEP 2: Apply special business logic - Wessel Bonus
        // Special case: Students named "Wessel" receive a +10 point bonus
        if (request->student_name == "Wessel") {
            avg += 10.0;  // Add 10 bonus points for Wessel
        }

        // STEP 3: Enforce grade boundaries (Dutch grading system: 10-100 scale)
        // Minimum grade: 10 (fail threshold)
        // Maximum grade: 100 (perfect score)
        avg = std::max(10.0, std::min(100.0, avg));

        // STEP 4: Prepare response with calculated grade and confirmation message
        response->final_cijfer = static_cast<int>(avg);  // Convert to integer grade
        response->message = "Grade calculated";           // Success confirmation message
        
        // Log the calculation result for monitoring and debugging
        RCLCPP_INFO(this->get_logger(), "Calculated final grade for %s/%s: %d", 
                   request->student_name.c_str(), request->course_name.c_str(), response->final_cijfer);
    }

    // ROS2 service server handle for grade calculation requests
    rclcpp::Service<g1_interface_pkg::srv::Tentamens>::SharedPtr service_;
};

// Main function: Entry point for the Grade Calculator Service Node
int main(int argc, char **argv) {
    // Initialize ROS2 runtime environment with command line arguments
    rclcpp::init(argc, argv);
    
    // Log node startup for system monitoring
    RCLCPP_INFO(rclcpp::get_logger("cijfer_calculator"), "Starting Grade Calculator service node");
    
    // Create and run the grade calculator node
    // spin() keeps the node alive and processes incoming service requests
    rclcpp::spin(std::make_shared<CijferCalculatorNode>());
    
    // Clean shutdown when node terminates (e.g., Ctrl+C)
    rclcpp::shutdown();
    return 0;
}