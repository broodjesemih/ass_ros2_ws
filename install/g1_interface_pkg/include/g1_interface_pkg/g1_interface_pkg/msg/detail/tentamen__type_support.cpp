// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from g1_interface_pkg:msg/Tentamen.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "g1_interface_pkg/msg/detail/tentamen__functions.h"
#include "g1_interface_pkg/msg/detail/tentamen__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace g1_interface_pkg
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Tentamen_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) g1_interface_pkg::msg::Tentamen(_init);
}

void Tentamen_fini_function(void * message_memory)
{
  auto typed_message = static_cast<g1_interface_pkg::msg::Tentamen *>(message_memory);
  typed_message->~Tentamen();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Tentamen_message_member_array[4] = {
  {
    "stamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg::msg::Tentamen, stamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "student_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg::msg::Tentamen, student_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "course_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg::msg::Tentamen, course_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "tentamen_cijfer",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg::msg::Tentamen, tentamen_cijfer),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Tentamen_message_members = {
  "g1_interface_pkg::msg",  // message namespace
  "Tentamen",  // message name
  4,  // number of fields
  sizeof(g1_interface_pkg::msg::Tentamen),
  false,  // has_any_key_member_
  Tentamen_message_member_array,  // message members
  Tentamen_init_function,  // function to initialize message memory (memory has to be allocated)
  Tentamen_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Tentamen_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Tentamen_message_members,
  get_message_typesupport_handle_function,
  &g1_interface_pkg__msg__Tentamen__get_type_hash,
  &g1_interface_pkg__msg__Tentamen__get_type_description,
  &g1_interface_pkg__msg__Tentamen__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace g1_interface_pkg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g1_interface_pkg::msg::Tentamen>()
{
  return &::g1_interface_pkg::msg::rosidl_typesupport_introspection_cpp::Tentamen_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g1_interface_pkg, msg, Tentamen)() {
  return &::g1_interface_pkg::msg::rosidl_typesupport_introspection_cpp::Tentamen_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
