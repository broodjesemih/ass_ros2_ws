// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from g1_interface_pkg:msg/Tentamen.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "g1_interface_pkg/msg/detail/tentamen__rosidl_typesupport_introspection_c.h"
#include "g1_interface_pkg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "g1_interface_pkg/msg/detail/tentamen__functions.h"
#include "g1_interface_pkg/msg/detail/tentamen__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"
// Member `student_name`
// Member `course_name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g1_interface_pkg__msg__Tentamen__init(message_memory);
}

void g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_fini_function(void * message_memory)
{
  g1_interface_pkg__msg__Tentamen__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_message_member_array[4] = {
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg__msg__Tentamen, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "student_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg__msg__Tentamen, student_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "course_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg__msg__Tentamen, course_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "tentamen_cijfer",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg__msg__Tentamen, tentamen_cijfer),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_message_members = {
  "g1_interface_pkg__msg",  // message namespace
  "Tentamen",  // message name
  4,  // number of fields
  sizeof(g1_interface_pkg__msg__Tentamen),
  false,  // has_any_key_member_
  g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_message_member_array,  // message members
  g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_init_function,  // function to initialize message memory (memory has to be allocated)
  g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_message_type_support_handle = {
  0,
  &g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_message_members,
  get_message_typesupport_handle_function,
  &g1_interface_pkg__msg__Tentamen__get_type_hash,
  &g1_interface_pkg__msg__Tentamen__get_type_description,
  &g1_interface_pkg__msg__Tentamen__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g1_interface_pkg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g1_interface_pkg, msg, Tentamen)() {
  g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_message_type_support_handle.typesupport_identifier) {
    g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g1_interface_pkg__msg__Tentamen__rosidl_typesupport_introspection_c__Tentamen_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
