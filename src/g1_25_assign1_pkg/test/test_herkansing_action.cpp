#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <memory>
#include <chrono>
#include <future>
#include "g1_25_assign1_interfaces_pkg/action/herkanser.hpp"

/**
 * Unit tests for de Herkansing Action Server
 * 
 * These tests validate:
 * - Action server goal handling
 * - Feedback publishing tijdens action
 * - Result correctheid na completion
 * - Cancel functionaliteit
 * - Error handling en timeouts
 */

class HerkansingActionTest : public ::testing::Test 
{
protected:
    using HerkanserAction = g1_25_assign1_interfaces_pkg::action::Herkanser;
    using GoalHandleHerkanser = rclcpp_action::ClientGoalHandle<HerkanserAction>;

    void SetUp() override 
    {
        rclcpp::init(0, nullptr);
        test_node_ = rclcpp::Node::make_shared("test_herkansing_action");
        
        // Maak action client
        action_client_ = rclcpp_action::create_client<HerkanserAction>(
            test_node_, "herkanser");
        
        // Wacht tot action server beschikbaar is
        bool server_available = action_client_->wait_for_action_server(std::chrono::seconds(10));
        ASSERT_TRUE(server_available) << "Herkansing action server niet beschikbaar binnen 10 seconden";
        
        // Reset feedback tracking
        received_feedback_.clear();
    }

    void TearDown() override 
    {
        rclcpp::shutdown();
    }

    // Helper function to action goal te versturen
    std::shared_ptr<GoalHandleHerkanser> send_goal(
        const std::string& student_name,
        const std::string& course_name)
    {
        auto goal_msg = HerkanserAction::Goal();
        goal_msg.student_name = student_name;
        goal_msg.course_name = course_name;
        
        auto send_goal_options = rclcpp_action::Client<HerkanserAction>::SendGoalOptions();
        
        // Setup feedback callback
        send_goal_options.feedback_callback = 
            [this](GoalHandleHerkanser::SharedPtr, const std::shared_ptr<const HerkanserAction::Feedback> feedback) {
                received_feedback_.push_back(*feedback);
            };
        
        // Setup result callback
        send_goal_options.result_callback = 
            [this](const GoalHandleHerkanser::WrappedResult & result) {
                last_result_ = result;
            };
        
        auto goal_handle_future = action_client_->async_send_goal(goal_msg, send_goal_options);
        
        // Wait for goal acceptance
        if (rclcpp::spin_until_future_complete(test_node_, goal_handle_future, std::chrono::seconds(5)) == 
            rclcpp::FutureReturnCode::SUCCESS) {
            return goal_handle_future.get();
        }
        return nullptr;
    }

    rclcpp::Node::SharedPtr test_node_;
    rclcpp_action::Client<HerkanserAction>::SharedPtr action_client_;
    std::vector<HerkanserAction::Feedback> received_feedback_;
    GoalHandleHerkanser::WrappedResult last_result_;
};

/**
 * Test 1: Basis herkansing action flow
 * Send goal and wait for successful completion
 */
TEST_F(HerkansingActionTest, TestBasicHerkansingFlow)
{
    auto goal_handle = send_goal("Test Student", "Math");
    ASSERT_NE(goal_handle, nullptr) << "Goal werd niet geaccepteerd door action server";
    ASSERT_NE(goal_handle, nullptr) << "Goal should be accepted";
    
    // Wait for completion (herkansing duurt normaal ~3 seconden)
    auto result_future = action_client_->async_get_result(goal_handle);
    auto status = rclcpp::spin_until_future_complete(test_node_, result_future, std::chrono::seconds(10));
    
    ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS) << "Action completion timeout";
    
    auto wrapped_result = result_future.get();
    EXPECT_EQ(wrapped_result.code, rclcpp_action::ResultCode::SUCCEEDED) << "Action should succeed";
    
    auto result = wrapped_result.result;
    ASSERT_NE(result, nullptr) << "Result should not be null";
    
    // Verify result fields
    EXPECT_GE(result->final_cijfer, 10) << "Final cijfer should be at least 10";
    EXPECT_LE(result->final_cijfer, 100) << "Final cijfer should be at most 100";
    EXPECT_FALSE(result->message.empty()) << "Result message should not be empty";
}

/**
 * Test 2: Feedback tijdens action execution
 * Verify that feedback is published during execution
 */
TEST_F(HerkansingActionTest, TestFeedbackDuringExecution)
{
    auto goal_handle = send_goal("Feedback Student", "Physics");
    ASSERT_NE(goal_handle, nullptr);
    
    // Wait for completion
    auto result_future = action_client_->async_get_result(goal_handle);
    rclcpp::spin_until_future_complete(test_node_, result_future, std::chrono::seconds(10));
    
    // Verify that we feedback hebben received
    EXPECT_GT(received_feedback_.size(), 0) << "Should receive feedback during action execution";
    
    // Feedback should show progress
    for (const auto& feedback : received_feedback_) {
        EXPECT_GE(feedback.progress, 0.0f) << "Progress should be non-negative";
        EXPECT_LE(feedback.progress, 1.0f) << "Progress should not exceed 1.0";
        EXPECT_FALSE(feedback.status.empty()) << "Status message should not be empty";
    }
    
    // Progress should increase over time (laatste feedback moet hoger zijn dan eerste)
    if (received_feedback_.size() > 1) {
        EXPECT_GE(received_feedback_.back().progress, received_feedback_.front().progress)
            << "Progress should increase over time";
    }
}

/**
 * Test 3: Wessel Tip herkansing
 * Test speciale behandeling for Wessel (met bonus)
 */
TEST_F(HerkansingActionTest, TestWesselHerkansing)
{
    auto goal_handle = send_goal("Wessel Tip", "ROS2");
    ASSERT_NE(goal_handle, nullptr);
    
    auto result_future = action_client_->async_get_result(goal_handle);
    auto status = rclcpp::spin_until_future_complete(test_node_, result_future, std::chrono::seconds(10));
    
    ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS);
    
    auto wrapped_result = result_future.get();
    auto result = wrapped_result.result;
    
    // Wessel zou een redelijk cijfer should receive (met zijn +10 bonus)
    EXPECT_GE(result->final_cijfer, 10) << "Wessel should get at least minimum grade";
    
    // Als originele cijfers laag waren, zou bonus verschil moeten maken
    // (Dit hangt af van de implementation - test aanpassen aan werkelijke logica)
}

/**
 * Test 4: Gelijktijdige herkansingen
 * Test meerdere studenten simultaneously
 */
TEST_F(HerkansingActionTest, TestConcurrentHerkansingen)
{
    std::vector<std::string> students = {"Student1", "Student2", "Student3"};
    std::vector<std::string> courses = {"Math", "Physics", "ROS2"};
    std::vector<std::shared_ptr<GoalHandleHerkanser>> goal_handles;
    std::vector<std::shared_future<GoalHandleHerkanser::WrappedResult>> result_futures;
    
    // Start meerdere herkansingen simultaneously
    for (size_t i = 0; i < students.size(); ++i) {
        auto goal_handle = send_goal(students[i], courses[i]);
        ASSERT_NE(goal_handle, nullptr) << "Goal " << i << " not accepted";
        
        goal_handles.push_back(goal_handle);
        result_futures.push_back(action_client_->async_get_result(goal_handle));
    }
    
    // Wait for alle completions
    for (size_t i = 0; i < result_futures.size(); ++i) {
        auto status = rclcpp::spin_until_future_complete(
            test_node_, result_futures[i], std::chrono::seconds(15));
        
        ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS) 
            << "Concurrent action " << i << " timeout";
        
        auto wrapped_result = result_futures[i].get();
        EXPECT_EQ(wrapped_result.code, rclcpp_action::ResultCode::SUCCEEDED)
            << "Concurrent action " << i << " should succeed";
        
        auto result = wrapped_result.result;
        EXPECT_GE(result->final_cijfer, 10) << "Concurrent result " << i << " should be valid";
        EXPECT_LE(result->final_cijfer, 100) << "Concurrent result " << i << " should be valid";
    }
}

/**
 * Test 5: Action cancellation
 * Test het annuleren van een lopende herkansing
 */
TEST_F(HerkansingActionTest, TestActionCancellation)
{
    auto goal_handle = send_goal("Cancel Student", "Math");
    ASSERT_NE(goal_handle, nullptr);
    
    // Wait a moment until action is started
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // Cancel de action
    auto cancel_future = action_client_->async_cancel_goal(goal_handle);
    auto cancel_status = rclcpp::spin_until_future_complete(
        test_node_, cancel_future, std::chrono::seconds(5));
    
    EXPECT_EQ(cancel_status, rclcpp::FutureReturnCode::SUCCESS) 
        << "Cancel request should complete";
    
    auto cancel_response = cancel_future.get();
    EXPECT_EQ(cancel_response->return_code, action_msgs::srv::CancelGoal::Response::ERROR_NONE)
        << "Cancel should be accepted";
    
    // Wait for final result (should be canceled)
    auto result_future = action_client_->async_get_result(goal_handle);
    rclcpp::spin_until_future_complete(test_node_, result_future, std::chrono::seconds(5));
    
    auto wrapped_result = result_future.get();
    EXPECT_EQ(wrapped_result.code, rclcpp_action::ResultCode::CANCELED)
        << "Action should be marked as canceled";
}

/**
 * Test 6: Invalid input handling
 * Test error handling for ongeldige input
 */
TEST_F(HerkansingActionTest, TestInvalidInputHandling)
{
    // Test lege student name
    auto goal_handle1 = send_goal("", "Math");
    if (goal_handle1 != nullptr) {
        auto result_future = action_client_->async_get_result(goal_handle1);
        rclcpp::spin_until_future_complete(test_node_, result_future, std::chrono::seconds(10));
        
        // Action can succeed or fail - both are acceptable for empty input
        auto wrapped_result = result_future.get();
        EXPECT_TRUE(wrapped_result.code == rclcpp_action::ResultCode::SUCCEEDED || 
                   wrapped_result.code == rclcpp_action::ResultCode::ABORTED)
            << "Empty student name should be handled gracefully";
    }
    
    // Test lege course name
    auto goal_handle2 = send_goal("Student", "");
    if (goal_handle2 != nullptr) {
        auto result_future = action_client_->async_get_result(goal_handle2);
        rclcpp::spin_until_future_complete(test_node_, result_future, std::chrono::seconds(10));
        
        auto wrapped_result = result_future.get();
        EXPECT_TRUE(wrapped_result.code == rclcpp_action::ResultCode::SUCCEEDED || 
                   wrapped_result.code == rclcpp_action::ResultCode::ABORTED)
            << "Empty course name should be handled gracefully";
    }
}

/**
 * Test 7: Stress test - veel opeenvolgende herkansingen
 * Test systeem stabiliteit onder load
 */
TEST_F(HerkansingActionTest, TestStressHerkansingen)
{
    const int stress_count = 5; // Beperkt aantal for unit test
    std::vector<std::shared_future<GoalHandleHerkanser::WrappedResult>> results;
    
    for (int i = 0; i < stress_count; ++i) {
        std::string student = "StressStudent_" + std::to_string(i);
        std::string course = "Course_" + std::to_string(i % 3);
        
        auto goal_handle = send_goal(student, course);
        if (goal_handle != nullptr) {
            results.push_back(action_client_->async_get_result(goal_handle));
        }
    }
    
    // Verify that at least most actions are successful
    int successful_actions = 0;
    for (auto& result_future : results) {
        auto status = rclcpp::spin_until_future_complete(
            test_node_, result_future, std::chrono::seconds(20));
        
        if (status == rclcpp::FutureReturnCode::SUCCESS) {
            auto wrapped_result = result_future.get();
            if (wrapped_result.code == rclcpp_action::ResultCode::SUCCEEDED) {
                successful_actions++;
            }
        }
    }
    
    // Expect at least 80% of actions to be successful
    double success_rate = static_cast<double>(successful_actions) / results.size();
    EXPECT_GE(success_rate, 0.8) << "Success rate should be at least 80% under stress";
}

// Test runner
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
