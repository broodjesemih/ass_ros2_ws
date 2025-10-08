/* 
 * FINAL GRADE DETERMINATOR NODE - ROS2 Grade Calculator System
 *
 * PURPOSE: Aggregates individual exam results and determines final course grades
 * ROLE: Central processing node that collects exam scores, calculates final grades,
 *       stores results in database, and controls the exam generation pipeline
 *
 * WORKFLOW:
 * 1. Subscribe to individual exam results from tentamen_result_generator
 * 2. Accumulate scores per student/course combination (3 exams required)
 * 3. Request final grade calculation from cijfer_calculator service
 * 4. Store finalized grades in PostgreSQL database
 * 5. Send stop commands to halt further exam generation for completed courses
 *
 * BUSINESS LOGIC: Implements 3-exam completion rule for grade finalization
 * DATA FLOW: tentamen_results → aggregation → final_grade_calculation → database → student_control
 *
 * Coded by: Semih, Nout, Tycho
 * Last modified: October 9, 2025
 */

// CORE ROS2 DEPENDENCIES
#include <rclcpp/rclcpp.hpp>           // ROS2 C++ client library for node functionality
#include <fstream>                    // File I/O operations (currently unused)
#include <vector>                     // STL vector for exam score collections
#include <algorithm>                  // STL algorithms for data manipulation
#include <sstream>                    // String stream operations (currently unused)

// CUSTOM MESSAGE AND SERVICE INTERFACES
#include "g1_interface_pkg/msg/tentamen.hpp"    // Individual exam result message format
#include "g1_interface_pkg/msg/student.hpp"     // Student control message format
#include "g1_interface_pkg/srv/tentamens.hpp"   // Grade calculation service interface

// DATABASE ABSTRACTION LAYER
#include "database.cpp"               // PostgreSQL database operations for persistent storage

/**
 * COMPOSITE KEY STRUCTURE: Student-Course Combination Identifier
 * 
 * PURPOSE: Creates unique keys for student/course pairs to manage exam score aggregation
 * USE CASE: Maps each student-course combination to their collection of exam scores
 * 
 * DESIGN: Enables efficient lookup and storage in unordered_map containers
 * PERFORMANCE: O(1) average lookup time through custom hash function
 */
struct StudentCourseKey
{
    std::string student;    // Student name identifier
    std::string course;     // Course name identifier
    
    // EQUALITY OPERATOR: Required for unordered_map key comparison
    // Ensures two keys are identical if both student AND course names match
    bool operator==(const StudentCourseKey &other) const
    {
        return student == other.student && course == other.course;
    }
};

/**
 * CUSTOM HASH FUNCTION: Enables StudentCourseKey as unordered_map key
 * 
 * TECHNIQUE: XOR combination of individual string hashes
 * PERFORMANCE: Fast hash computation for efficient map operations
 * STD NAMESPACE: Required specialization for std::unordered_map compatibility
 */
namespace std
{
    template <>
    struct hash<StudentCourseKey>
    {
        std::size_t operator()(const StudentCourseKey &k) const
        {
            // Combine hash values using XOR for reasonably good distribution
            return std::hash<std::string>()(k.student) ^ std::hash<std::string>()(k.course);
        }
    };
}

/**
 * FINAL GRADE DETERMINATOR CLASS: ROS2 Node for Grade Processing Pipeline
 * 
 * ARCHITECTURE: Subscriber-Service Client-Publisher pattern for exam processing
 * RESPONSIBILITY: Aggregate exam results and coordinate final grade determination
 * 
 * ROS2 INTERFACES:
 * - SUBSCRIBER: Receives individual exam results from generators
 * - SERVICE CLIENT: Requests final grade calculations from calculator
 * - PUBLISHER: Sends control commands to stop exam generation
 */
class FinalCijferDeterminator : public rclcpp::Node
{
public:
    /**
     * CONSTRUCTOR: Initialize ROS2 interfaces and start grade processing pipeline
     * 
     * SETUP SEQUENCE:
     * 1. Create subscription for incoming exam results
     * 2. Create service client for grade calculations  
     * 3. Create publisher for exam generation control
     * 
     * NODE NAME: "final_cijfer_determinator" for ROS2 network identification
     */
    FinalCijferDeterminator() : Node("final_cijfer_determinator")
    {
        RCLCPP_INFO(this->get_logger(), "final_cijfer_determinator started!");
        
        // EXAM RESULT SUBSCRIPTION: Listen for individual exam scores
        // Topic: "tentamen_results" - receives exam data from generator nodes
        // Queue Size: 10 - buffers up to 10 messages to prevent loss during processing
        tentamen_sub_ = this->create_subscription<g1_interface_pkg::msg::Tentamen>(
            "tentamen_results", 10, std::bind(&FinalCijferDeterminator::tentamen_callback, this, std::placeholders::_1));
        
        // GRADE CALCULATION SERVICE CLIENT: Request final grade computations
        // Service: "calculate_final_cijfer" - communicates with cijfer_calculator node
        cijfer_client_ = this->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");
        
        // EXAM CONTROL PUBLISHER: Send stop commands to exam generators
        // Topic: "student_control" - controls exam generation pipeline
        // Queue Size: 10 - ensures control commands are delivered reliably
        student_control_pub_ = this->create_publisher<g1_interface_pkg::msg::Student>("student_control", 10);
    }

private:
    // EXAM SCORE AGGREGATION: Maps student/course pairs to their collected exam scores
    // KEY: StudentCourseKey (student_name + course_name combination)
    // VALUE: vector<int> containing all received exam scores for that combination
    // PURPOSE: Accumulates individual exam results until enough scores are collected (3 minimum)
    std::unordered_map<StudentCourseKey, std::vector<int>> tentamen_map_;
    
    // ROS2 INTERFACE HANDLES: Maintain connections to ROS2 communication channels
    rclcpp::Subscription<g1_interface_pkg::msg::Tentamen>::SharedPtr tentamen_sub_;      // Exam result subscription
    rclcpp::Client<g1_interface_pkg::srv::Tentamens>::SharedPtr cijfer_client_;         // Grade calculation service client
    rclcpp::Publisher<g1_interface_pkg::msg::Student>::SharedPtr student_control_pub_;  // Exam generation control publisher

    /**
     * EXAM RESULT CALLBACK: Process incoming individual exam scores
     * 
     * WORKFLOW:
     * 1. Extract student/course identification from message
     * 2. Add exam score to accumulation map for that combination
     * 3. Check if sufficient exams collected (3 minimum requirement)
     * 4. Trigger final grade calculation when threshold reached
     * 
     * BUSINESS RULE: 3 exams per course required for grade finalization
     * TRIGGER CONDITION: Initiates grade calculation pipeline when exam count >= 3
     */
    void tentamen_callback(const g1_interface_pkg::msg::Tentamen::SharedPtr msg)
    {
        // STEP 1: Create composite key for student/course combination
        StudentCourseKey key{msg->student_name, msg->course_name};
        
        // STEP 2: Add new exam score to collection for this student/course
        tentamen_map_[key].push_back(msg->tentamen_cijfer);

        RCLCPP_INFO(this->get_logger(), "Received exam: %s/%s %d", 
                   msg->student_name.c_str(), msg->course_name.c_str(), msg->tentamen_cijfer);

        // STEP 3: Check completion threshold (3 exams per course business rule)
        if (tentamen_map_[key].size() >= 3)
        {
            // STEP 4A: Prepare service request for final grade calculation
            auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
            request->student_name = key.student;           // Student identification
            request->course_name = key.course;             // Course identification  
            request->tentamen_cijfers = tentamen_map_[key]; // All collected exam scores

            // STEP 4B: Define asynchronous response handler using lambda
            // ASYNC PATTERN: Non-blocking service call to prevent node freezing
            // CAPTURE: [this, key] captures node context and student/course key for callback
            auto response_callback = [this, key](rclcpp::Client<g1_interface_pkg::srv::Tentamens>::SharedFuture result_future)
            {
                // PHASE 1: Extract calculated final grade from service response
                auto response = result_future.get();

                RCLCPP_INFO(this->get_logger(),
                            "Write to database: %s,%s,%zu,%d,%s",
                            key.student.c_str(),
                            key.course.c_str(),
                            tentamen_map_[key].size(),
                            response->final_cijfer,
                            std::to_string(this->now().seconds()).c_str());

                // PHASE 2: Establish database connection for final grade storage
                if (!Database::open())
                {
                    std::cerr << "Could not open database!\n";
                    return; // Exit callback if database connection fails
                }

                // PHASE 3: Prepare database record with finalized grade information
                StudentRecord record;
                record.student_name = key.student;                                    // Student identifier
                record.course = key.course;                                          // Course identifier
                record.number_of_exams = static_cast<int>(tentamen_map_[key].size()); // Total exams taken
                record.final_result = response->final_cijfer;                        // Calculated final grade
                record.timestamp = this->now().seconds();                           // Completion timestamp

                // PHASE 4: Persist final grade to PostgreSQL database
                if (!Database::insert(record))
                {
                    std::cerr << "Failed to insert record into database\n";
                    return; // Exit callback if database insertion fails
                }

                RCLCPP_INFO(this->get_logger(), "Final cijfer for %s/%s: %d", 
                           key.student.c_str(), key.course.c_str(), response->final_cijfer);

                // PHASE 5: Clean up completed entry from accumulation map
                // Removes student/course combination since processing is complete
                tentamen_map_.erase(key);

                // PHASE 6: Send stop command to halt further exam generation
                // CONTROL FLOW: Prevents unnecessary exam creation for completed courses
                g1_interface_pkg::msg::Student stop_msg;
                stop_msg.stamp = this->now();              // Command timestamp
                stop_msg.name = key.student;               // Target student
                stop_msg.course = key.course;              // Target course  
                stop_msg.command = "stop";                 // Stop exam generation command

                // Publish control message to exam generation pipeline
                student_control_pub_->publish(stop_msg);
                RCLCPP_INFO(this->get_logger(), "Sent stop command for %s/%s", 
                           key.student.c_str(), key.course.c_str());
            }; // End of response callback lambda

            // STEP 4C: Execute asynchronous service call with callback
            // NON-BLOCKING: Node continues processing other exams while waiting for response
            cijfer_client_->async_send_request(request, response_callback);
        }
        // NOTE: If < 3 exams collected, function returns and waits for more exam results
    }
}; // End of FinalCijferDeterminator class

/**
 * MAIN FUNCTION: Entry point for Final Grade Determinator ROS2 Node
 * 
 * EXECUTION FLOW:
 * 1. Initialize ROS2 system and node context
 * 2. Create and start FinalCijferDeterminator node instance  
 * 3. Enter event loop for continuous message processing
 * 4. Clean shutdown when terminated
 * 
 * NODE LIFECYCLE: Runs continuously until system shutdown or external termination
 * INTEGRATION: Central component in grade calculation pipeline architecture
 */
int main(int argc, char **argv)
{
    // PHASE 1: Initialize ROS2 runtime system
    rclcpp::init(argc, argv);
    
    // PHASE 2: Log node startup for system monitoring
    RCLCPP_INFO(rclcpp::get_logger("final_cijfer_determinator"), 
               "[!] Starting final_cijfer_determinator node");
    
    // PHASE 3: Create node instance and enter processing loop
    // SPIN PATTERN: Handles incoming messages, service responses, and callbacks
    rclcpp::spin(std::make_shared<FinalCijferDeterminator>());
    
    // PHASE 4: Clean shutdown when spin() returns
    rclcpp::shutdown();
    return 0; // Success exit code
}
// END OF FILE: Final Grade Determinator - Grade Processing Pipeline Controller
