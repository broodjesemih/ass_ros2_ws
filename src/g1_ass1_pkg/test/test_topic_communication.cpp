#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <chrono>
#include <thread>
#include "g1_interface_pkg/msg/tentamen.hpp"
#include "g1_interface_pkg/msg/student.hpp"

/**
 * Unit tests voor het Topic Communication systeem
 * 
 * Deze tests valideren:
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
        
        // Setup publisher voor tentamen results
        tentamen_pub_ = test_node_->create_publisher<g1_interface_pkg::msg::Tentamen>(
            "tentamen_results", 10);
        
        // Setup subscriber voor student control
        student_control_pub_ = test_node_->create_publisher<g1_interface_pkg::msg::Student>(
            "student_control", 10);
        
        // Setup subscribers om berichten te ontvangen
        tentamen_sub_ = test_node_->create_subscription<g1_interface_pkg::msg::Tentamen>(
            "tentamen_results", 10,
            [this](const g1_interface_pkg::msg::Tentamen::SharedPtr msg) {
                received_tentamen_msgs_.push_back(*msg);
            });
            
        student_control_sub_ = test_node_->create_subscription<g1_interface_pkg::msg::Student>(
            "student_control", 10,
            [this](const g1_interface_pkg::msg::Student::SharedPtr msg) {
                received_student_msgs_.push_back(*msg);
            });
        
        // Wacht even voor topic discovery
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    void TearDown() override 
    {
        received_tentamen_msgs_.clear();
        received_student_msgs_.clear();
        rclcpp::shutdown();
    }

    // Helper functie om berichten te verwerken
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
    rclcpp::Publisher<g1_interface_pkg::msg::Tentamen>::SharedPtr tentamen_pub_;
    rclcpp::Publisher<g1_interface_pkg::msg::Student>::SharedPtr student_control_pub_;
    rclcpp::Subscription<g1_interface_pkg::msg::Tentamen>::SharedPtr tentamen_sub_;
    rclcpp::Subscription<g1_interface_pkg::msg::Student>::SharedPtr student_control_sub_;
    
    std::vector<g1_interface_pkg::msg::Tentamen> received_tentamen_msgs_;
    std::vector<g1_interface_pkg::msg::Student> received_student_msgs_;
};

/**
 * Test 1: Tentamen message publishing en receiving
 * Valideert dat tentamen berichten correct worden verstuurd en ontvangen
 */
TEST_F(TopicCommunicationTest, TestTentamenMessagePublishing)
{
    // Maak een test tentamen message
    g1_interface_pkg::msg::Tentamen test_msg;
    test_msg.student_name = "Test Student";
    test_msg.course_name = "Math";
    test_msg.tentamen_cijfer = 85;
    test_msg.stamp = test_node_->now();
    
    // Publish het bericht
    tentamen_pub_->publish(test_msg);
    
    // Wacht op ontvangst
    spin_for_messages(1);
    
    // Verificeer dat bericht is ontvangen
    ASSERT_EQ(received_tentamen_msgs_.size(), 1) << "Tentamen message niet ontvangen";
    
    auto& received = received_tentamen_msgs_[0];
    EXPECT_EQ(received.student_name, "Test Student");
    EXPECT_EQ(received.course_name, "Math");
    EXPECT_EQ(received.tentamen_cijfer, 85);
}

/**
 * Test 2: Student control message publishing
 * Test student control berichten voor herkansing systeem
 */
TEST_F(TopicCommunicationTest, TestStudentControlMessage)
{
    g1_interface_pkg::msg::Student control_msg;
    control_msg.name = "Wessel Tip";
    control_msg.course = "ROS2";
    control_msg.command = "again";
    control_msg.stamp = test_node_->now();
    
    student_control_pub_->publish(control_msg);
    
    spin_for_messages(1);
    
    ASSERT_EQ(received_student_msgs_.size(), 1) << "Student control message niet ontvangen";
    
    auto& received = received_student_msgs_[0];
    EXPECT_EQ(received.name, "Wessel Tip");
    EXPECT_EQ(received.course, "ROS2");  
    EXPECT_EQ(received.command, "again");
}

/**
 * Test 3: Multiple message publishing
 * Test batch van berichten voor verschillende studenten
 */
TEST_F(TopicCommunicationTest, TestMultipleMessagePublishing)
{
    std::vector<std::string> students = {"Student1", "Student2", "Wessel Tip"};
    std::vector<std::string> courses = {"Math", "Physics", "ROS2"};
    std::vector<int> grades = {75, 80, 90};
    
    // Publish meerdere tentamen berichten
        for (size_t i = 0; i < students.size(); ++i) {
            g1_interface_pkg::msg::Tentamen msg;
            msg.student_name = students[i];
            msg.course_name = courses[i];
            msg.tentamen_cijfer = grades[i];
            msg.stamp = test_node_->now();        tentamen_pub_->publish(msg);
        // Kleine delay tussen berichten
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    spin_for_messages(3);
    
    ASSERT_EQ(received_tentamen_msgs_.size(), 3) << "Niet alle berichten ontvangen";
    
    // Verificeer dat alle berichten correct zijn
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
        EXPECT_TRUE(found) << "Bericht " << i << " komt niet overeen met verwachte data";
    }
}

/**
 * Test 4: Message field validation
 * Test dat alle vereiste velden correct worden doorgegeven
 */
TEST_F(TopicCommunicationTest, TestMessageFieldValidation)
{
    // Test tentamen message met alle velden gevuld
    g1_interface_pkg::msg::Tentamen full_msg;
    full_msg.student_name = "Complete Student";
    full_msg.course_name = "Complete Course";
    full_msg.tentamen_cijfer = 95;
    full_msg.stamp = test_node_->now();
    
    tentamen_pub_->publish(full_msg);
    spin_for_messages(1);
    
    ASSERT_EQ(received_tentamen_msgs_.size(), 1);
    auto& received = received_tentamen_msgs_[0];
    
    // Verificeer dat alle velden behouden zijn gebleven
    EXPECT_FALSE(received.student_name.empty()) << "Student name mag niet leeg zijn";
    EXPECT_FALSE(received.course_name.empty()) << "Course name mag niet leeg zijn";
    EXPECT_GT(received.tentamen_cijfer, 0) << "Tentamen cijfer moet positief zijn";
    
    // Verificeer dat timestamp redelijk is (niet te ver in verleden/toekomst)
    auto now = test_node_->now();
    auto time_diff = now.seconds() - received.stamp.sec;
    EXPECT_LT(abs(time_diff), 5.0) << "Timestamp verschil te groot";
}

/**
 * Test 5: High frequency message publishing
 * Test systeem performance bij veel berichten
 */
TEST_F(TopicCommunicationTest, TestHighFrequencyPublishing)
{
    const int message_count = 50;
    
    // Publish veel berichten in korte tijd
        for (int i = 0; i < message_count; ++i) {
            g1_interface_pkg::msg::Tentamen msg;
            msg.student_name = "Student_" + std::to_string(i);
            msg.course_name = "Course_" + std::to_string(i % 5);
            msg.tentamen_cijfer = 50 + (i % 50);
            msg.stamp = test_node_->now();        tentamen_pub_->publish(msg);
    }
    
    // Geef het systeem tijd om alle berichten te verwerken
    spin_for_messages(message_count, 5000); // 5 seconden timeout
    
    // We verwachten dat minimaal enkele berichten aankomen (realistisch voor test environment)
    EXPECT_GE(received_tentamen_msgs_.size(), static_cast<size_t>(5)) 
        << "Minder dan 5 berichten ontvangen bij hoge frequentie (ontvangen: " << received_tentamen_msgs_.size() << ")";
}

/**
 * Test 6: Edge cases - lege en speciale tekens
 * Test handling van edge case input
 */
TEST_F(TopicCommunicationTest, TestEdgeCaseMessages)
{
    std::vector<std::pair<std::string, std::string>> edge_cases = {
        {"", "EmptyCourse"},                    // Lege student naam
        {"EmptyStudent", ""},                   // Lege course naam
        {"Special!@#$%", "Chars&*()"},         // Speciale tekens
        {"VeryLongStudentNameThatExceedsNormalLimits", "VeryLongCourseNameForTesting"}, // Lange namen
        {"Üñíçødé Tëst", "Çöürsé Nämé"}       // Unicode characters
    };
    
        for (size_t i = 0; i < edge_cases.size(); ++i) {
            g1_interface_pkg::msg::Tentamen msg;
            msg.student_name = edge_cases[i].first;
            msg.course_name = edge_cases[i].second;
            msg.tentamen_cijfer = 75;
            msg.stamp = test_node_->now();        tentamen_pub_->publish(msg);
    }
    
    spin_for_messages(edge_cases.size(), 3000);
    
    // Systeem zou moeten omgaan met edge cases zonder crashes
    EXPECT_EQ(received_tentamen_msgs_.size(), edge_cases.size()) 
        << "Niet alle edge case berichten correct verwerkt";
}

// Test runner
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
