#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "g1_interface_pkg/msg/tentamen.hpp"
#include <chrono>

using namespace std::chrono_literals;

class TestTentamenPublisher : public ::testing::Test {
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

TEST_F(TestTentamenPublisher, test_tentamen_published) {
  auto node = rclcpp::Node::make_shared("test_tentamen_subscriber");

  bool received = false;
  g1_interface_pkg::msg::Tentamen received_msg;

  auto subscription = node->create_subscription<g1_interface_pkg::msg::Tentamen>(
    "tentamen_results", 10,
    [&received, &received_msg](const g1_interface_pkg::msg::Tentamen::SharedPtr msg) {
      received = true;
      received_msg = *msg;
    });

  // Spin for a few seconds to receive messages
  auto start = std::chrono::steady_clock::now();
  while (!received && (std::chrono::steady_clock::now() - start) < 10s) {
    rclcpp::spin_some(node);
    std::this_thread::sleep_for(100ms);
  }

  ASSERT_TRUE(received) << "No tentamen message received within timeout";
  EXPECT_FALSE(received_msg.student_name.empty());
  EXPECT_FALSE(received_msg.course_name.empty());
  EXPECT_GE(received_msg.tentamen_cijfer, 10);
  EXPECT_LE(received_msg.tentamen_cijfer, 100);
}

TEST_F(TestTentamenPublisher, test_multiple_messages) {
  auto node = rclcpp::Node::make_shared("test_tentamen_subscriber");

  int count = 0;

  auto subscription = node->create_subscription<g1_interface_pkg::msg::Tentamen>(
    "tentamen_results", 10,
    [&count](const g1_interface_pkg::msg::Tentamen::SharedPtr) {
      count++;
    });

  // Spin for 5 seconds to receive multiple messages (published every 2 seconds)
  auto start = std::chrono::steady_clock::now();
  while ((std::chrono::steady_clock::now() - start) < 5s) {
    rclcpp::spin_some(node);
    std::this_thread::sleep_for(100ms);
  }

  EXPECT_GE(count, 1) << "Should receive at least 1 message in 5 seconds";
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
