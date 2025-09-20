// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from g1_interface_pkg:msg/Student.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "g1_interface_pkg/msg/detail/student__rosidl_typesupport_introspection_c.h"
#include "g1_interface_pkg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "g1_interface_pkg/msg/detail/student__functions.h"
#include "g1_interface_pkg/msg/detail/student__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `name`
// Member `course`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g1_interface_pkg__msg__Student__init(message_memory);
}

void g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_fini_function(void * message_memory)
{
  g1_interface_pkg__msg__Student__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_message_member_array[3] = {
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg__msg__Student, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg__msg__Student, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "course",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg__msg__Student, course),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_message_members = {
  "g1_interface_pkg__msg",  // message namespace
  "Student",  // message name
  3,  // number of fields
  sizeof(g1_interface_pkg__msg__Student),
  false,  // has_any_key_member_
  g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_message_member_array,  // message members
  g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_init_function,  // function to initialize message memory (memory has to be allocated)
  g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_message_type_support_handle = {
  0,
  &g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_message_members,
  get_message_typesupport_handle_function,
  &g1_interface_pkg__msg__Student__get_type_hash,
  &g1_interface_pkg__msg__Student__get_type_description,
  &g1_interface_pkg__msg__Student__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g1_interface_pkg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g1_interface_pkg, msg, Student)() {
  g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_message_type_support_handle.typesupport_identifier) {
    g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g1_interface_pkg__msg__Student__rosidl_typesupport_introspection_c__Student_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
