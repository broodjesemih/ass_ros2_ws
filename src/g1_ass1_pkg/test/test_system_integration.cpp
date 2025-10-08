#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <memory>
#include <chrono>
#include <vector>
#include <string>
#include <thread>
#include "g1_interface_pkg/srv/tentamens.hpp"
#include "g1_interface_pkg/action/herkanser.hpp"

/**
 * Integration tests for het complete ROS2 Grade Calculator systeem
 * 
 * These tests validate:
 * - End-to-end workflow (tentamen → berekening → database → herkansing)
 * - Inter-node communicatie
 * - System-level requirements compliance
 * - Real-world scenario simulation
 * - Performance onder normale load
 */

class SystemIntegrationTest : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        rclcpp::init(0, nullptr);
        test_node_ = rclcpp::Node::make_shared("test_system_integration");
        
        // Wacht even for node discovery
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        // Verify that alle vereiste nodes draaien
        auto node_names = test_node_->get_node_names();
        
        required_nodes_ = {
            "tentamen_result_generator",
            "cijfer_calculator", 
            "final_cijfer_determinator",
            "herkansing_scheduler",
            "herkansing_cijfer_determinator"
        };
        
        missing_nodes_.clear();
        for (const auto& required : required_nodes_) {
            bool found = false;
            for (const auto& running : node_names) {
                if (running.find(required) != std::string::npos) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                missing_nodes_.push_back(required);
            }
        }
    }

    void TearDown() override 
    {
        rclcpp::shutdown();
    }

    // Helper function to te wachten op system stabiliteit
    void wait_for_system_stability(int seconds = 5)
    {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        
        // Spin node om messages te process
        for (int i = 0; i < 10; ++i) {
            rclcpp::spin_some(test_node_);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    // Helper function to check active topics  
    std::vector<std::string> get_active_topics()
    {
        auto topic_map = test_node_->get_topic_names_and_types();
        std::vector<std::string> topics;
        for (const auto& pair : topic_map) {
            topics.push_back(pair.first);
        }
        return topics;
    }

    // Helper function to check active services
    std::vector<std::string> get_active_services() 
    {
        auto service_map = test_node_->get_service_names_and_types();
        std::vector<std::string> services;
        for (const auto& pair : service_map) {
            services.push_back(pair.first);
        }
        return services;
    }

    rclcpp::Node::SharedPtr test_node_;
    std::vector<std::string> required_nodes_;
    std::vector<std::string> missing_nodes_;
};

/**
 * Test 1: System startup en node availability
 * Verificeer that all vereiste nodes actief zijn
 */
TEST_F(SystemIntegrationTest, TestSystemStartupAndNodeAvailability)
{
    EXPECT_TRUE(missing_nodes_.empty()) 
        << "Missing nodes: " << [this]() {
            std::string missing_str;
            for (const auto& node : missing_nodes_) {
                if (!missing_str.empty()) missing_str += ", ";
                missing_str += node;
            }
            return missing_str;
        }();

    // Verify minimale node count
    auto node_names = test_node_->get_node_names();
    EXPECT_GE(node_names.size(), 5) << "Should have at least 5 nodes running (excluding test node)";
}

/**
 * Test 2: ROS2 Communication Infrastructure
 * Verificeer that all vereiste topics en services beschikbaar zijn
 */
TEST_F(SystemIntegrationTest, TestCommunicationInfrastructure)
{
    auto topics = get_active_topics();
    auto services = get_active_services();
    
    // Vereiste topics
    std::vector<std::string> required_topics = {
        "tentamen_results",
        "student_control"
    };
    
    for (const auto& topic : required_topics) {
        bool found = false;
        for (const auto& active_topic : topics) {
            if (active_topic.find(topic) != std::string::npos) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found) << "Required topic not found: " << topic;
    }
    
    // Vereiste services
    std::vector<std::string> required_services = {
        "calculate_final_cijfer"
    };
    
    for (const auto& service : required_services) {
        bool found = false;
        for (const auto& active_service : services) {
            if (active_service.find(service) != std::string::npos) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found) << "Required service not found: " << service;
    }
}

/**
 * Test 3: End-to-End Grade Calculation Workflow
 * Test complete flow van tentamen publicatie tot final result
 */
TEST_F(SystemIntegrationTest, TestEndToEndGradeCalculation)
{
    // Maak service client for cijfer calculator
    auto cijfer_client = test_node_->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");
    
    ASSERT_TRUE(cijfer_client->wait_for_service(std::chrono::seconds(5))) 
        << "Cijfer calculator service niet beschikbaar";
    
    // Test normal student
    {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "Integration Test Student";
        request->course_name = "SystemTest";
        request->tentamen_cijfers = {75, 80, 85};
        
        auto future = cijfer_client->async_send_request(request);
        auto status = rclcpp::spin_until_future_complete(test_node_, future, std::chrono::seconds(5));
        
        ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS) << "Grade calculation service call failed";
        
        auto response = future.get();
        EXPECT_EQ(response->final_cijfer, 80) << "Expected average of 75, 80, 85 = 80";
    }
    
    // Test Wessel bonus
    {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "Wessel Tip";
        request->course_name = "SystemTest";
        request->tentamen_cijfers = {50, 50, 50};
        
        auto future = cijfer_client->async_send_request(request);
        auto status = rclcpp::spin_until_future_complete(test_node_, future, std::chrono::seconds(5));
        
        ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS);
        
        auto response = future.get();
        EXPECT_EQ(response->final_cijfer, 60) << "Wessel should get +10 bonus: 50 + 10 = 60";
    }
}

/**
 * Test 4: Herkansing Action Server Integration
 * Test complete herkansing workflow via action server
 */
TEST_F(SystemIntegrationTest, TestHerkansingActionIntegration)
{
    // Maak action client
    auto action_client = rclcpp_action::create_client<g1_interface_pkg::action::Herkanser>(
        test_node_, "herkanser");
    
    ASSERT_TRUE(action_client->wait_for_action_server(std::chrono::seconds(10)))
        << "Herkansing action server niet beschikbaar";
    
    // Test herkansing for failed student
    auto goal_msg = g1_interface_pkg::action::Herkanser::Goal();
    goal_msg.student_name = "Integration Failed Student";
    goal_msg.course_name = "SystemTest";
    
    auto send_goal_options = rclcpp_action::Client<g1_interface_pkg::action::Herkanser>::SendGoalOptions();
    
    bool feedback_received = false;
    send_goal_options.feedback_callback = 
        [&feedback_received](auto, const auto& feedback) {
            feedback_received = true;
            EXPECT_GE(feedback->progress, 0.0f) << "Progress should be non-negative";
            EXPECT_LE(feedback->progress, 1.0f) << "Progress should not exceed 1.0";
        };
    
    auto goal_handle_future = action_client->async_send_goal(goal_msg, send_goal_options);
    
    // Wait for goal acceptance
    auto goal_handle_status = rclcpp::spin_until_future_complete(
        test_node_, goal_handle_future, std::chrono::seconds(5));
    
    ASSERT_EQ(goal_handle_status, rclcpp::FutureReturnCode::SUCCESS) << "Goal submission failed";
    
    auto goal_handle = goal_handle_future.get();
    ASSERT_NE(goal_handle, nullptr) << "Goal was not accepted";
    
    // Wait for completion
    auto result_future = action_client->async_get_result(goal_handle);
    auto result_status = rclcpp::spin_until_future_complete(
        test_node_, result_future, std::chrono::seconds(15));
    
    ASSERT_EQ(result_status, rclcpp::FutureReturnCode::SUCCESS) << "Action completion timeout";
    
    auto wrapped_result = result_future.get();
    EXPECT_EQ(wrapped_result.code, rclcpp_action::ResultCode::SUCCEEDED) << "Action should succeed";
    
    auto result = wrapped_result.result;
    EXPECT_GE(result->final_cijfer, 10) << "Herkansing result should be valid";
    EXPECT_LE(result->final_cijfer, 100) << "Herkansing result should be valid";
    EXPECT_TRUE(feedback_received) << "Should receive feedback during execution";
}

/**
 * Test 5: System Performance under Load
 * Test system behavior met meerdere gelijktijdige operaties
 */
TEST_F(SystemIntegrationTest, TestSystemPerformanceUnderLoad)
{
    auto cijfer_client = test_node_->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");
    ASSERT_TRUE(cijfer_client->wait_for_service(std::chrono::seconds(5)));
    
    const int concurrent_requests = 10;
    std::vector<rclcpp::Client<g1_interface_pkg::srv::Tentamens>::SharedFuture> futures;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    // Send multiple requests gelijktijdig
    for (int i = 0; i < concurrent_requests; ++i) {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "Load Test Student " + std::to_string(i);
        request->course_name = "LoadTest";
        request->tentamen_cijfers = {70 + i, 75 + i, 80 + i};
        
        futures.push_back(cijfer_client->async_send_request(request).future);
    }
    
    // Wait for all responses
    int successful_requests = 0;
    for (auto& future : futures) {
        auto status = rclcpp::spin_until_future_complete(test_node_, future, std::chrono::seconds(10));
        if (status == rclcpp::FutureReturnCode::SUCCESS) {
            auto response = future.get();
            if (response && response->final_cijfer >= 10 && response->final_cijfer <= 100) {
                successful_requests++;
            }
        }
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    // Performance expectations
    EXPECT_EQ(successful_requests, concurrent_requests) 
        << "All concurrent requests should succeed";
    EXPECT_LT(duration.count(), 10000) 
        << "Concurrent requests should complete within 10 seconds";
    
    std::cout << "Load test: " << concurrent_requests << " requests in " << duration.count() << "ms" << std::endl;
}

/**
 * Test 6: System Requirements Compliance
 * Verificeer dat systeem voldoet aan originele requirements
 */
TEST_F(SystemIntegrationTest, TestSystemRequirementsCompliance)
{
    // Requirement 1: 5 ROS2 nodes
    auto node_names = test_node_->get_node_names();
    int system_nodes = 0;
    for (const auto& node : node_names) {
        // Tel alleen system nodes (niet test/monitoring nodes)
        if (node.find("tentamen") != std::string::npos ||
            node.find("cijfer") != std::string::npos ||
            node.find("herkansing") != std::string::npos ||
            node.find("final") != std::string::npos) {
            system_nodes++;
        }
    }
    EXPECT_GE(system_nodes, 5) << "System should have at least 5 nodes";
    
    // Requirement 2: Topics, Services, Actions
    auto topics = get_active_topics();
    auto services = get_active_services();
    
    bool has_topics = false, has_services = false, has_actions = false;
    
    for (const auto& topic : topics) {
        if (topic.find("tentamen") != std::string::npos) has_topics = true;
        if (topic.find("_action") != std::string::npos) has_actions = true;
    }
    
    for (const auto& service : services) {
        if (service.find("calculate") != std::string::npos) has_services = true;
    }
    
    EXPECT_TRUE(has_topics) << "System should use ROS2 topics";
    EXPECT_TRUE(has_services) << "System should use ROS2 services"; 
    EXPECT_TRUE(has_actions) << "System should use ROS2 actions";
    
    // Requirement 3: Grade calculation with Wessel bonus
    auto cijfer_client = test_node_->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");
    if (cijfer_client->wait_for_service(std::chrono::seconds(2))) {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "Wessel Tip";
        request->course_name = "RequirementTest";
        request->tentamen_cijfers = {50, 50, 50};
        
        auto future = cijfer_client->async_send_request(request);
        auto status = rclcpp::spin_until_future_complete(test_node_, future, std::chrono::seconds(3));
        
        if (status == rclcpp::FutureReturnCode::SUCCESS) {
            auto response = future.get();
            EXPECT_EQ(response->final_cijfer, 60) << "Wessel bonus requirement not met";
        }
    }
    
    // Requirement 4: Herkansing system  
    auto action_client = rclcpp_action::create_client<g1_interface_pkg::action::Herkanser>(
        test_node_, "herkanser");
    EXPECT_TRUE(action_client->wait_for_action_server(std::chrono::seconds(2)))
        << "Herkansing action server requirement not met";
}

/**
 * Test 7: Error Recovery and System Resilience  
 * Test hoe systeem omgaat met fouten en recovery scenarios
 */
TEST_F(SystemIntegrationTest, TestErrorRecoveryAndResilience)
{
    auto cijfer_client = test_node_->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");
    ASSERT_TRUE(cijfer_client->wait_for_service(std::chrono::seconds(5)));
    
    // Test invalid input handling
    {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "";  // Empty name
        request->course_name = "ErrorTest";
        request->tentamen_cijfers = {75, 80, 85};
        
        auto future = cijfer_client->async_send_request(request);
        auto status = rclcpp::spin_until_future_complete(test_node_, future, std::chrono::seconds(5));
        
        // System should handle gracefully (either accept with default or reject cleanly)
        EXPECT_EQ(status, rclcpp::FutureReturnCode::SUCCESS) 
            << "System should handle invalid input gracefully";
    }
    
    // Test empty grade list
    {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "ErrorTestStudent";
        request->course_name = "ErrorTest";
        request->tentamen_cijfers = {};  // Empty grades
        
        auto future = cijfer_client->async_send_request(request);
        auto status = rclcpp::spin_until_future_complete(test_node_, future, std::chrono::seconds(5));
        
        EXPECT_EQ(status, rclcpp::FutureReturnCode::SUCCESS)
            << "System should handle empty grade list gracefully";
    }
}

/**
 * Test 8: System Shutdown and Cleanup
 * Test orderly system shutdown behavior
 */
TEST_F(SystemIntegrationTest, TestSystemShutdownBehavior)
{
    // This test is more informative - we test that nodes still respond
    auto cijfer_client = test_node_->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");
    
    if (cijfer_client->wait_for_service(std::chrono::milliseconds(1000))) {
        // Test that service still works before we test shutdown
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "Shutdown Test";
        request->course_name = "Final";
        request->tentamen_cijfers = {85, 90, 95};
        
        auto future = cijfer_client->async_send_request(request);
        auto status = rclcpp::spin_until_future_complete(test_node_, future, std::chrono::seconds(3));
        
        EXPECT_EQ(status, rclcpp::FutureReturnCode::SUCCESS)
            << "Service should still be responsive before shutdown";
        
        if (status == rclcpp::FutureReturnCode::SUCCESS) {
            auto response = future.get();
            EXPECT_EQ(response->final_cijfer, 90) << "Final service call should work correctly";
        }
    }
    
    // Note: Actual shutdown testing would require process management
    // which is beyond scope of unit testing
}

// Test runner
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
