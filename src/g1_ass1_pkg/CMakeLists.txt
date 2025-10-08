cmake_minimum_required(VERSION 3.8)
project(g1_ass1_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Dependencies
find_package(g1_interface_pkg REQUIRED)
find_package(ament_cmake REQUIRED)            # cmake package
find_package(rclcpp REQUIRED)                 # nodig voor alle nodes
find_package(rclcpp_action REQUIRED)          # nodig als er een actionserver node wordt gemaakt
find_package(std_msgs REQUIRED)               # gebruik maken von standaard messages
find_package(builtin_interfaces REQUIRED)     # nodig voor Time messages
find_package(rosidl_default_generators REQUIRED) # nodig om custom messages te gebruiken

# Find PostgreSQL and libpqxx
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Create a library from database.cpp
add_library(database_lib src/database.cpp)
target_include_directories(database_lib PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(database_lib ${PQXX_LIBRARIES})
target_compile_options(database_lib PRIVATE ${PQXX_CFLAGS_OTHER})

# Executables
add_executable(tentamen_result_generator src/tentamen_result_generator.cpp)
ament_target_dependencies(tentamen_result_generator rclcpp g1_interface_pkg)
target_link_libraries(tentamen_result_generator database_lib)

add_executable(final_cijfer_determinator src/final_cijfer_determinator.cpp)
ament_target_dependencies(final_cijfer_determinator rclcpp g1_interface_pkg)
target_link_libraries(final_cijfer_determinator database_lib)

add_executable(cijfer_calculator src/cijfer_calculator.cpp)
ament_target_dependencies(cijfer_calculator rclcpp g1_interface_pkg)
target_link_libraries(cijfer_calculator database_lib)

add_executable(herkansing_cijfer_determinator src/herkansing_cijfer_determinator.cpp)
ament_target_dependencies(herkansing_cijfer_determinator rclcpp_action rclcpp g1_interface_pkg)
target_link_libraries(herkansing_cijfer_determinator database_lib)

add_executable(herkansing_scheduler src/herkansing_scheduler.cpp)
ament_target_dependencies(herkansing_scheduler rclcpp_action rclcpp g1_interface_pkg)
target_link_libraries(herkansing_scheduler database_lib)



# # Executables
# add_executable(tentamen_result_generator src/tentamen_result_generator.cpp)
# ament_target_dependencies(tentamen_result_generator rclcpp g1_interface_pkg)

# add_executable(final_cijfer_determinator src/final_cijfer_determinator.cpp)
# ament_target_dependencies(final_cijfer_determinator rclcpp g1_interface_pkg)

# add_executable(cijfer_calculator src/cijfer_calculator.cpp)
# ament_target_dependencies(cijfer_calculator rclcpp g1_interface_pkg)

# add_executable(herkansing_cijfer_determinator src/herkansing_cijfer_determinator.cpp)
# ament_target_dependencies(herkansing_cijfer_determinator rclcpp_action rclcpp g1_interface_pkg)

# add_executable(herkansing_scheduler src/herkansing_scheduler.cpp)
# ament_target_dependencies(herkansing_scheduler rclcpp_action rclcpp g1_interface_pkg)

install(TARGETS
  tentamen_result_generator
  final_cijfer_determinator
  cijfer_calculator
  herkansing_cijfer_determinator
  herkansing_scheduler
  DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()


ament_package()