// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from g1_interface_pkg:msg/Student.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/msg/student.hpp"


#ifndef G1_INTERFACE_PKG__MSG__DETAIL__STUDENT__STRUCT_HPP_
#define G1_INTERFACE_PKG__MSG__DETAIL__STUDENT__STRUCT_HPP_

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
# define DEPRECATED__g1_interface_pkg__msg__Student __attribute__((deprecated))
#else
# define DEPRECATED__g1_interface_pkg__msg__Student __declspec(deprecated)
#endif

namespace g1_interface_pkg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Student_
{
  using Type = Student_<ContainerAllocator>;

  explicit Student_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->course = "";
    }
  }

  explicit Student_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    name(_alloc),
    course(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->course = "";
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _course_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _course_type course;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__course(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->course = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g1_interface_pkg::msg::Student_<ContainerAllocator> *;
  using ConstRawPtr =
    const g1_interface_pkg::msg::Student_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g1_interface_pkg::msg::Student_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g1_interface_pkg::msg::Student_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g1_interface_pkg::msg::Student_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g1_interface_pkg::msg::Student_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g1_interface_pkg::msg::Student_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g1_interface_pkg::msg::Student_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g1_interface_pkg::msg::Student_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g1_interface_pkg::msg::Student_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g1_interface_pkg__msg__Student
    std::shared_ptr<g1_interface_pkg::msg::Student_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g1_interface_pkg__msg__Student
    std::shared_ptr<g1_interface_pkg::msg::Student_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Student_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->name != other.name) {
      return false;
    }
    if (this->course != other.course) {
      return false;
    }
    return true;
  }
  bool operator!=(const Student_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Student_

// alias to use template instance with default allocator
using Student =
  g1_interface_pkg::msg::Student_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace g1_interface_pkg

#endif  // G1_INTERFACE_PKG__MSG__DETAIL__STUDENT__STRUCT_HPP_
