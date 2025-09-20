// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from g1_interface_pkg:srv/Tentamens.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/srv/tentamens.h"


#ifndef G1_INTERFACE_PKG__SRV__DETAIL__TENTAMENS__STRUCT_H_
#define G1_INTERFACE_PKG__SRV__DETAIL__TENTAMENS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'student_name'
// Member 'course_name'
#include "rosidl_runtime_c/string.h"
// Member 'tentamen_cijfers'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/Tentamens in the package g1_interface_pkg.
typedef struct g1_interface_pkg__srv__Tentamens_Request
{
  rosidl_runtime_c__String student_name;
  rosidl_runtime_c__String course_name;
  rosidl_runtime_c__int32__Sequence tentamen_cijfers;
} g1_interface_pkg__srv__Tentamens_Request;

// Struct for a sequence of g1_interface_pkg__srv__Tentamens_Request.
typedef struct g1_interface_pkg__srv__Tentamens_Request__Sequence
{
  g1_interface_pkg__srv__Tentamens_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__srv__Tentamens_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Tentamens in the package g1_interface_pkg.
typedef struct g1_interface_pkg__srv__Tentamens_Response
{
  int32_t final_cijfer;
  rosidl_runtime_c__String message;
} g1_interface_pkg__srv__Tentamens_Response;

// Struct for a sequence of g1_interface_pkg__srv__Tentamens_Response.
typedef struct g1_interface_pkg__srv__Tentamens_Response__Sequence
{
  g1_interface_pkg__srv__Tentamens_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__srv__Tentamens_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  g1_interface_pkg__srv__Tentamens_Event__request__MAX_SIZE = 1
};
// response
enum
{
  g1_interface_pkg__srv__Tentamens_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/Tentamens in the package g1_interface_pkg.
typedef struct g1_interface_pkg__srv__Tentamens_Event
{
  service_msgs__msg__ServiceEventInfo info;
  g1_interface_pkg__srv__Tentamens_Request__Sequence request;
  g1_interface_pkg__srv__Tentamens_Response__Sequence response;
} g1_interface_pkg__srv__Tentamens_Event;

// Struct for a sequence of g1_interface_pkg__srv__Tentamens_Event.
typedef struct g1_interface_pkg__srv__Tentamens_Event__Sequence
{
  g1_interface_pkg__srv__Tentamens_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__srv__Tentamens_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // G1_INTERFACE_PKG__SRV__DETAIL__TENTAMENS__STRUCT_H_
