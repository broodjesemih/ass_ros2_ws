#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <chrono>
#include <thread>
#include "g1_25_assign1_interfaces_pkg/msg/tentamen.hpp"
#include "g1_25_assign1_interfaces_pkg/msg/student.hpp"

/**
 * Unit tests for het Topic Communication systeem
 * 
 * These tests validate:
 * - Topic publishing/subscribing
 * - Message format correctheid
 * - Communication tussen nodes
 * - Message delivery reliability
 */

class TopicCommunicationTest : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        rclcpp::init(0, nullptr);
        test_node_ = rclcpp::Node::make_shared("test_topic_communication");
        
        // Setup publisher for tentamen results
        tentamen_pub_ = test_node_->create_publisher<g1_25_assign1_interfaces_pkg::msg::Tentamen>(
            "tentamen_results", 10);
        
        // Setup subscriber for student control
        student_control_pub_ = test_node_->create_publisher<g1_25_assign1_interfaces_pkg::msg::Student>(
            "student_control", 10);
        
        // Setup subscribers to receive messages
        tentamen_sub_ = test_node_->create_subscription<g1_25_assign1_interfaces_pkg::msg::Tentamen>(
            "tentamen_results", 10,
            [this](const g1_25_assign1_interfaces_pkg::msg::Tentamen::SharedPtr msg) {
                received_tentamen_msgs_.push_back(*msg);
            });
            
        student_control_sub_ = test_node_->create_subscription<g1_25_assign1_interfaces_pkg::msg::Student>(
            "student_control", 10,
            [this](const g1_25_assign1_interfaces_pkg::msg::Student::SharedPtr msg) {
                received_student_msgs_.push_back(*msg);
            });
        
        // Wait for topic discovery
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    void TearDown() override 
    {
        received_tentamen_msgs_.clear();
        received_student_msgs_.clear();
        rclcpp::shutdown();
    }

    // Helper function to messages te process
    void spin_for_messages(int expected_count, int timeout_ms = 2000)
    {
        auto start_time = std::chrono::steady_clock::now();
        while (received_tentamen_msgs_.size() + received_student_msgs_.size() < static_cast<size_t>(expected_count)) {
            rclcpp::spin_some(test_node_);
            
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start_time);
            if (elapsed.count() > timeout_ms) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    rclcpp::Node::SharedPtr test_node_;
    rclcpp::Publisher<g1_25_assign1_interfaces_pkg::msg::Tentamen>::SharedPtr tentamen_pub_;
    rclcpp::Publisher<g1_25_assign1_interfaces_pkg::msg::Student>::SharedPtr student_control_pub_;
    rclcpp::Subscription<g1_25_assign1_interfaces_pkg::msg::Tentamen>::SharedPtr tentamen_sub_;
    rclcpp::Subscription<g1_25_assign1_interfaces_pkg::msg::Student>::SharedPtr student_control_sub_;
    
    std::vector<g1_25_assign1_interfaces_pkg::msg::Tentamen> received_tentamen_msgs_;
    std::vector<g1_25_assign1_interfaces_pkg::msg::Student> received_student_msgs_;
};

/**
 * Test 1: Tentamen message publishing en receiving
 * Validates that tentamen messages are sent and received correctly
 */
TEST_F(TopicCommunicationTest, TestTentamenMessagePublishing)
{
    // Create a test tentamen message
    g1_25_assign1_interfaces_pkg::msg::Tentamen test_msg;
    test_msg.student_name = "Test Student";
    test_msg.course_name = "Math";
    test_msg.tentamen_cijfer = 85;
    test_msg.stamp = test_node_->now();
    
    // Publish het message
    tentamen_pub_->publish(test_msg);
    
    // Wait for reception
    spin_for_messages(1);
    
    // Verify that message is received
    ASSERT_EQ(received_tentamen_msgs_.size(), 1) << "Tentamen message not received";
    
    auto& received = received_tentamen_msgs_[0];
    EXPECT_EQ(received.student_name, "Test Student");
    EXPECT_EQ(received.course_name, "Math");
    EXPECT_EQ(received.tentamen_cijfer, 85);
}

/**
 * Test 2: Student control message publishing
 * Test student control messages for retake system
 */
TEST_F(TopicCommunicationTest, TestStudentControlMessage)
{
    g1_25_assign1_interfaces_pkg::msg::Student control_msg;
    control_msg.name = "Wessel Tip";
    control_msg.course = "ROS2";
    control_msg.command = "again";
    control_msg.stamp = test_node_->now();
    
    student_control_pub_->publish(control_msg);
    
    spin_for_messages(1);
    
    ASSERT_EQ(received_student_msgs_.size(), 1) << "Student control message not received";
    
    auto& received = received_student_msgs_[0];
    EXPECT_EQ(received.name, "Wessel Tip");
    EXPECT_EQ(received.course, "ROS2");  
    EXPECT_EQ(received.command, "again");
}

/**
 * Test 3: Multiple message publishing
 * Test batch of messages for different students
 */
TEST_F(TopicCommunicationTest, TestMultipleMessagePublishing)
{
    std::vector<std::string> students = {"Student1", "Student2", "Wessel Tip"};
    std::vector<std::string> courses = {"Math", "Physics", "ROS2"};
    std::vector<int> grades = {75, 80, 90};
    
    // Publish meerdere tentamen messages
        for (size_t i = 0; i < students.size(); ++i) {
            g1_25_assign1_interfaces_pkg::msg::Tentamen msg;
            msg.student_name = students[i];
            msg.course_name = courses[i];
            msg.tentamen_cijfer = grades[i];
            msg.stamp = test_node_->now();        tentamen_pub_->publish(msg);
        // Small delay between messages
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    spin_for_messages(3);
    
    ASSERT_EQ(received_tentamen_msgs_.size(), 3) << "Not all messages received";
    
    // Verify that alle messages are correct
    for (size_t i = 0; i < received_tentamen_msgs_.size(); ++i) {
        bool found = false;
        for (size_t j = 0; j < students.size(); ++j) {
            if (received_tentamen_msgs_[i].student_name == students[j] &&
                received_tentamen_msgs_[i].course_name == courses[j] &&
                received_tentamen_msgs_[i].tentamen_cijfer == grades[j]) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found) << "Message " << i << " does not match expected data";
    }
}

/**
 * Test 4: Message field validation
 * Test that all vereiste velden correct worden doorgegeven
 */
TEST_F(TopicCommunicationTest, TestMessageFieldValidation)
{
    // Test tentamen message with all fields filled
    g1_25_assign1_interfaces_pkg::msg::Tentamen full_msg;
    full_msg.student_name = "Complete Student";
    full_msg.course_name = "Complete Course";
    full_msg.tentamen_cijfer = 95;
    full_msg.stamp = test_node_->now();
    
    tentamen_pub_->publish(full_msg);
    spin_for_messages(1);
    
    ASSERT_EQ(received_tentamen_msgs_.size(), 1);
    auto& received = received_tentamen_msgs_[0];
    
    // Verify that all fields have been preserved
    EXPECT_FALSE(received.student_name.empty()) << "Student name may not be empty";
    EXPECT_FALSE(received.course_name.empty()) << "Course name may not be empty";
    EXPECT_GT(received.tentamen_cijfer, 0) << "Tentamen cijfer must be positive";
    
    // Verify that timestamp reasonable is (not too far in verleden/toekomst)
    auto now = test_node_->now();
    auto time_diff = now.seconds() - received.stamp.sec;
    EXPECT_LT(abs(time_diff), 5.0) << "Timestamp difference too large";
}

/**
 * Test 5: High frequency message publishing
 * Test systeem performance bij many messages
 */
TEST_F(TopicCommunicationTest, TestHighFrequencyPublishing)
{
    const int message_count = 50;
    
    // Publish many messages in short time
        for (int i = 0; i < message_count; ++i) {
            g1_25_assign1_interfaces_pkg::msg::Tentamen msg;
            msg.student_name = "Student_" + std::to_string(i);
            msg.course_name = "Course_" + std::to_string(i % 5);
            msg.tentamen_cijfer = 50 + (i % 50);
            msg.stamp = test_node_->now();        tentamen_pub_->publish(msg);
    }
    
    // Give the system time to process all messages
    spin_for_messages(message_count, 5000); // 5 seconden timeout
    
    // We expect that at least some messages arrive (realistic for test environment)
    EXPECT_GE(received_tentamen_msgs_.size(), static_cast<size_t>(5)) 
        << "Less than 5 messages received at high frequency (received: " << received_tentamen_msgs_.size() << ")";
}

/**
 * Test 6: Edge cases - lege en speciale tekens
 * Test handling of edge case input
 */
TEST_F(TopicCommunicationTest, TestEdgeCaseMessages)
{
    std::vector<std::pair<std::string, std::string>> edge_cases = {
        {"", "EmptyCourse"},                    // Empty student name
        {"EmptyStudent", ""},                   // Empty course name
        {"Special!@#$%", "Chars&*()"},         // Special characters
        {"VeryLongStudentNameThatExceedsNormalLimits", "VeryLongCourseNameForTesting"}, // Long names
        {"Üñíçødé Tëst", "Çöürsé Nämé"}       // Unicode characters
    };
    
        for (size_t i = 0; i < edge_cases.size(); ++i) {
            g1_25_assign1_interfaces_pkg::msg::Tentamen msg;
            msg.student_name = edge_cases[i].first;
            msg.course_name = edge_cases[i].second;
            msg.tentamen_cijfer = 75;
            msg.stamp = test_node_->now();        tentamen_pub_->publish(msg);
    }
    
    spin_for_messages(edge_cases.size(), 3000);
    
    // Systeem should handle edge cases without crashes
    EXPECT_EQ(received_tentamen_msgs_.size(), edge_cases.size()) 
        << "Niet alle edge case messages correctly processed";
}

// Test runner
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
