// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from g1_interface_pkg:msg/Student.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/msg/student.hpp"


#ifndef G1_INTERFACE_PKG__MSG__DETAIL__STUDENT__TRAITS_HPP_
#define G1_INTERFACE_PKG__MSG__DETAIL__STUDENT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "g1_interface_pkg/msg/detail/student__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace g1_interface_pkg
{

namespace msg
{

inline void to_flow_style_yaml(
  const Student & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: name
  {
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << ", ";
  }

  // member: course
  {
    out << "course: ";
    rosidl_generator_traits::value_to_yaml(msg.course, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Student & msg,
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

  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "name: ";
    rosidl_generator_traits::value_to_yaml(msg.name, out);
    out << "\n";
  }

  // member: course
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "course: ";
    rosidl_generator_traits::value_to_yaml(msg.course, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Student & msg, bool use_flow_style = false)
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
  const g1_interface_pkg::msg::Student & msg,
  std::ostream & out, size_t indentation = 0)
{
  g1_interface_pkg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g1_interface_pkg::msg::to_yaml() instead")]]
inline std::string to_yaml(const g1_interface_pkg::msg::Student & msg)
{
  return g1_interface_pkg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<g1_interface_pkg::msg::Student>()
{
  return "g1_interface_pkg::msg::Student";
}

template<>
inline const char * name<g1_interface_pkg::msg::Student>()
{
  return "g1_interface_pkg/msg/Student";
}

template<>
struct has_fixed_size<g1_interface_pkg::msg::Student>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g1_interface_pkg::msg::Student>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<g1_interface_pkg::msg::Student>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // G1_INTERFACE_PKG__MSG__DETAIL__STUDENT__TRAITS_HPP_
