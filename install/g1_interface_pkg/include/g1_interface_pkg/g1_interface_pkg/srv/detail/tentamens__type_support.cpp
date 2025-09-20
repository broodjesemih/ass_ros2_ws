// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from g1_interface_pkg:srv/Tentamens.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "g1_interface_pkg/srv/detail/tentamens__functions.h"
#include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace g1_interface_pkg
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void Tentamens_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) g1_interface_pkg::srv::Tentamens_Request(_init);
}

void Tentamens_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<g1_interface_pkg::srv::Tentamens_Request *>(message_memory);
  typed_message->~Tentamens_Request();
}

size_t size_function__Tentamens_Request__tentamen_cijfers(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Tentamens_Request__tentamen_cijfers(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void * get_function__Tentamens_Request__tentamen_cijfers(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__Tentamens_Request__tentamen_cijfers(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int32_t *>(
    get_const_function__Tentamens_Request__tentamen_cijfers(untyped_member, index));
  auto & value = *reinterpret_cast<int32_t *>(untyped_value);
  value = item;
}

void assign_function__Tentamens_Request__tentamen_cijfers(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int32_t *>(
    get_function__Tentamens_Request__tentamen_cijfers(untyped_member, index));
  const auto & value = *reinterpret_cast<const int32_t *>(untyped_value);
  item = value;
}

void resize_function__Tentamens_Request__tentamen_cijfers(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Tentamens_Request_message_member_array[3] = {
  {
    "student_name",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg::srv::Tentamens_Request, student_name),  // bytes offset in struct
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
    offsetof(g1_interface_pkg::srv::Tentamens_Request, course_name),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "tentamen_cijfers",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg::srv::Tentamens_Request, tentamen_cijfers),  // bytes offset in struct
    nullptr,  // default value
    size_function__Tentamens_Request__tentamen_cijfers,  // size() function pointer
    get_const_function__Tentamens_Request__tentamen_cijfers,  // get_const(index) function pointer
    get_function__Tentamens_Request__tentamen_cijfers,  // get(index) function pointer
    fetch_function__Tentamens_Request__tentamen_cijfers,  // fetch(index, &value) function pointer
    assign_function__Tentamens_Request__tentamen_cijfers,  // assign(index, value) function pointer
    resize_function__Tentamens_Request__tentamen_cijfers  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Tentamens_Request_message_members = {
  "g1_interface_pkg::srv",  // message namespace
  "Tentamens_Request",  // message name
  3,  // number of fields
  sizeof(g1_interface_pkg::srv::Tentamens_Request),
  false,  // has_any_key_member_
  Tentamens_Request_message_member_array,  // message members
  Tentamens_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  Tentamens_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Tentamens_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Tentamens_Request_message_members,
  get_message_typesupport_handle_function,
  &g1_interface_pkg__srv__Tentamens_Request__get_type_hash,
  &g1_interface_pkg__srv__Tentamens_Request__get_type_description,
  &g1_interface_pkg__srv__Tentamens_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace g1_interface_pkg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Request>()
{
  return &::g1_interface_pkg::srv::rosidl_typesupport_introspection_cpp::Tentamens_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g1_interface_pkg, srv, Tentamens_Request)() {
  return &::g1_interface_pkg::srv::rosidl_typesupport_introspection_cpp::Tentamens_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__functions.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace g1_interface_pkg
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void Tentamens_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) g1_interface_pkg::srv::Tentamens_Response(_init);
}

void Tentamens_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<g1_interface_pkg::srv::Tentamens_Response *>(message_memory);
  typed_message->~Tentamens_Response();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Tentamens_Response_message_member_array[2] = {
  {
    "final_cijfer",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg::srv::Tentamens_Response, final_cijfer),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg::srv::Tentamens_Response, message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Tentamens_Response_message_members = {
  "g1_interface_pkg::srv",  // message namespace
  "Tentamens_Response",  // message name
  2,  // number of fields
  sizeof(g1_interface_pkg::srv::Tentamens_Response),
  false,  // has_any_key_member_
  Tentamens_Response_message_member_array,  // message members
  Tentamens_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  Tentamens_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Tentamens_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Tentamens_Response_message_members,
  get_message_typesupport_handle_function,
  &g1_interface_pkg__srv__Tentamens_Response__get_type_hash,
  &g1_interface_pkg__srv__Tentamens_Response__get_type_description,
  &g1_interface_pkg__srv__Tentamens_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace g1_interface_pkg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Response>()
{
  return &::g1_interface_pkg::srv::rosidl_typesupport_introspection_cpp::Tentamens_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g1_interface_pkg, srv, Tentamens_Response)() {
  return &::g1_interface_pkg::srv::rosidl_typesupport_introspection_cpp::Tentamens_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__functions.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace g1_interface_pkg
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void Tentamens_Event_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) g1_interface_pkg::srv::Tentamens_Event(_init);
}

void Tentamens_Event_fini_function(void * message_memory)
{
  auto typed_message = static_cast<g1_interface_pkg::srv::Tentamens_Event *>(message_memory);
  typed_message->~Tentamens_Event();
}

size_t size_function__Tentamens_Event__request(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<g1_interface_pkg::srv::Tentamens_Request> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Tentamens_Event__request(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<g1_interface_pkg::srv::Tentamens_Request> *>(untyped_member);
  return &member[index];
}

void * get_function__Tentamens_Event__request(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<g1_interface_pkg::srv::Tentamens_Request> *>(untyped_member);
  return &member[index];
}

void fetch_function__Tentamens_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const g1_interface_pkg::srv::Tentamens_Request *>(
    get_const_function__Tentamens_Event__request(untyped_member, index));
  auto & value = *reinterpret_cast<g1_interface_pkg::srv::Tentamens_Request *>(untyped_value);
  value = item;
}

void assign_function__Tentamens_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<g1_interface_pkg::srv::Tentamens_Request *>(
    get_function__Tentamens_Event__request(untyped_member, index));
  const auto & value = *reinterpret_cast<const g1_interface_pkg::srv::Tentamens_Request *>(untyped_value);
  item = value;
}

void resize_function__Tentamens_Event__request(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<g1_interface_pkg::srv::Tentamens_Request> *>(untyped_member);
  member->resize(size);
}

size_t size_function__Tentamens_Event__response(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<g1_interface_pkg::srv::Tentamens_Response> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Tentamens_Event__response(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<g1_interface_pkg::srv::Tentamens_Response> *>(untyped_member);
  return &member[index];
}

void * get_function__Tentamens_Event__response(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<g1_interface_pkg::srv::Tentamens_Response> *>(untyped_member);
  return &member[index];
}

void fetch_function__Tentamens_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const g1_interface_pkg::srv::Tentamens_Response *>(
    get_const_function__Tentamens_Event__response(untyped_member, index));
  auto & value = *reinterpret_cast<g1_interface_pkg::srv::Tentamens_Response *>(untyped_value);
  value = item;
}

void assign_function__Tentamens_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<g1_interface_pkg::srv::Tentamens_Response *>(
    get_function__Tentamens_Event__response(untyped_member, index));
  const auto & value = *reinterpret_cast<const g1_interface_pkg::srv::Tentamens_Response *>(untyped_value);
  item = value;
}

void resize_function__Tentamens_Event__response(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<g1_interface_pkg::srv::Tentamens_Response> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Tentamens_Event_message_member_array[3] = {
  {
    "info",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<service_msgs::msg::ServiceEventInfo>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g1_interface_pkg::srv::Tentamens_Event, info),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "request",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Request>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(g1_interface_pkg::srv::Tentamens_Event, request),  // bytes offset in struct
    nullptr,  // default value
    size_function__Tentamens_Event__request,  // size() function pointer
    get_const_function__Tentamens_Event__request,  // get_const(index) function pointer
    get_function__Tentamens_Event__request,  // get(index) function pointer
    fetch_function__Tentamens_Event__request,  // fetch(index, &value) function pointer
    assign_function__Tentamens_Event__request,  // assign(index, value) function pointer
    resize_function__Tentamens_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Response>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(g1_interface_pkg::srv::Tentamens_Event, response),  // bytes offset in struct
    nullptr,  // default value
    size_function__Tentamens_Event__response,  // size() function pointer
    get_const_function__Tentamens_Event__response,  // get_const(index) function pointer
    get_function__Tentamens_Event__response,  // get(index) function pointer
    fetch_function__Tentamens_Event__response,  // fetch(index, &value) function pointer
    assign_function__Tentamens_Event__response,  // assign(index, value) function pointer
    resize_function__Tentamens_Event__response  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Tentamens_Event_message_members = {
  "g1_interface_pkg::srv",  // message namespace
  "Tentamens_Event",  // message name
  3,  // number of fields
  sizeof(g1_interface_pkg::srv::Tentamens_Event),
  false,  // has_any_key_member_
  Tentamens_Event_message_member_array,  // message members
  Tentamens_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  Tentamens_Event_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Tentamens_Event_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Tentamens_Event_message_members,
  get_message_typesupport_handle_function,
  &g1_interface_pkg__srv__Tentamens_Event__get_type_hash,
  &g1_interface_pkg__srv__Tentamens_Event__get_type_description,
  &g1_interface_pkg__srv__Tentamens_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace g1_interface_pkg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Event>()
{
  return &::g1_interface_pkg::srv::rosidl_typesupport_introspection_cpp::Tentamens_Event_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g1_interface_pkg, srv, Tentamens_Event)() {
  return &::g1_interface_pkg::srv::rosidl_typesupport_introspection_cpp::Tentamens_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__functions.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace g1_interface_pkg
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers Tentamens_service_members = {
  "g1_interface_pkg::srv",  // service namespace
  "Tentamens",  // service name
  // the following fields are initialized below on first access
  // see get_service_type_support_handle<g1_interface_pkg::srv::Tentamens>()
  nullptr,  // request message
  nullptr,  // response message
  nullptr,  // event message
};

static const rosidl_service_type_support_t Tentamens_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Tentamens_service_members,
  get_service_typesupport_handle_function,
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Request>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Response>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<g1_interface_pkg::srv::Tentamens>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<g1_interface_pkg::srv::Tentamens>,
  &g1_interface_pkg__srv__Tentamens__get_type_hash,
  &g1_interface_pkg__srv__Tentamens__get_type_description,
  &g1_interface_pkg__srv__Tentamens__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace g1_interface_pkg


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<g1_interface_pkg::srv::Tentamens>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::g1_interface_pkg::srv::rosidl_typesupport_introspection_cpp::Tentamens_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure all of the service_members are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr ||
    service_members->event_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::g1_interface_pkg::srv::Tentamens_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::g1_interface_pkg::srv::Tentamens_Response
      >()->data
      );
    // initialize the event_members_ with the static function from the external library
    service_members->event_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::g1_interface_pkg::srv::Tentamens_Event
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g1_interface_pkg, srv, Tentamens)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<g1_interface_pkg::srv::Tentamens>();
}

#ifdef __cplusplus
}
#endif
