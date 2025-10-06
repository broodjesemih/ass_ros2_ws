#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "g1_interface_pkg/srv/tentamens.hpp"
#include <chrono>

using namespace std::chrono_literals;

class TestCijferService : public ::testing::Test {
protected:
  static void SetUpTestSuite()
  {
    rclcpp::init(0, nullptr);
  }

  static void TearDownTestSuite()
  {
    rclcpp::shutdown();
  }
};

TEST_F(TestCijferService, test_average_calculation) {
  auto node = rclcpp::Node::make_shared("test_cijfer_client");
  auto client = node->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");

  ASSERT_TRUE(client->wait_for_service(5s));

  auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
  request->student_name = "Alice";
  request->course_name = "Math";
  request->tentamen_cijfers = {60, 70, 80};

  auto result = client->async_send_request(request);
  auto status = rclcpp::spin_until_future_complete(node, result, 5s);

  ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS);
  auto response = result.get();

  // Average of 60, 70, 80 = 70
  EXPECT_EQ(response->final_cijfer, 70);
  EXPECT_EQ(response->message, "Cijfer berekend");
}

TEST_F(TestCijferService, test_wessel_bonus) {
  auto node = rclcpp::Node::make_shared("test_cijfer_client");
  auto client = node->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");

  ASSERT_TRUE(client->wait_for_service(5s));

  auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
  request->student_name = "Wessel";
  request->course_name = "Physics";
  request->tentamen_cijfers = {50, 60, 70};

  auto result = client->async_send_request(request);
  auto status = rclcpp::spin_until_future_complete(node, result, 5s);

  ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS);
  auto response = result.get();

  // Average of 50, 60, 70 = 60, plus 10 bonus = 70
  EXPECT_EQ(response->final_cijfer, 70);
}

TEST_F(TestCijferService, test_max_clamp) {
  auto node = rclcpp::Node::make_shared("test_cijfer_client");
  auto client = node->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");

  ASSERT_TRUE(client->wait_for_service(5s));

  auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
  request->student_name = "Wessel";
  request->course_name = "Chemistry";
  request->tentamen_cijfers = {95, 100, 100};

  auto result = client->async_send_request(request);
  auto status = rclcpp::spin_until_future_complete(node, result, 5s);

  ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS);
  auto response = result.get();

  // Average of 95, 100, 100 = 98.33, plus 10 bonus = 108.33, clamped to 100
  EXPECT_EQ(response->final_cijfer, 100);
}

TEST_F(TestCijferService, test_min_clamp) {
  auto node = rclcpp::Node::make_shared("test_cijfer_client");
  auto client = node->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");

  ASSERT_TRUE(client->wait_for_service(5s));

  auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
  request->student_name = "Bob";
  request->course_name = "History";
  request->tentamen_cijfers = {5, 5, 5};

  auto result = client->async_send_request(request);
  auto status = rclcpp::spin_until_future_complete(node, result, 5s);

  ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS);
  auto response = result.get();

  // Average of 5, 5, 5 = 5, clamped to minimum 10
  EXPECT_EQ(response->final_cijfer, 10);
}

TEST_F(TestCijferService, test_empty_cijfers) {
  auto node = rclcpp::Node::make_shared("test_cijfer_client");
  auto client = node->create_client<g1_interface_pkg::srv::Tentamens>("calculate_final_cijfer");

  ASSERT_TRUE(client->wait_for_service(5s));

  auto request = std::make_shared<g1_interface_pkg::srv::Tentamens::Request>();
  request->student_name = "Charlie";
  request->course_name = "Biology";
  request->tentamen_cijfers = {};

  auto result = client->async_send_request(request);
  auto status = rclcpp::spin_until_future_complete(node, result, 5s);

  ASSERT_EQ(status, rclcpp::FutureReturnCode::SUCCESS);
  auto response = result.get();

  // Empty list should result in average 0, clamped to minimum 10
  EXPECT_EQ(response->final_cijfer, 10);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
