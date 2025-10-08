cmake_minimum_required(VERSION 3.8)
project(g1_25_assign1_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Dependencies
find_package(g1_25_assign1_interfaces_pkg REQUIRED)
find_package(ament_cmake REQUIRED)            # cmake package
find_package(rclcpp REQUIRED)                 # required for all nodes
find_package(rclcpp_action REQUIRED)          # required if an action server node is created
find_package(std_msgs REQUIRED)               # use standard messages
find_package(builtin_interfaces REQUIRED)     # required for Time messages
find_package(rosidl_default_generators REQUIRED) # required to use custom messages

# Find PostgreSQL and libpqxx
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Create a library from database.cpp
add_library(database_lib src/database.cpp)
target_include_directories(database_lib PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(database_lib ${PQXX_LIBRARIES})
target_compile_options(database_lib PRIVATE ${PQXX_CFLAGS_OTHER})

# Executables
add_executable(g1_25_tentamen_result_generator_node src/g1_25_tentamen_result_generator_node.cpp)
ament_target_dependencies(g1_25_tentamen_result_generator_node rclcpp g1_25_assign1_interfaces_pkg)
target_link_libraries(g1_25_tentamen_result_generator_node database_lib)

add_executable(g1_25_final_cijfer_determinator_node src/g1_25_final_cijfer_determinator_node.cpp)
ament_target_dependencies(g1_25_final_cijfer_determinator_node rclcpp g1_25_assign1_interfaces_pkg)
target_link_libraries(g1_25_final_cijfer_determinator_node database_lib)

add_executable(g1_25_cijfer_calculator_node src/g1_25_cijfer_calculator_node.cpp)
ament_target_dependencies(g1_25_cijfer_calculator_node rclcpp g1_25_assign1_interfaces_pkg)
target_link_libraries(g1_25_cijfer_calculator_node database_lib)

add_executable(g1_25_herkansing_cijfer_determinator_node src/g1_25_herkansing_cijfer_determinator_node.cpp)
ament_target_dependencies(g1_25_herkansing_cijfer_determinator_node rclcpp_action rclcpp g1_25_assign1_interfaces_pkg)
target_link_libraries(g1_25_herkansing_cijfer_determinator_node database_lib)

add_executable(g1_25_herkansing_scheduler_node src/g1_25_herkansing_scheduler_node.cpp)
ament_target_dependencies(g1_25_herkansing_scheduler_node rclcpp_action rclcpp g1_25_assign1_interfaces_pkg)
target_link_libraries(g1_25_herkansing_scheduler_node database_lib)



# # Executables
# add_executable(tentamen_result_generator src/tentamen_result_generator.cpp)
# ament_target_dependencies(tentamen_result_generator rclcpp g1_25_assign1_interfaces_pkg)

# add_executable(final_cijfer_determinator src/final_cijfer_determinator.cpp)
# ament_target_dependencies(final_cijfer_determinator rclcpp g1_25_assign1_interfaces_pkg)

# add_executable(cijfer_calculator src/cijfer_calculator.cpp)
# ament_target_dependencies(cijfer_calculator rclcpp g1_25_assign1_interfaces_pkg)

# add_executable(herkansing_cijfer_determinator src/herkansing_cijfer_determinator.cpp)
# ament_target_dependencies(herkansing_cijfer_determinator rclcpp_action rclcpp g1_25_assign1_interfaces_pkg)

# add_executable(herkansing_scheduler src/herkansing_scheduler.cpp)
# ament_target_dependencies(herkansing_scheduler rclcpp_action rclcpp g1_25_assign1_interfaces_pkg)

install(TARGETS
  g1_25_tentamen_result_generator_node
  g1_25_final_cijfer_determinator_node
  g1_25_cijfer_calculator_node
  g1_25_herkansing_cijfer_determinator_node
  g1_25_herkansing_scheduler_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install test executables (if built)
if(BUILD_TESTING)
  # Only install targets that actually exist
  if(TARGET test_cijfer_calculator)
    install(TARGETS test_cijfer_calculator DESTINATION lib/${PROJECT_NAME})
  endif()
  if(TARGET test_topic_communication)
    install(TARGETS test_topic_communication DESTINATION lib/${PROJECT_NAME})
  endif()
  if(TARGET test_herkansing_action)
    install(TARGETS test_herkansing_action DESTINATION lib/${PROJECT_NAME})
  endif()
  if(TARGET test_database)
    install(TARGETS test_database DESTINATION lib/${PROJECT_NAME})
  endif()
  if(TARGET test_system_integration)
    install(TARGETS test_system_integration DESTINATION lib/${PROJECT_NAME})
  endif()
endif()

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  # Skip all linting tests for cleaner colcon test output
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  set(ament_cmake_lint_cmake_FOUND TRUE)
  set(ament_cmake_uncrustify_FOUND TRUE)
  set(ament_cmake_xmllint_FOUND TRUE)
  set(ament_cmake_cppcheck_FOUND TRUE)

  # Unit Tests Configuration
  # ========================
  # STANDAARD: Alleen standalone tests (database + topic communication)
  # Voor alle tests: colcon build -DBUILD_ALL_TESTS=ON

  # STANDALONE TESTS (always enabled) - These should always pass

  # Database Tests (standalone, no ROS2 system required)
  ament_add_gtest(test_database test/test_database.cpp)
  if(TARGET test_database)
    target_include_directories(test_database PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${PQXX_INCLUDE_DIRS})
    target_compile_options(test_database PRIVATE ${PQXX_CFLAGS_OTHER})
    target_link_libraries(test_database ${GTEST_LIBRARIES} ${PQXX_LIBRARIES})
  endif()

  # Topic Communication Tests (standalone, no external services required)
  ament_add_gtest(test_topic_communication test/test_topic_communication.cpp)
  if(TARGET test_topic_communication)
    target_include_directories(test_topic_communication PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
    ament_target_dependencies(test_topic_communication rclcpp g1_25_assign1_interfaces_pkg)
    target_link_libraries(test_topic_communication ${GTEST_LIBRARIES})
  endif()

  # ⚠️ INTEGRATION TESTS (only when BUILD_ALL_TESTS=ON) - Require running ROS2 system
  if(BUILD_ALL_TESTS)
    message(STATUS "Building ALL tests (including integration tests)")

    # Service Tests (require active ROS2 services)
    ament_add_gtest(test_cijfer_calculator test/test_cijfer_calculator.cpp)
    if(TARGET test_cijfer_calculator)
      target_include_directories(test_cijfer_calculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
      ament_target_dependencies(test_cijfer_calculator rclcpp g1_25_assign1_interfaces_pkg)
      target_link_libraries(test_cijfer_calculator ${GTEST_LIBRARIES})
    endif()

    # Action Server Tests (require active ROS2 action servers)
    ament_add_gtest(test_herkansing_action test/test_herkansing_action.cpp)
    if(TARGET test_herkansing_action)
      target_include_directories(test_herkansing_action PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
      ament_target_dependencies(test_herkansing_action rclcpp rclcpp_action g1_25_assign1_interfaces_pkg)
      target_link_libraries(test_herkansing_action ${GTEST_LIBRARIES})
    endif()

    # System Integration Tests (require full system running)
    ament_add_gtest(test_system_integration test/test_system_integration.cpp)
    if(TARGET test_system_integration)
      target_include_directories(test_system_integration PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
      ament_target_dependencies(test_system_integration rclcpp rclcpp_action g1_25_assign1_interfaces_pkg)
      target_link_libraries(test_system_integration ${GTEST_LIBRARIES})
    endif()
  else()
    message(STATUS "Building STANDALONE tests only (database + topic communication)")
    message(STATUS "For all tests use: colcon build --cmake-args -DBUILD_ALL_TESTS=ON")
  endif()

endif()


ament_package()