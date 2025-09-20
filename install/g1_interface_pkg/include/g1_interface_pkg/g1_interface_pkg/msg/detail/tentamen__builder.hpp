// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from g1_interface_pkg:msg/Tentamen.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/msg/tentamen.hpp"


#ifndef G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__BUILDER_HPP_
#define G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "g1_interface_pkg/msg/detail/tentamen__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace g1_interface_pkg
{

namespace msg
{

namespace builder
{

class Init_Tentamen_tentamen_cijfer
{
public:
  explicit Init_Tentamen_tentamen_cijfer(::g1_interface_pkg::msg::Tentamen & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::msg::Tentamen tentamen_cijfer(::g1_interface_pkg::msg::Tentamen::_tentamen_cijfer_type arg)
  {
    msg_.tentamen_cijfer = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::msg::Tentamen msg_;
};

class Init_Tentamen_course_name
{
public:
  explicit Init_Tentamen_course_name(::g1_interface_pkg::msg::Tentamen & msg)
  : msg_(msg)
  {}
  Init_Tentamen_tentamen_cijfer course_name(::g1_interface_pkg::msg::Tentamen::_course_name_type arg)
  {
    msg_.course_name = std::move(arg);
    return Init_Tentamen_tentamen_cijfer(msg_);
  }

private:
  ::g1_interface_pkg::msg::Tentamen msg_;
};

class Init_Tentamen_student_name
{
public:
  explicit Init_Tentamen_student_name(::g1_interface_pkg::msg::Tentamen & msg)
  : msg_(msg)
  {}
  Init_Tentamen_course_name student_name(::g1_interface_pkg::msg::Tentamen::_student_name_type arg)
  {
    msg_.student_name = std::move(arg);
    return Init_Tentamen_course_name(msg_);
  }

private:
  ::g1_interface_pkg::msg::Tentamen msg_;
};

class Init_Tentamen_stamp
{
public:
  Init_Tentamen_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Tentamen_student_name stamp(::g1_interface_pkg::msg::Tentamen::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_Tentamen_student_name(msg_);
  }

private:
  ::g1_interface_pkg::msg::Tentamen msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::msg::Tentamen>()
{
  return g1_interface_pkg::msg::builder::Init_Tentamen_stamp();
}

}  // namespace g1_interface_pkg

#endif  // G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__BUILDER_HPP_
