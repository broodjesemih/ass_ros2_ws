// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from g1_interface_pkg:msg/Student.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/msg/student.hpp"


#ifndef G1_INTERFACE_PKG__MSG__DETAIL__STUDENT__BUILDER_HPP_
#define G1_INTERFACE_PKG__MSG__DETAIL__STUDENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "g1_interface_pkg/msg/detail/student__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace g1_interface_pkg
{

namespace msg
{

namespace builder
{

class Init_Student_course
{
public:
  explicit Init_Student_course(::g1_interface_pkg::msg::Student & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::msg::Student course(::g1_interface_pkg::msg::Student::_course_type arg)
  {
    msg_.course = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::msg::Student msg_;
};

class Init_Student_name
{
public:
  explicit Init_Student_name(::g1_interface_pkg::msg::Student & msg)
  : msg_(msg)
  {}
  Init_Student_course name(::g1_interface_pkg::msg::Student::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_Student_course(msg_);
  }

private:
  ::g1_interface_pkg::msg::Student msg_;
};

class Init_Student_stamp
{
public:
  Init_Student_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Student_name stamp(::g1_interface_pkg::msg::Student::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_Student_name(msg_);
  }

private:
  ::g1_interface_pkg::msg::Student msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::msg::Student>()
{
  return g1_interface_pkg::msg::builder::Init_Student_stamp();
}

}  // namespace g1_interface_pkg

#endif  // G1_INTERFACE_PKG__MSG__DETAIL__STUDENT__BUILDER_HPP_
