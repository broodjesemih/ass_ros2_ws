// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from g1_interface_pkg:msg/Tentamen.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/msg/tentamen.hpp"


#ifndef G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__TRAITS_HPP_
#define G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "g1_interface_pkg/msg/detail/tentamen__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace g1_interface_pkg
{

namespace msg
{

inline void to_flow_style_yaml(
  const Tentamen & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: student_name
  {
    out << "student_name: ";
    rosidl_generator_traits::value_to_yaml(msg.student_name, out);
    out << ", ";
  }

  // member: course_name
  {
    out << "course_name: ";
    rosidl_generator_traits::value_to_yaml(msg.course_name, out);
    out << ", ";
  }

  // member: tentamen_cijfer
  {
    out << "tentamen_cijfer: ";
    rosidl_generator_traits::value_to_yaml(msg.tentamen_cijfer, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Tentamen & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: student_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "student_name: ";
    rosidl_generator_traits::value_to_yaml(msg.student_name, out);
    out << "\n";
  }

  // member: course_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "course_name: ";
    rosidl_generator_traits::value_to_yaml(msg.course_name, out);
    out << "\n";
  }

  // member: tentamen_cijfer
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tentamen_cijfer: ";
    rosidl_generator_traits::value_to_yaml(msg.tentamen_cijfer, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Tentamen & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace g1_interface_pkg

namespace rosidl_generator_traits
{

[[deprecated("use g1_interface_pkg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g1_interface_pkg::msg::Tentamen & msg,
  std::ostream & out, size_t indentation = 0)
{
  g1_interface_pkg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g1_interface_pkg::msg::to_yaml() instead")]]
inline std::string to_yaml(const g1_interface_pkg::msg::Tentamen & msg)
{
  return g1_interface_pkg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<g1_interface_pkg::msg::Tentamen>()
{
  return "g1_interface_pkg::msg::Tentamen";
}

template<>
inline const char * name<g1_interface_pkg::msg::Tentamen>()
{
  return "g1_interface_pkg/msg/Tentamen";
}

template<>
struct has_fixed_size<g1_interface_pkg::msg::Tentamen>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g1_interface_pkg::msg::Tentamen>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<g1_interface_pkg::msg::Tentamen>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__TRAITS_HPP_
