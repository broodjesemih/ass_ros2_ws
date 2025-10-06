#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "g1_interface_pkg/msg/tentamen.hpp"
#include <chrono>
#include <fstream>

using namespace std::chrono_literals;

class TestFinalCijferDeterminator : public ::testing::Test {
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

TEST_F(TestFinalCijferDeterminator, test_subscription_active) {
  auto node = rclcpp::Node::make_shared("test_final_cijfer");
  auto publisher = node->create_publisher<g1_interface_pkg::msg::Tentamen>("tentamen_results", 10);

  // Wait for subscriber to connect
  std::this_thread::sleep_for(500ms);

  EXPECT_GE(publisher->get_subscription_count(),
    1) << "final_cijfer_determinator should be subscribed";
}

TEST_F(TestFinalCijferDeterminator, test_tentamen_reception) {
  auto node = rclcpp::Node::make_shared("test_publisher");
  auto publisher = node->create_publisher<g1_interface_pkg::msg::Tentamen>("tentamen_results", 10);

  // Wait for subscriber to connect
  std::this_thread::sleep_for(500ms);

  // Publish 3 tentamen results for the same student/course
  for (int i = 0; i < 3; i++) {
    auto msg = g1_interface_pkg::msg::Tentamen();
    msg.stamp = node->now();
    msg.student_name = "TestStudent";
    msg.course_name = "TestCourse";
    msg.tentamen_cijfer = 70 + i * 5;

    publisher->publish(msg);
    rclcpp::spin_some(node);
    std::this_thread::sleep_for(200ms);
  }

  // Give it time to process and write to database
  std::this_thread::sleep_for(1500ms);

  // Check if database entry was created
  std::ifstream db("/home/broodjesemih/ass_ros2_ws/database.csv");
  std::string line;
  bool found = false;

  while (std::getline(db, line)) {
    if (line.find("TestStudent") != std::string::npos &&
      line.find("TestCourse") != std::string::npos)
    {
      found = true;
      break;
    }
  }

  EXPECT_TRUE(found) << "Database should contain entry for TestStudent/TestCourse";
}

TEST_F(TestFinalCijferDeterminator, test_three_tentamen_threshold) {
  auto node = rclcpp::Node::make_shared("test_threshold");
  auto publisher = node->create_publisher<g1_interface_pkg::msg::Tentamen>("tentamen_results", 10);

  std::this_thread::sleep_for(500ms);

  // Count initial database entries
  std::ifstream db_before("/home/broodjesemih/ass_ros2_ws/database.csv");
  int count_before = std::count(std::istreambuf_iterator<char>(db_before),
                                 std::istreambuf_iterator<char>(), '\n');
  db_before.close();

  // Publish only 2 tentamen results
  for (int i = 0; i < 2; i++) {
    auto msg = g1_interface_pkg::msg::Tentamen();
    msg.stamp = node->now();
    msg.student_name = "TestStudent2";
    msg.course_name = "TestCourse2";
    msg.tentamen_cijfer = 60;

    publisher->publish(msg);
    rclcpp::spin_some(node);
    std::this_thread::sleep_for(100ms);
  }

  std::this_thread::sleep_for(1s);

  // Count database entries again
  std::ifstream db_after("/home/broodjesemih/ass_ros2_ws/database.csv");
  int count_after = std::count(std::istreambuf_iterator<char>(db_after),
                                std::istreambuf_iterator<char>(), '\n');
  db_after.close();

  // Should not have added new entry with only 2 tentamens
  EXPECT_EQ(count_before, count_after) << "Should not create database entry with only 2 tentamens";
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
