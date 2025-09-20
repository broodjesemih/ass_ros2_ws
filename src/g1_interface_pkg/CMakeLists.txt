cmake_minimum_required(VERSION 3.5)
project(g1_interface_pkg)

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Student.msg"
  "msg/Tentamen.msg"
  "srv/Tentamens.srv"
  "action/Herkanser.action"
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()