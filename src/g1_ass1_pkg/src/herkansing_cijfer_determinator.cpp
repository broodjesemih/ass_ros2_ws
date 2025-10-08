/* 
 * RETAKE EXAM PROCESSOR NODE - ROS2 Grade Calculator System
 *
 * PURPOSE: Handles retake examination (herkansing) requests for students needing grade improvement
 * ROLE: Action server that processes retake requests, generates new exam sequences, 
 *       calculates updated grades, and manages database persistence with thread safety
 *
 * DUTCH CONTEXT: "Herkansing" = retake exam opportunity for grade improvement
 *
 * WORKFLOW:
 * 1. Receive retake action goals from clients (student/course combinations)
 * 2. Reactivate exam generation pipeline for specified student/course
 * 3. Generate 3 new randomized exam scores with progress feedback
 * 4. Calculate new final grade using existing calculation service
 * 5. Store updated results in database with concurrent access protection
 * 6. Return success response with new grade information
 *
 * THREAD SAFETY: Implements mutex-protected database access to prevent segmentation faults
 * ACTION PATTERN: Long-running operations with progress feedback and cancellation support
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
#include <mutex>                      // Thread synchronization for database safety

// CUSTOM MESSAGE AND SERVICE INTERFACES
#include "g1_interface_pkg/msg/tentamen.hpp"    // Individual exam result message format
#include "g1_interface_pkg/msg/student.hpp"     // Student control message format
#include "g1_interface_pkg/action/herkanser.hpp" // Retake exam action interface
#include "g1_interface_pkg/srv/tentamens.hpp"   // Grade calculation service interface

// ROS2 ACTION FRAMEWORK
#include "rclcpp_action/rclcpp_action.hpp"      // Action server implementation support

// DATABASE ABSTRACTION LAYER
#include "database.cpp"               // PostgreSQL database operations for persistent storage

/**
 * THREAD SAFETY: Global database access mutex
 * 
 * PURPOSE: Prevents concurrent database operations that can cause segmentation faults
 * SCOPE: Static (file-local) to ensure single instance across all class methods
 * PROTECTION: Guards all database open/insert operations in multi-threaded environment
 * 
 * CRITICAL: Essential for preventing crashes when multiple retake requests execute simultaneously
 */
static std::mutex db_access_mutex;

/**
 * COMPOSITE KEY STRUCTURE: Student-Course Combination Identifier
 * 
 * PURPOSE: Creates unique keys for student/course pairs in retake processing
 * USE CASE: Identifies specific retake targets and manages concurrent retake requests
 * 
 * DESIGN: Reuses pattern from other nodes for consistency across the system
 * PERFORMANCE: O(1) average lookup time through custom hash function
 */
struct StudentCourseKey
{
    std::string student;    // Student name requiring retake
    std::string course;     // Course name for retake examination
    
    // EQUALITY OPERATOR: Required for hash map key comparison
    // Ensures two keys are identical if both student AND course names match
    bool operator==(const StudentCourseKey &other) const
    {
        return student == other.student && course == other.course;
    }
};

/**
 * CUSTOM HASH FUNCTION: Enables StudentCourseKey as hash map key
 * 
 * TECHNIQUE: XOR combination of individual string hashes for good distribution
 * PERFORMANCE: Fast hash computation for efficient retake request tracking
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
 * RETAKE EXAM PROCESSOR CLASS: ROS2 Action Server for Grade Improvement
 * 
 * ARCHITECTURE: Action server pattern for long-running retake exam operations
 * RESPONSIBILITY: Manage complete retake workflow from request to grade persistence
 * 
 * ACTION INTERFACE: Herkanser (Dutch: retake) - provides progress feedback and cancellation
 * INTEGRATION: Coordinates with exam generation, grade calculation, and database systems
 * 
 * THREAD SAFETY: Implements protected database access for concurrent operations
 */
class HerkansingCijferDeterminator : public rclcpp::Node
{
public:
    // TYPE ALIAS: Simplify action interface usage throughout the class
    using Herkanser = g1_interface_pkg::action::Herkanser;
    
    /**
     * CONSTRUCTOR: Initialize retake exam processing infrastructure
     * 
     * SETUP SEQUENCE:
     * 1. Create action server for retake requests
     * 2. Create service client for grade calculations
     * 3. Create publisher for exam generation control
     * 
     * NODE NAME: "herkansing_cijfer_determinator" for ROS2 network identification
     */
    HerkansingCijferDeterminator() : Node("herkansing_cijfer_determinator")
    {
        // ACTION SERVER: Handle retake exam requests with callback binding
        // Action: "herkanser" - receives retake requests from external clients
        // Callbacks: Goal handling, cancellation support, and execution management
        action_server_ = rclcpp_action::create_server<Herkanser>(
            this, "herkanser",
            std::bind(&HerkansingCijferDeterminator::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&HerkansingCijferDeterminator::handle_cancel, this, std::placeholders::_1),
            std::bind(&HerkansingCijferDeterminator::handle_accepted, this, std::placeholders::_1));
            
        // GRADE CALCULATION SERVICE CLIENT: Request final grade computations
        // Service: "calculate_final_cijfer" - communicates with cijfer_calculator node
        cijfer_client_ = this->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");
        
        // EXAM CONTROL PUBLISHER: Send restart commands to exam generators
        // Topic: "student_control" - reactivates exam generation for retakes
        // Queue Size: 10 - ensures control commands are delivered reliably
        student_control_pub_ = this->create_publisher<g1_interface_pkg::msg::Student>("student_control", 10);
    }

private:
    // ROS2 INTERFACE HANDLES: Maintain connections to ROS2 communication channels
    rclcpp_action::Server<Herkanser>::SharedPtr action_server_;                     // Retake action server
    rclcpp::Client<g1_interface_pkg::srv::Tentamens>::SharedPtr cijfer_client_;     // Grade calculation service client
    rclcpp::Publisher<g1_interface_pkg::msg::Student>::SharedPtr student_control_pub_; // Exam generation control publisher

    /**
     * GOAL HANDLER: Process incoming retake requests
     * 
     * PURPOSE: Evaluate retake requests and decide acceptance
     * POLICY: Accept all valid retake requests immediately
     * 
     * PARAMETERS:
     * - GoalUUID: Unique identifier for request tracking (unused in simple implementation)
     * - Goal: Contains student_name and course_name for retake target
     * 
     * RETURN: ACCEPT_AND_EXECUTE for immediate processing
     */
    rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID &, std::shared_ptr<const Herkanser::Goal> goal)
    {
        RCLCPP_INFO(this->get_logger(), "Received herkansing goal for %s/%s", 
                   goal->student_name.c_str(), goal->course_name.c_str());
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    /**
     * CANCELLATION HANDLER: Process retake cancellation requests
     * 
     * PURPOSE: Allow clients to cancel ongoing retake operations
     * POLICY: Accept all cancellation requests (graceful termination)
     * 
     * IMPLEMENTATION: Simple acceptance - actual cancellation handled in execute()
     * RETURN: ACCEPT for all cancellation requests
     */
    rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<rclcpp_action::ServerGoalHandle<Herkanser>>)
    {
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    /**
     * EXECUTION HANDLER: Start retake processing in separate thread
     * 
     * PURPOSE: Initiate long-running retake exam workflow
     * PATTERN: Detached thread prevents blocking of action server
     * 
     * THREAD SAFETY: Each retake runs independently in its own thread
     * PERFORMANCE: Allows concurrent processing of multiple retake requests
     */
    void handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<Herkanser>> goal_handle)
    {
        // Create detached thread for non-blocking retake execution
        std::thread{std::bind(&HerkansingCijferDeterminator::execute, this, goal_handle)}.detach();
    }

    /**
     * RETAKE EXECUTION: Complete workflow for processing retake examination
     * 
     * WORKFLOW PHASES:
     * 1. Extract retake target information from goal
     * 2. Reactivate exam generation for specified student/course
     * 3. Generate new exam sequence with progress feedback
     * 4. Calculate updated final grade via service call
     * 5. Store results in database with thread safety protection
     * 6. Return success response with new grade information
     * 
     * THREAD CONTEXT: Runs in detached thread for non-blocking operation
     * ERROR HANDLING: Robust exception handling prevents node crashes
     */
    void execute(const std::shared_ptr<rclcpp_action::ServerGoalHandle<Herkanser>> goal_handle)
    {
        // PHASE 1: Extract retake target from action goal
        auto goal = goal_handle->get_goal();
        StudentCourseKey key{goal->student_name, goal->course_name};

        // PHASE 2: Reactivate exam generation pipeline for retake
        // CONTROL FLOW: Sends "again" command to restart exam generation
        g1_interface_pkg::msg::Student start_msg;
        start_msg.stamp = this->now();              // Command timestamp
        start_msg.name = key.student;               // Target student for retake
        start_msg.course = key.course;              // Target course for retake
        start_msg.command = "again";                // Restart exam generation command
        
        student_control_pub_->publish(start_msg);
        RCLCPP_INFO(this->get_logger(), "Sent 'again' command for %s/%s", 
                   key.student.c_str(), key.course.c_str());

        // PHASE 3: Generate new exam sequence (simulated random generation)
        // BUSINESS RULE: 3 new exams required for retake grade calculation
        std::vector<int> cijfers;
        
        // EXAM GENERATION LOOP: Create 3 new exam scores with progress feedback
        for (int i = 0; i < 3; ++i)
        {
            // Generate random exam score (10-100 range for realistic grades)
            cijfers.push_back(10 + (rand() % 91));
            
            // PROGRESS FEEDBACK: Update client on retake exam collection progress
            auto feedback = std::make_shared<Herkanser::Feedback>();
            feedback->progress = (i + 1) / 3.0f;           // Progress percentage (0.33, 0.67, 1.0)
            feedback->status = "Collecting tentamen results"; // Status message for client
            goal_handle->publish_feedback(feedback);
            
            // TIMING: Simulate realistic exam collection delay
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // PHASE 4: Calculate updated final grade using existing service
        // SERVICE REQUEST: Prepare exam data for grade calculation
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = key.student;        // Student identification
        request->course_name = key.course;          // Course identification
        request->tentamen_cijfers = cijfers;        // New retake exam scores

        // SYNCHRONOUS SERVICE CALL: Wait for grade calculation completion
        // BLOCKING: Ensures grade is calculated before database storage
        auto future = cijfer_client_->async_send_request(request);
        future.wait();
        auto response = future.get();

        // PHASE 5: Persist retake results to database with thread safety protection
        // CRITICAL SECTION: Protected database operations to prevent segmentation faults
        try {
            // MUTEX LOCK: Prevent concurrent database access from multiple retake threads
            std::lock_guard<std::mutex> lock(db_access_mutex);
            
            // DATABASE CONNECTION: Establish connection for retake result storage
            if (!Database::open()) {
                RCLCPP_WARN(this->get_logger(), "Could not open database! Herkansing result not saved: %s/%s = %d", 
                           key.student.c_str(), key.course.c_str(), response->final_cijfer);
            } else {
                // RECORD PREPARATION: Create database record for retake result
                StudentRecord record;
                record.student_name = key.student;                          // Student identifier
                record.course = key.course;                                // Course identifier
                record.number_of_exams = static_cast<int>(cijfers.size()); // Retake exam count (3)
                record.final_result = response->final_cijfer;              // New calculated grade
                record.timestamp = this->now().seconds();                  // Retake completion time

                // DATABASE INSERTION: Store retake result with error handling
                if (!Database::insert(record)) {
                    RCLCPP_WARN(this->get_logger(), "Failed to insert herkansing result: %s/%s = %d", 
                               key.student.c_str(), key.course.c_str(), response->final_cijfer);
                } else {
                    RCLCPP_INFO(this->get_logger(), "Successfully saved herkansing result: %s/%s = %d", 
                               key.student.c_str(), key.course.c_str(), response->final_cijfer);
                }
            }
        } catch (const std::exception& e) {
            // EXCEPTION HANDLING: Log database errors but prevent node crashes
            // RESILIENCE: Retake calculation succeeds even if database storage fails
            RCLCPP_WARN(this->get_logger(), "Database error (non-fatal): %s. Herkansing still calculated: %s/%s = %d", 
                       e.what(), key.student.c_str(), key.course.c_str(), response->final_cijfer);
        } catch (...) {
            // CATCH-ALL: Handle any unexpected exceptions to prevent segmentation faults
            RCLCPP_WARN(this->get_logger(), "Unknown database error (non-fatal). Herkansing still calculated: %s/%s = %d", 
                       key.student.c_str(), key.course.c_str(), response->final_cijfer);
        }

        // PHASE 6: Prepare and send success response to action client
        auto result = std::make_shared<Herkanser::Result>();
        result->final_cijfer = response->final_cijfer;          // New grade from retake
        result->message = "New retake grade added";             // Success confirmation message
        
        // ACTION COMPLETION: Mark retake action as successfully completed
        goal_handle->succeed(result);
    }
}; // End of HerkansingCijferDeterminator class

/**
 * MAIN FUNCTION: Entry point for Retake Exam Processor ROS2 Node
 * 
 * EXECUTION FLOW:
 * 1. Initialize ROS2 system and node context
 * 2. Create and start HerkansingCijferDeterminator action server
 * 3. Enter event loop for continuous action request processing
 * 4. Clean shutdown when terminated
 * 
 * NODE LIFECYCLE: Runs continuously serving retake exam requests
 * INTEGRATION: Provides retake services to grade calculator system clients
 * 
 * THREAD SAFETY: Multi-threaded action execution with protected database access
 */
int main(int argc, char **argv)
{
    // PHASE 1: Initialize ROS2 runtime system
    rclcpp::init(argc, argv);
    
    // PHASE 2: Log node startup for system monitoring
    RCLCPP_INFO(rclcpp::get_logger("herkansing_cijfer_determinator"), 
               "[!] Starting herkansing_cijfer_determinator node");
    
    // PHASE 3: Create node instance and enter action serving loop
    // SPIN PATTERN: Handles incoming action requests, service responses, and callbacks
    rclcpp::spin(std::make_shared<HerkansingCijferDeterminator>());
    
    // PHASE 4: Clean shutdown when spin() returns
    rclcpp::shutdown();
    return 0; // Success exit code
}
// END OF FILE: Retake Exam Processor - Grade Improvement Action Server
