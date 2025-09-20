// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from g1_interface_pkg:msg/Tentamen.idl
// generated code does not contain a copyright notice
#include "g1_interface_pkg/msg/detail/tentamen__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `student_name`
// Member `course_name`
#include "rosidl_runtime_c/string_functions.h"

bool
g1_interface_pkg__msg__Tentamen__init(g1_interface_pkg__msg__Tentamen * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    g1_interface_pkg__msg__Tentamen__fini(msg);
    return false;
  }
  // student_name
  if (!rosidl_runtime_c__String__init(&msg->student_name)) {
    g1_interface_pkg__msg__Tentamen__fini(msg);
    return false;
  }
  // course_name
  if (!rosidl_runtime_c__String__init(&msg->course_name)) {
    g1_interface_pkg__msg__Tentamen__fini(msg);
    return false;
  }
  // tentamen_cijfer
  return true;
}

void
g1_interface_pkg__msg__Tentamen__fini(g1_interface_pkg__msg__Tentamen * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // student_name
  rosidl_runtime_c__String__fini(&msg->student_name);
  // course_name
  rosidl_runtime_c__String__fini(&msg->course_name);
  // tentamen_cijfer
}

bool
g1_interface_pkg__msg__Tentamen__are_equal(const g1_interface_pkg__msg__Tentamen * lhs, const g1_interface_pkg__msg__Tentamen * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // student_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->student_name), &(rhs->student_name)))
  {
    return false;
  }
  // course_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->course_name), &(rhs->course_name)))
  {
    return false;
  }
  // tentamen_cijfer
  if (lhs->tentamen_cijfer != rhs->tentamen_cijfer) {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__msg__Tentamen__copy(
  const g1_interface_pkg__msg__Tentamen * input,
  g1_interface_pkg__msg__Tentamen * output)
{
  if (!input || !output) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // student_name
  if (!rosidl_runtime_c__String__copy(
      &(input->student_name), &(output->student_name)))
  {
    return false;
  }
  // course_name
  if (!rosidl_runtime_c__String__copy(
      &(input->course_name), &(output->course_name)))
  {
    return false;
  }
  // tentamen_cijfer
  output->tentamen_cijfer = input->tentamen_cijfer;
  return true;
}

g1_interface_pkg__msg__Tentamen *
g1_interface_pkg__msg__Tentamen__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__msg__Tentamen * msg = (g1_interface_pkg__msg__Tentamen *)allocator.allocate(sizeof(g1_interface_pkg__msg__Tentamen), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__msg__Tentamen));
  bool success = g1_interface_pkg__msg__Tentamen__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__msg__Tentamen__destroy(g1_interface_pkg__msg__Tentamen * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__msg__Tentamen__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__msg__Tentamen__Sequence__init(g1_interface_pkg__msg__Tentamen__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__msg__Tentamen * data = NULL;

  if (size) {
    data = (g1_interface_pkg__msg__Tentamen *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__msg__Tentamen), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__msg__Tentamen__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__msg__Tentamen__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
g1_interface_pkg__msg__Tentamen__Sequence__fini(g1_interface_pkg__msg__Tentamen__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      g1_interface_pkg__msg__Tentamen__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

g1_interface_pkg__msg__Tentamen__Sequence *
g1_interface_pkg__msg__Tentamen__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__msg__Tentamen__Sequence * array = (g1_interface_pkg__msg__Tentamen__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__msg__Tentamen__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__msg__Tentamen__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__msg__Tentamen__Sequence__destroy(g1_interface_pkg__msg__Tentamen__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__msg__Tentamen__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__msg__Tentamen__Sequence__are_equal(const g1_interface_pkg__msg__Tentamen__Sequence * lhs, const g1_interface_pkg__msg__Tentamen__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__msg__Tentamen__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__msg__Tentamen__Sequence__copy(
  const g1_interface_pkg__msg__Tentamen__Sequence * input,
  g1_interface_pkg__msg__Tentamen__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__msg__Tentamen);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__msg__Tentamen * data =
      (g1_interface_pkg__msg__Tentamen *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__msg__Tentamen__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__msg__Tentamen__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__msg__Tentamen__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
