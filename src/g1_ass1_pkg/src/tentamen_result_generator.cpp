/* 
 * EXAM RESULT GENERATOR NODE - ROS2 Grade Calculator System
 *
 * PURPOSE: Simulates continuous exam result generation for students in active courses
 * ROLE: Data source node that feeds the grade calculation pipeline with realistic exam scores
 *
 * DUTCH CONTEXT: "Tentamen" = examination/test in Dutch academic terminology
 *
 * WORKFLOW:
 * 1. Load incomplete student/course combinations from database at startup
 * 2. Continuously generate random exam results for active combinations
 * 3. Respond to control commands (stop/resume generation for specific students)
 * 4. Publish exam results to grade processing pipeline
 * 5. Manage active student/course combinations dynamically
 *
 * SIMULATION FEATURES:
 * - Random score generation (10-100 range for realistic grades)
 * - Timer-based periodic result publishing (2-second intervals)
 * - Dynamic control via student_control topic commands
 * - Database-driven initialization of active combinations
 *
 * INTEGRATION: Publisher to final_cijfer_determinator for grade aggregation
 *
 * Coded by: Semih, Nout, Tyhco
 * Last modified: October 9, 2025
 */

// CORE ROS2 DEPENDENCIES
#include <rclcpp/rclcpp.hpp>           // ROS2 C++ client library for node functionality
#include <fstream>                    // File I/O operations (currently unused)
#include <random>                     // Random number generation for exam scores
#include <chrono>                     // Time utilities for timer operations
#include <unordered_set>              // STL unordered set for active combination tracking

// CUSTOM MESSAGE INTERFACES
#include "g1_interface_pkg/msg/tentamen.hpp"    // Exam result message format
#include "g1_interface_pkg/msg/student.hpp"     // Student control message format

// DATABASE ABSTRACTION LAYER
#include "database.cpp"               // PostgreSQL database operations for student data loading

/**
 * COMPOSITE KEY STRUCTURE: Student-Course Combination Identifier
 * 
 * PURPOSE: Creates unique identifiers for active student/course pairs in exam generation
 * USE CASE: Manages which student/course combinations should receive generated exam results
 * 
 * DESIGN: Enables efficient tracking in unordered_set containers
 * PERFORMANCE: O(1) average lookup time through custom hash function implementation
 */
struct StudentCourseKey
{
    std::string student;    // Student name identifier
    std::string course;     // Course name identifier
    
    // EQUALITY OPERATOR: Required for unordered_set key comparison
    // Ensures two keys are identical if both student AND course names match
    bool operator==(const StudentCourseKey &other) const
    {
        return student == other.student && course == other.course;
    }
};

/**
 * CUSTOM HASH FUNCTION: Enables StudentCourseKey as unordered_set element
 * 
 * TECHNIQUE: XOR combination of individual string hashes for good distribution
 * PERFORMANCE: Fast hash computation for efficient set operations
 * STD NAMESPACE: Required specialization for std::unordered_set compatibility
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
 * EXAM RESULT GENERATOR CLASS: Simulated Exam Score Production System
 * 
 * ARCHITECTURE: Timer-driven publisher with dynamic control capability
 * RESPONSIBILITY: Generate realistic exam results for grade calculation pipeline
 * 
 * SIMULATION STRATEGY: Random score generation for active student/course combinations
 * CONTROL INTERFACE: Responds to external start/stop commands for targeted generation
 * 
 * INTEGRATION: Data source for grade aggregation and calculation systems
 */
class TentamenResultGenerator : public rclcpp::Node
{
public:
    /**
     * CONSTRUCTOR: Initialize exam result generation infrastructure
     * 
     * SETUP SEQUENCE:
     * 1. Create publisher for exam result distribution
     * 2. Create subscriber for generation control commands
     * 3. Create periodic timer for continuous result generation
     * 4. Load active student/course combinations from database
     * 
     * NODE NAME: "tentamen_result_generator" for ROS2 network identification
     * TIMING: 2-second intervals for realistic exam result frequency
     */
    TentamenResultGenerator() : Node("tentamen_result_generator")
    {
        // EXAM RESULT PUBLISHER: Distribute generated exam scores
        // Topic: "tentamen_results" - feeds grade calculation pipeline
        // Queue Size: 10 - buffers exam results to prevent loss during processing
        publisher_ = this->create_publisher<g1_interface_pkg::msg::Tentamen>("tentamen_results", 10);
        
        // CONTROL SUBSCRIBER: Listen for generation start/stop commands
        // Topic: "student_control" - receives commands from grade processors
        // Queue Size: 10 - ensures control commands are processed reliably
        student_control_sub_ = this->create_subscription<g1_interface_pkg::msg::Student>(
            "student_control", 10,
            std::bind(&TentamenResultGenerator::student_control_callback, this, std::placeholders::_1));
            
        // GENERATION TIMER: Periodic exam result creation
        // Frequency: 2 seconds - balanced between activity and system load
        // Callback: publish_random_result() - generates and publishes exam scores
        timer_ = this->create_wall_timer(
            std::chrono::seconds(2),
            std::bind(&TentamenResultGenerator::publish_random_result, this));
            
        // INITIALIZATION: Load active student/course combinations from database
        load_student_course_combinations();
    }


private:
    // ACTIVE COMBINATION TRACKING: Set of student/course pairs requiring exam generation
    // PURPOSE: Determines which combinations should receive generated exam results
    // DYNAMIC: Updated via control commands (add/remove combinations as needed)
    // PERFORMANCE: Unordered set for O(1) average lookup and modification operations
    std::unordered_set<StudentCourseKey> active_combinations_;
    
    // ROS2 INTERFACE HANDLES: Maintain connections to ROS2 communication channels
    rclcpp::Publisher<g1_interface_pkg::msg::Tentamen>::SharedPtr publisher_;        // Exam result publisher
    rclcpp::Subscription<g1_interface_pkg::msg::Student>::SharedPtr student_control_sub_; // Control command subscriber
    rclcpp::TimerBase::SharedPtr timer_;                                           // Periodic generation timer

    /**
     * INITIALIZATION: Load active student/course combinations from database
     * 
     * PURPOSE: Populate initial set of combinations requiring exam generation
     * DATA SOURCE: Database records without final results (incomplete courses)
     * 
     * WORKFLOW:
     * 1. Establish database connection for data retrieval
     * 2. Query for incomplete student records (NULL final_result)
     * 3. Extract student/course pairs and add to active set
     * 
     * BUSINESS LOGIC: Only generate exams for students with incomplete courses
     * ERROR HANDLING: Graceful database connection failure (continues with empty set)
     */
    void load_student_course_combinations()
    {
        // DATABASE CONNECTION: Establish connection for initial data loading
        if (!Database::open())
        {
            std::cerr << "Could not open database!\n";
            return; // Continue with empty active set if database unavailable
        }

        // DATA RETRIEVAL: Get all incomplete student records from database
        // FILTER: getWithoutFinalResult() returns only records needing more exams
        auto records = Database::getWithoutFinalResult();
        
        // POPULATION: Add each incomplete student/course pair to active generation set
        for (const auto &r : records)
        {
            active_combinations_.insert(StudentCourseKey{r.student_name, r.course});
        }
    }

    /**
     * EXAM GENERATION: Create and publish random exam result
     * 
     * SELECTION STRATEGY: Random selection from active student/course combinations
     * SCORE GENERATION: Random grades in 10-100 range for realistic distribution
     * 
     * WORKFLOW:
     * 1. Check if any active combinations exist for generation
     * 2. Randomly select one student/course combination
     * 3. Generate random exam score in valid range
     * 4. Create and publish exam result message
     * 
     * TIMING: Called every 2 seconds by timer callback
     * BUSINESS RULE: Only generates for currently active combinations
     */
    void publish_random_result()
    {
        // AVAILABILITY CHECK: Ensure active combinations exist for generation
        if (active_combinations_.empty())
            return; // No active combinations - skip generation cycle
            
        // RANDOM SELECTION: Choose student/course combination for exam generation
        auto it = active_combinations_.begin();
        std::advance(it, rand() % active_combinations_.size()); // Random iterator position
        auto key = *it; // Selected student/course combination

        // EXAM MESSAGE CREATION: Prepare exam result for publication
        g1_interface_pkg::msg::Tentamen msg;
        msg.stamp = this->now();                              // Exam timestamp
        msg.student_name = key.student;                       // Student taking exam
        msg.course_name = key.course;                         // Course for exam
        msg.tentamen_cijfer = 10 + (rand() % 91);             // Random score (10-100 range)

        // PUBLICATION: Send exam result to grade processing pipeline
        publisher_->publish(msg);
        RCLCPP_INFO(this->get_logger(), "Published tentamen for %s/%s: %d", 
                   key.student.c_str(), key.course.c_str(), msg.tentamen_cijfer);
    }

    /**
     * CONTROL CALLBACK: Process generation control commands
     * 
     * PURPOSE: Dynamically manage which student/course combinations receive exam generation
     * COMMANDS: "stop" (cease generation) and "again" (resume/start generation)
     * 
     * WORKFLOW:
     * 1. Extract student/course identification from control message
     * 2. Execute appropriate action based on command type
     * 3. Update active combinations set accordingly
     * 4. Log control action for system monitoring
     * 
     * INTEGRATION: Receives commands from grade processors and retake schedulers
     * REAL-TIME: Immediate response to control commands for dynamic pipeline management
     */
    void student_control_callback(const g1_interface_pkg::msg::Student::SharedPtr msg)
    {
        // IDENTIFICATION: Create key for targeted student/course combination
        StudentCourseKey key{msg->name, msg->course};
        
        // COMMAND PROCESSING: Execute appropriate control action
        if (msg->command == "stop")
        {
            // STOP COMMAND: Remove combination from active generation set
            // USE CASE: Student completed course or failed too many times
            active_combinations_.erase(key);
            RCLCPP_INFO(this->get_logger(), "Stopped generating for %s/%s", 
                       msg->name.c_str(), msg->course.c_str());
        }
        else if (msg->command == "again")
        {
            // RESUME COMMAND: Add combination back to active generation set
            // USE CASE: Retake exam opportunity or reactivation after pause
            active_combinations_.insert(key);
            RCLCPP_INFO(this->get_logger(), "Resumed generating for %s/%s", 
                       msg->name.c_str(), msg->course.c_str());
        }
        // NOTE: Unknown commands are silently ignored for system robustness
    }
}; // End of TentamenResultGenerator class

/**
 * MAIN FUNCTION: Entry point for Exam Result Generator ROS2 Node
 * 
 * EXECUTION FLOW:
 * 1. Initialize ROS2 system and node context
 * 2. Create and start TentamenResultGenerator simulation system
 * 3. Enter event loop for continuous exam result generation
 * 4. Clean shutdown when terminated
 * 
 * NODE LIFECYCLE: Runs continuously generating simulated exam results
 * INTEGRATION: Primary data source for grade calculation pipeline
 * 
 * SIMULATION MODE: Provides realistic exam data flow for system testing and demonstration
 * BUSINESS VALUE: Enables continuous operation of grade calculation system without manual input
 */
int main(int argc, char **argv)
{
    // PHASE 1: Initialize ROS2 runtime system
    rclcpp::init(argc, argv);
    
    // PHASE 2: Log node startup for system monitoring
    RCLCPP_INFO(rclcpp::get_logger("tentamen_result_generator"), 
               "[!] Starting tentamen_result_generator node");
    
    // PHASE 3: Create node instance and enter generation loop
    // SPIN PATTERN: Handles timer callbacks, control messages, and publications
    rclcpp::spin(std::make_shared<TentamenResultGenerator>());
    
    // PHASE 4: Clean shutdown when spin() returns
    rclcpp::shutdown();
    return 0; // Success exit code
}
// END OF FILE: Exam Result Generator - Simulated Exam Data Source for Grade Pipeline
