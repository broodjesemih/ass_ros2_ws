#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <chrono>
#include <future>
#include "g1_interface_pkg/srv/tentamens.hpp"

/**
 * Unit tests voor de CijferCalculator service node
 * 
 * Deze tests valideren:
 * - Service response correctheid
 * - Wessel bonus logica (+10 punten)
 * - Grade boundary validatie (10-100)
 * - Gemiddelde berekening
 * - Error handling
 */

class CijferCalculatorTest : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        rclcpp::init(0, nullptr);
        node_ = rclcpp::Node::make_shared("test_cijfer_calculator");
        client_ = node_->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");
        
        // Wacht tot service beschikbaar is (max 5 seconden)
        ASSERT_TRUE(client_->wait_for_service(std::chrono::seconds(5))) 
            << "Service 'calculate_final_cijfer' is niet beschikbaar binnen 5 seconden";
    }

    void TearDown() override 
    {
        rclcpp::shutdown();
    }

    // Helper functie om service calls uit te voeren
    std::shared_ptr<g1_interface_pkg::srv::Tentamens::Response> call_service(
        const std::string& student_name, 
        const std::string& course_name, 
        const std::vector<int>& cijfers)
    {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = student_name;
        request->course_name = course_name;
        request->tentamen_cijfers = cijfers;

        auto future = client_->async_send_request(request);
        
        // Wacht op response (max 3 seconden)
        auto status = future.wait_for(std::chrono::seconds(3));
        EXPECT_EQ(status, std::future_status::ready) << "Service call timeout";
        
        if (status == std::future_status::ready) {
            return future.get();
        }
        return nullptr;
    }

    rclcpp::Node::SharedPtr node_;
    rclcpp::Client<g1_interface_pkg::srv::Tentamens>::SharedPtr client_;
};

/**
 * Test 1: Basis gemiddelde berekening voor normale student
 * Input: [80, 70, 90]
 * Verwacht: gemiddelde = 80
 */
TEST_F(CijferCalculatorTest, TestBasicAverageCalculation)
{
    auto response = call_service("TestStudent", "Math", {80, 70, 90});
    
    ASSERT_NE(response, nullptr) << "Service response is null";
    EXPECT_EQ(response->final_cijfer, 80) << "Gemiddelde berekening incorrect voor normale student";
    EXPECT_FALSE(response->message.empty()) << "Response message should not be empty";
}

/**
 * Test 2: Wessel Tip bonus logica 
 * Wessel krijgt +10 punten bonus
 * Input: [50, 50, 50] → gemiddelde 50 + 10 = 60
 */
TEST_F(CijferCalculatorTest, TestWesselBonus)
{
    auto response = call_service("Wessel Tip", "ROS2", {50, 50, 50});
    
    ASSERT_NE(response, nullptr) << "Service response is null";
    EXPECT_EQ(response->final_cijfer, 60) << "Wessel bonus (+10) niet correct toegepast";
}

/**
 * Test 3: Grade boundaries - minimum cijfer is 10
 * Input: [5, 5, 5] → gemiddelde 5, maar minimum is 10
 */
TEST_F(CijferCalculatorTest, TestMinimumGradeBoundary)
{
    auto response = call_service("TestStudent", "Math", {5, 5, 5});
    
    ASSERT_NE(response, nullptr) << "Service response is null";
    EXPECT_EQ(response->final_cijfer, 10) << "Minimum grade boundary (10) niet gerespecteerd";
}

/**
 * Test 4: Grade boundaries - maximum cijfer is 100
 * Wessel met hoge cijfers + bonus mag niet boven 100 gaan
 */
TEST_F(CijferCalculatorTest, TestMaximumGradeBoundary)
{
    auto response = call_service("Wessel Tip", "Math", {95, 95, 95});
    
    ASSERT_NE(response, nullptr) << "Service response is null";
    EXPECT_LE(response->final_cijfer, 100) << "Maximum grade boundary (100) overschreden";
}

/**
 * Test 5: Wessel met verschillende case variations
 * Test verschillende schrijfwijzen van Wessel's naam
 */
TEST_F(CijferCalculatorTest, TestWesselNameVariations)
{
    std::vector<std::string> wessel_variations = {"Wessel Tip", "wessel tip", "WESSEL TIP", "Wessel tip"};
    
    for (const auto& name : wessel_variations) {
        auto response = call_service(name, "Test", {50, 50, 50});
        ASSERT_NE(response, nullptr) << "Service response is null for name: " << name;
        
        // Alle variations zouden bonus moeten krijgen (afhankelijk van implementatie)
        // Als implementatie case-sensitive is, pas verwachting aan
        if (name == "Wessel Tip") {
            EXPECT_EQ(response->final_cijfer, 60) << "Wessel bonus niet toegepast voor: " << name;
        }
    }
}

/**
 * Test 6: Edge case - lege cijferlijst
 * Test error handling voor invalide input
 */
TEST_F(CijferCalculatorTest, TestEmptyGradesList)
{
    auto response = call_service("TestStudent", "Math", {});
    
    // Service zou moeten antwoorden (al is het met error)
    ASSERT_NE(response, nullptr) << "Service should respond even for invalid input";
    
    // Afhankelijk van implementatie: default waarde of error handling
    EXPECT_GE(response->final_cijfer, 10) << "Final grade should be at least minimum (10)";
}

/**
 * Test 7: Drie verschillende studenten tegelijkertijd
 * Test concurrency en correcte response matching
 */
TEST_F(CijferCalculatorTest, TestMultipleStudentsConcurrency)
{
    // Verstuur meerdere requests tegelijkertijd
    std::vector<rclcpp::Client<g1_interface_pkg::srv::Tentamens>::SharedFuture> futures;
    
    // Normale student
    {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "Student1";
        request->course_name = "Math";
        request->tentamen_cijfers = {80, 80, 80};
        futures.push_back(client_->async_send_request(request).future);
    }
    
    // Wessel
    {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "Wessel Tip";
        request->course_name = "Math";
        request->tentamen_cijfers = {50, 50, 50};
        futures.push_back(client_->async_send_request(request).future);
    }
    
    // Andere student
    {
        auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
        request->student_name = "Student2";
        request->course_name = "Math";
        request->tentamen_cijfers = {60, 70, 80};
        futures.push_back(client_->async_send_request(request).future);
    }
    
    // Wacht op alle responses
    std::vector<int> expected_results = {80, 60, 70}; // Student1, Wessel+bonus, Student2 gemiddelde
    
    for (size_t i = 0; i < futures.size(); ++i) {
        auto status = futures[i].wait_for(std::chrono::seconds(3));
        ASSERT_EQ(status, std::future_status::ready) << "Concurrent service call " << i << " timeout";
        
        auto response = futures[i].get();
        ASSERT_NE(response, nullptr) << "Concurrent response " << i << " is null";
        EXPECT_EQ(response->final_cijfer, expected_results[i]) << "Concurrent calculation " << i << " incorrect";
    }
}

/**
 * Test 8: Afrondingslogica
 * Test correcte afronding van gemiddelden
 */
TEST_F(CijferCalculatorTest, TestRoundingLogic)
{
    // Test verschillende rounding scenarios
    auto response1 = call_service("TestStudent", "Math", {75, 76, 77}); // gemiddelde 76.0
    ASSERT_NE(response1, nullptr);
    EXPECT_EQ(response1->final_cijfer, 76);
    
    auto response2 = call_service("TestStudent", "Math", {75, 75, 76}); // gemiddelde 75.33... 
    ASSERT_NE(response2, nullptr);
    // Afhankelijk van afrondingslogica in implementatie
    EXPECT_TRUE(response2->final_cijfer == 75 || response2->final_cijfer == 76) 
        << "Rounding logic should handle decimals correctly";
}

// Test runner main functie
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
