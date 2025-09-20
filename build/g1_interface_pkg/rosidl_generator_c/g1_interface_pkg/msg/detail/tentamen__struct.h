// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from g1_interface_pkg:msg/Tentamen.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/msg/tentamen.h"


#ifndef G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__STRUCT_H_
#define G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'student_name'
// Member 'course_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Tentamen in the package g1_interface_pkg.
typedef struct g1_interface_pkg__msg__Tentamen
{
  builtin_interfaces__msg__Time stamp;
  rosidl_runtime_c__String student_name;
  rosidl_runtime_c__String course_name;
  int32_t tentamen_cijfer;
} g1_interface_pkg__msg__Tentamen;

// Struct for a sequence of g1_interface_pkg__msg__Tentamen.
typedef struct g1_interface_pkg__msg__Tentamen__Sequence
{
  g1_interface_pkg__msg__Tentamen * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__msg__Tentamen__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__STRUCT_H_
