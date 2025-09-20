// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from g1_interface_pkg:action/Herkanser.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/action/herkanser.h"


#ifndef G1_INTERFACE_PKG__ACTION__DETAIL__HERKANSER__STRUCT_H_
#define G1_INTERFACE_PKG__ACTION__DETAIL__HERKANSER__STRUCT_H_

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

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_Goal
{
  rosidl_runtime_c__String student_name;
  rosidl_runtime_c__String course_name;
} g1_interface_pkg__action__Herkanser_Goal;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_Goal.
typedef struct g1_interface_pkg__action__Herkanser_Goal__Sequence
{
  g1_interface_pkg__action__Herkanser_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_Result
{
  int32_t final_cijfer;
  rosidl_runtime_c__String message;
} g1_interface_pkg__action__Herkanser_Result;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_Result.
typedef struct g1_interface_pkg__action__Herkanser_Result__Sequence
{
  g1_interface_pkg__action__Herkanser_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'status'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_Feedback
{
  float progress;
  rosidl_runtime_c__String status;
} g1_interface_pkg__action__Herkanser_Feedback;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_Feedback.
typedef struct g1_interface_pkg__action__Herkanser_Feedback__Sequence
{
  g1_interface_pkg__action__Herkanser_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "g1_interface_pkg/action/detail/herkanser__struct.h"

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  g1_interface_pkg__action__Herkanser_Goal goal;
} g1_interface_pkg__action__Herkanser_SendGoal_Request;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_SendGoal_Request.
typedef struct g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence
{
  g1_interface_pkg__action__Herkanser_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} g1_interface_pkg__action__Herkanser_SendGoal_Response;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_SendGoal_Response.
typedef struct g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence
{
  g1_interface_pkg__action__Herkanser_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  g1_interface_pkg__action__Herkanser_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  g1_interface_pkg__action__Herkanser_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence request;
  g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence response;
} g1_interface_pkg__action__Herkanser_SendGoal_Event;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_SendGoal_Event.
typedef struct g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence
{
  g1_interface_pkg__action__Herkanser_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} g1_interface_pkg__action__Herkanser_GetResult_Request;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_GetResult_Request.
typedef struct g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence
{
  g1_interface_pkg__action__Herkanser_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "g1_interface_pkg/action/detail/herkanser__struct.h"

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_GetResult_Response
{
  int8_t status;
  g1_interface_pkg__action__Herkanser_Result result;
} g1_interface_pkg__action__Herkanser_GetResult_Response;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_GetResult_Response.
typedef struct g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence
{
  g1_interface_pkg__action__Herkanser_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  g1_interface_pkg__action__Herkanser_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  g1_interface_pkg__action__Herkanser_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence request;
  g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence response;
} g1_interface_pkg__action__Herkanser_GetResult_Event;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_GetResult_Event.
typedef struct g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence
{
  g1_interface_pkg__action__Herkanser_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "g1_interface_pkg/action/detail/herkanser__struct.h"

/// Struct defined in action/Herkanser in the package g1_interface_pkg.
typedef struct g1_interface_pkg__action__Herkanser_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  g1_interface_pkg__action__Herkanser_Feedback feedback;
} g1_interface_pkg__action__Herkanser_FeedbackMessage;

// Struct for a sequence of g1_interface_pkg__action__Herkanser_FeedbackMessage.
typedef struct g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence
{
  g1_interface_pkg__action__Herkanser_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // G1_INTERFACE_PKG__ACTION__DETAIL__HERKANSER__STRUCT_H_
