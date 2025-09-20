// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from g1_interface_pkg:msg/Tentamen.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/msg/tentamen.hpp"


#ifndef G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__STRUCT_HPP_
#define G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__g1_interface_pkg__msg__Tentamen __attribute__((deprecated))
#else
# define DEPRECATED__g1_interface_pkg__msg__Tentamen __declspec(deprecated)
#endif

namespace g1_interface_pkg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Tentamen_
{
  using Type = Tentamen_<ContainerAllocator>;

  explicit Tentamen_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->student_name = "";
      this->course_name = "";
      this->tentamen_cijfer = 0l;
    }
  }

  explicit Tentamen_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    student_name(_alloc),
    course_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->student_name = "";
      this->course_name = "";
      this->tentamen_cijfer = 0l;
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _student_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _student_name_type student_name;
  using _course_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _course_name_type course_name;
  using _tentamen_cijfer_type =
    int32_t;
  _tentamen_cijfer_type tentamen_cijfer;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__student_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->student_name = _arg;
    return *this;
  }
  Type & set__course_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->course_name = _arg;
    return *this;
  }
  Type & set__tentamen_cijfer(
    const int32_t & _arg)
  {
    this->tentamen_cijfer = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g1_interface_pkg::msg::Tentamen_<ContainerAllocator> *;
  using ConstRawPtr =
    const g1_interface_pkg::msg::Tentamen_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g1_interface_pkg::msg::Tentamen_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g1_interface_pkg::msg::Tentamen_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g1_interface_pkg::msg::Tentamen_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g1_interface_pkg::msg::Tentamen_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g1_interface_pkg::msg::Tentamen_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g1_interface_pkg::msg::Tentamen_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g1_interface_pkg::msg::Tentamen_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g1_interface_pkg::msg::Tentamen_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g1_interface_pkg__msg__Tentamen
    std::shared_ptr<g1_interface_pkg::msg::Tentamen_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g1_interface_pkg__msg__Tentamen
    std::shared_ptr<g1_interface_pkg::msg::Tentamen_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Tentamen_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->student_name != other.student_name) {
      return false;
    }
    if (this->course_name != other.course_name) {
      return false;
    }
    if (this->tentamen_cijfer != other.tentamen_cijfer) {
      return false;
    }
    return true;
  }
  bool operator!=(const Tentamen_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Tentamen_

// alias to use template instance with default allocator
using Tentamen =
  g1_interface_pkg::msg::Tentamen_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace g1_interface_pkg

#endif  // G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__STRUCT_HPP_
