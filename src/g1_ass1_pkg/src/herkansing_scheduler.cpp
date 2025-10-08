/* 
 * RETAKE EXAM SCHEDULER NODE - ROS2 Grade Calculator System
 *
 * PURPOSE: Automatically monitors student grades and schedules retake exams for failing students
 * ROLE: Intelligent scheduler that identifies academic failures and initiates grade improvement opportunities
 *
 * DUTCH CONTEXT: "Herkansing" = retake exam opportunity for students with failing grades
 *
 * WORKFLOW:
 * 1. Periodically query database for all finalized student grades
 * 2. Identify students with failing grades (10-54 range, below passing threshold of 55)
 * 3. Automatically schedule retake exams via action client requests
 * 4. Track processed retakes to prevent duplicate scheduling
 * 5. Log scheduling activities for system monitoring
 *
 * BUSINESS LOGIC: 
 * - Failing grade threshold: 10-54 (inclusive)
 * - Duplicate prevention: Once-per-student-course scheduling
 * - Periodic monitoring: 30-second interval checks
 *
 * INTEGRATION: Action client to herkansing_cijfer_determinator for retake processing
 *
 * Coded by: Semih, Nout, Tycho
 * Last modified: October 9, 2025
 */

// CORE ROS2 DEPENDENCIES
#include <rclcpp/rclcpp.hpp>           // ROS2 C++ client library for node functionality
#include <fstream>                    // File I/O operations (currently unused)
#include <vector>                     // STL vector for record collections
#include <string>                     // String operations for student/course identification
#include <set>                        // STL set for duplicate tracking

// CUSTOM ACTION INTERFACE
#include "g1_interface_pkg/action/herkanser.hpp" // Retake exam action interface

// ROS2 ACTION FRAMEWORK
#include "rclcpp_action/rclcpp_action.hpp"      // Action client implementation support

// DATABASE ABSTRACTION LAYER
#include "database.cpp"               // PostgreSQL database operations for grade monitoring


/**
 * RETAKE EXAM SCHEDULER CLASS: Automated Academic Failure Detection and Response
 * 
 * ARCHITECTURE: Timer-driven monitoring system with action client integration
 * RESPONSIBILITY: Continuous surveillance of student grades and automatic retake scheduling
 * 
 * MONITORING STRATEGY: Periodic database polling to identify failing students
 * SCHEDULING POLICY: One retake opportunity per student/course combination
 * 
 * INTEGRATION: Action client to retake processing system for exam coordination
 */
class HerkansingSchedulerNode : public rclcpp::Node
{
public:
    // TYPE ALIAS: Simplify retake action interface usage throughout the class
    using Herkanser = g1_interface_pkg::action::Herkanser;
    
    /**
     * CONSTRUCTOR: Initialize retake exam scheduling infrastructure
     * 
     * SETUP SEQUENCE:
     * 1. Create action client for retake exam requests
     * 2. Create periodic timer for continuous grade monitoring
     * 
     * NODE NAME: "herkansing_scheduler" for ROS2 network identification
     * TIMING: 30-second intervals for balanced responsiveness and system load
     */
    HerkansingSchedulerNode() : Node("herkansing_scheduler")
    {
        // ACTION CLIENT: Connect to retake exam processing service
        // Action: "herkanser" - sends retake requests to processing node
        action_client_ = rclcpp_action::create_client<Herkanser>(this, "herkanser");
        
        // PERIODIC TIMER: Schedule regular grade monitoring checks
        // Frequency: 30 seconds - balanced between responsiveness and resource usage
        // Callback: check_failed_students() - identifies and schedules retakes
        timer_ = this->create_wall_timer(
            std::chrono::seconds(30), // Reduced frequency to 30 seconds for system efficiency
            std::bind(&HerkansingSchedulerNode::check_failed_students, this));
    }

private:
    // ROS2 INTERFACE HANDLES: Maintain connections to ROS2 communication channels
    rclcpp_action::Client<Herkanser>::SharedPtr action_client_;    // Retake exam action client
    rclcpp::TimerBase::SharedPtr timer_;                          // Periodic monitoring timer
    
    // DUPLICATE PREVENTION: Track already processed retake requests
    // KEY FORMAT: "student_name/course_name" for unique identification
    // PURPOSE: Prevents multiple retake scheduling for same student/course combination
    // PERSISTENCE: In-memory storage (resets on node restart - intentional for fresh starts)
    std::set<std::string> processed_herkansingen_;

    /**
     * PERIODIC MONITORING: Check for students requiring retake exams
     * 
     * WORKFLOW:
     * 1. Establish database connection for grade monitoring
     * 2. Retrieve all finalized student records from database
     * 3. Evaluate each grade against failure threshold (10-54)
     * 4. Schedule retakes for failing grades (with duplicate prevention)
     * 5. Log scheduling activities for system monitoring
     * 
     * BUSINESS RULES:
     * - Failing grade range: 10-54 (inclusive)
     * - Passing threshold: 55+ (no retake needed)
     * - One retake per student/course combination
     * 
     * ERROR HANDLING: Graceful database connection failures
     */
    void check_failed_students()
    {
        // PHASE 1: Establish database connection for grade monitoring
        if (!Database::open())
        {
            std::cerr << "Could not open database!\n";
            return; // Exit gracefully if database unavailable
        }
        
        // PHASE 2: Retrieve complete grade dataset for analysis
        auto records = Database::getAll();
        int new_herkansingen = 0; // Counter for newly scheduled retakes

        // PHASE 3: Evaluate each student record for retake eligibility
        for (const auto &r : records)
        {
            // GRADE EVALUATION: Convert final result to integer for threshold comparison
            int cijfer = static_cast<int>(r.final_result);

            // FAILURE DETECTION: Check if grade falls within failing range (10-54)
            // BUSINESS RULE: Grades 10-54 require retake opportunity
            // EXCLUSIONS: Grades below 10 (invalid) and 55+ (passing) are ignored
            if (cijfer >= 10 && cijfer <= 54)
            {
                // DUPLICATE PREVENTION: Create unique identifier for student/course pair
                std::string key = r.student_name + "/" + r.course;
                
                // CHECK PROCESSING HISTORY: Only schedule if not already processed
                // EFFICIENCY: Prevents redundant retake requests for same failure
                if (processed_herkansingen_.find(key) == processed_herkansingen_.end())
                {
                    // RETAKE SCHEDULING: Prepare and send action goal for failed student
                    auto goal_msg = Herkanser::Goal();
                    goal_msg.student_name = r.student_name;    // Student requiring retake
                    goal_msg.course_name = r.course;           // Course requiring retake
                    
                    // ASYNC ACTION CALL: Send retake request without blocking scheduler
                    action_client_->async_send_goal(goal_msg);

                    // TRACKING: Mark this student/course as processed
                    processed_herkansingen_.insert(key);
                    new_herkansingen++;

                    RCLCPP_INFO(this->get_logger(),
                                "Requested herkansing for %s/%s (cijfer: %d)",
                                r.student_name.c_str(), r.course.c_str(), cijfer);
                }
            }
        }
        
        // PHASE 4: Log monitoring results for system transparency
        if (new_herkansingen == 0)
        {
            // NO ACTION NEEDED: All students either passing or already have retakes scheduled
            RCLCPP_INFO(this->get_logger(), "No new herkansingen needed (checked %zu records)", records.size());
        }
        else
        {
            // RETAKES SCHEDULED: Report number of new retake requests initiated
            RCLCPP_INFO(this->get_logger(), "Scheduled %d new herkansingen", new_herkansingen);
        }
    }
}; // End of HerkansingSchedulerNode class

/**
 * MAIN FUNCTION: Entry point for Retake Exam Scheduler ROS2 Node
 * 
 * EXECUTION FLOW:
 * 1. Initialize ROS2 system and node context
 * 2. Create and start HerkansingSchedulerNode monitoring system
 * 3. Enter event loop for continuous grade monitoring and retake scheduling
 * 4. Clean shutdown when terminated
 * 
 * NODE LIFECYCLE: Runs continuously monitoring for academic failures
 * INTEGRATION: Autonomous scheduler in grade calculator system ecosystem
 * 
 * OPERATIONAL MODE: Background service with periodic monitoring cycles
 * BUSINESS VALUE: Ensures no failing student misses retake opportunities
 */
int main(int argc, char **argv)
{
    // PHASE 1: Initialize ROS2 runtime system
    rclcpp::init(argc, argv);
    
    // PHASE 2: Log node startup for system monitoring
    RCLCPP_INFO(rclcpp::get_logger("herkansing_scheduler"), 
               "[!] Starting herkansing_scheduler node");
    
    // PHASE 3: Create node instance and enter monitoring loop
    // SPIN PATTERN: Handles timer callbacks and action client communications
    rclcpp::spin(std::make_shared<HerkansingSchedulerNode>());
    
    // PHASE 4: Clean shutdown when spin() returns
    rclcpp::shutdown();
    return 0; // Success exit code
}
// END OF FILE: Retake Exam Scheduler - Automated Academic Failure Response System