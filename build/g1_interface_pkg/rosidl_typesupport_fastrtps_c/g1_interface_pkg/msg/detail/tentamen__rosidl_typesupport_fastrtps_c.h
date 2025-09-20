// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from g1_interface_pkg:msg/Tentamen.idl
// generated code does not contain a copyright notice
#ifndef G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "g1_interface_pkg/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "g1_interface_pkg/msg/detail/tentamen__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_g1_interface_pkg
bool cdr_serialize_g1_interface_pkg__msg__Tentamen(
  const g1_interface_pkg__msg__Tentamen * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_g1_interface_pkg
bool cdr_deserialize_g1_interface_pkg__msg__Tentamen(
  eprosima::fastcdr::Cdr &,
  g1_interface_pkg__msg__Tentamen * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_g1_interface_pkg
size_t get_serialized_size_g1_interface_pkg__msg__Tentamen(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_g1_interface_pkg
size_t max_serialized_size_g1_interface_pkg__msg__Tentamen(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_g1_interface_pkg
bool cdr_serialize_key_g1_interface_pkg__msg__Tentamen(
  const g1_interface_pkg__msg__Tentamen * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_g1_interface_pkg
size_t get_serialized_size_key_g1_interface_pkg__msg__Tentamen(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_g1_interface_pkg
size_t max_serialized_size_key_g1_interface_pkg__msg__Tentamen(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_g1_interface_pkg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, g1_interface_pkg, msg, Tentamen)();

#ifdef __cplusplus
}
#endif

#endif  // G1_INTERFACE_PKG__MSG__DETAIL__TENTAMEN__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
