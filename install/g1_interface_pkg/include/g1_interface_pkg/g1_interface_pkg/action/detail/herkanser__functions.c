// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from g1_interface_pkg:action/Herkanser.idl
// generated code does not contain a copyright notice
#include "g1_interface_pkg/action/detail/herkanser__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `student_name`
// Member `course_name`
#include "rosidl_runtime_c/string_functions.h"

bool
g1_interface_pkg__action__Herkanser_Goal__init(g1_interface_pkg__action__Herkanser_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // student_name
  if (!rosidl_runtime_c__String__init(&msg->student_name)) {
    g1_interface_pkg__action__Herkanser_Goal__fini(msg);
    return false;
  }
  // course_name
  if (!rosidl_runtime_c__String__init(&msg->course_name)) {
    g1_interface_pkg__action__Herkanser_Goal__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_Goal__fini(g1_interface_pkg__action__Herkanser_Goal * msg)
{
  if (!msg) {
    return;
  }
  // student_name
  rosidl_runtime_c__String__fini(&msg->student_name);
  // course_name
  rosidl_runtime_c__String__fini(&msg->course_name);
}

bool
g1_interface_pkg__action__Herkanser_Goal__are_equal(const g1_interface_pkg__action__Herkanser_Goal * lhs, const g1_interface_pkg__action__Herkanser_Goal * rhs)
{
  if (!lhs || !rhs) {
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
  return true;
}

bool
g1_interface_pkg__action__Herkanser_Goal__copy(
  const g1_interface_pkg__action__Herkanser_Goal * input,
  g1_interface_pkg__action__Herkanser_Goal * output)
{
  if (!input || !output) {
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
  return true;
}

g1_interface_pkg__action__Herkanser_Goal *
g1_interface_pkg__action__Herkanser_Goal__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_Goal * msg = (g1_interface_pkg__action__Herkanser_Goal *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_Goal));
  bool success = g1_interface_pkg__action__Herkanser_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_Goal__destroy(g1_interface_pkg__action__Herkanser_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_Goal__Sequence__init(g1_interface_pkg__action__Herkanser_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_Goal * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_Goal *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_Goal__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_Goal__Sequence__fini(g1_interface_pkg__action__Herkanser_Goal__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_Goal__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_Goal__Sequence *
g1_interface_pkg__action__Herkanser_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_Goal__Sequence * array = (g1_interface_pkg__action__Herkanser_Goal__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_Goal__Sequence__destroy(g1_interface_pkg__action__Herkanser_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_Goal__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_Goal__Sequence * lhs, const g1_interface_pkg__action__Herkanser_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_Goal__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_Goal__Sequence * input,
  g1_interface_pkg__action__Herkanser_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_Goal * data =
      (g1_interface_pkg__action__Herkanser_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
g1_interface_pkg__action__Herkanser_Result__init(g1_interface_pkg__action__Herkanser_Result * msg)
{
  if (!msg) {
    return false;
  }
  // final_cijfer
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    g1_interface_pkg__action__Herkanser_Result__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_Result__fini(g1_interface_pkg__action__Herkanser_Result * msg)
{
  if (!msg) {
    return;
  }
  // final_cijfer
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
g1_interface_pkg__action__Herkanser_Result__are_equal(const g1_interface_pkg__action__Herkanser_Result * lhs, const g1_interface_pkg__action__Herkanser_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // final_cijfer
  if (lhs->final_cijfer != rhs->final_cijfer) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_Result__copy(
  const g1_interface_pkg__action__Herkanser_Result * input,
  g1_interface_pkg__action__Herkanser_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // final_cijfer
  output->final_cijfer = input->final_cijfer;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__action__Herkanser_Result *
g1_interface_pkg__action__Herkanser_Result__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_Result * msg = (g1_interface_pkg__action__Herkanser_Result *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_Result));
  bool success = g1_interface_pkg__action__Herkanser_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_Result__destroy(g1_interface_pkg__action__Herkanser_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_Result__Sequence__init(g1_interface_pkg__action__Herkanser_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_Result * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_Result *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_Result__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_Result__Sequence__fini(g1_interface_pkg__action__Herkanser_Result__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_Result__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_Result__Sequence *
g1_interface_pkg__action__Herkanser_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_Result__Sequence * array = (g1_interface_pkg__action__Herkanser_Result__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_Result__Sequence__destroy(g1_interface_pkg__action__Herkanser_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_Result__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_Result__Sequence * lhs, const g1_interface_pkg__action__Herkanser_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_Result__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_Result__Sequence * input,
  g1_interface_pkg__action__Herkanser_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_Result * data =
      (g1_interface_pkg__action__Herkanser_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `status`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
g1_interface_pkg__action__Herkanser_Feedback__init(g1_interface_pkg__action__Herkanser_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // progress
  // status
  if (!rosidl_runtime_c__String__init(&msg->status)) {
    g1_interface_pkg__action__Herkanser_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_Feedback__fini(g1_interface_pkg__action__Herkanser_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // progress
  // status
  rosidl_runtime_c__String__fini(&msg->status);
}

bool
g1_interface_pkg__action__Herkanser_Feedback__are_equal(const g1_interface_pkg__action__Herkanser_Feedback * lhs, const g1_interface_pkg__action__Herkanser_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // progress
  if (lhs->progress != rhs->progress) {
    return false;
  }
  // status
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->status), &(rhs->status)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_Feedback__copy(
  const g1_interface_pkg__action__Herkanser_Feedback * input,
  g1_interface_pkg__action__Herkanser_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // progress
  output->progress = input->progress;
  // status
  if (!rosidl_runtime_c__String__copy(
      &(input->status), &(output->status)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__action__Herkanser_Feedback *
g1_interface_pkg__action__Herkanser_Feedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_Feedback * msg = (g1_interface_pkg__action__Herkanser_Feedback *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_Feedback));
  bool success = g1_interface_pkg__action__Herkanser_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_Feedback__destroy(g1_interface_pkg__action__Herkanser_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_Feedback__Sequence__init(g1_interface_pkg__action__Herkanser_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_Feedback * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_Feedback *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_Feedback__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_Feedback__Sequence__fini(g1_interface_pkg__action__Herkanser_Feedback__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_Feedback__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_Feedback__Sequence *
g1_interface_pkg__action__Herkanser_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_Feedback__Sequence * array = (g1_interface_pkg__action__Herkanser_Feedback__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_Feedback__Sequence__destroy(g1_interface_pkg__action__Herkanser_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_Feedback__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_Feedback__Sequence * lhs, const g1_interface_pkg__action__Herkanser_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_Feedback__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_Feedback__Sequence * input,
  g1_interface_pkg__action__Herkanser_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_Feedback * data =
      (g1_interface_pkg__action__Herkanser_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "g1_interface_pkg/action/detail/herkanser__functions.h"

bool
g1_interface_pkg__action__Herkanser_SendGoal_Request__init(g1_interface_pkg__action__Herkanser_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    g1_interface_pkg__action__Herkanser_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!g1_interface_pkg__action__Herkanser_Goal__init(&msg->goal)) {
    g1_interface_pkg__action__Herkanser_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_SendGoal_Request__fini(g1_interface_pkg__action__Herkanser_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  g1_interface_pkg__action__Herkanser_Goal__fini(&msg->goal);
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Request__are_equal(const g1_interface_pkg__action__Herkanser_SendGoal_Request * lhs, const g1_interface_pkg__action__Herkanser_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!g1_interface_pkg__action__Herkanser_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Request__copy(
  const g1_interface_pkg__action__Herkanser_SendGoal_Request * input,
  g1_interface_pkg__action__Herkanser_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!g1_interface_pkg__action__Herkanser_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__action__Herkanser_SendGoal_Request *
g1_interface_pkg__action__Herkanser_SendGoal_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_SendGoal_Request * msg = (g1_interface_pkg__action__Herkanser_SendGoal_Request *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Request));
  bool success = g1_interface_pkg__action__Herkanser_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_SendGoal_Request__destroy(g1_interface_pkg__action__Herkanser_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__init(g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_SendGoal_Request * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_SendGoal_Request *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_SendGoal_Request__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__fini(g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_SendGoal_Request__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence *
g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence * array = (g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__destroy(g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence * lhs, const g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence * input,
  g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_SendGoal_Request * data =
      (g1_interface_pkg__action__Herkanser_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
g1_interface_pkg__action__Herkanser_SendGoal_Response__init(g1_interface_pkg__action__Herkanser_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    g1_interface_pkg__action__Herkanser_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_SendGoal_Response__fini(g1_interface_pkg__action__Herkanser_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Response__are_equal(const g1_interface_pkg__action__Herkanser_SendGoal_Response * lhs, const g1_interface_pkg__action__Herkanser_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Response__copy(
  const g1_interface_pkg__action__Herkanser_SendGoal_Response * input,
  g1_interface_pkg__action__Herkanser_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__action__Herkanser_SendGoal_Response *
g1_interface_pkg__action__Herkanser_SendGoal_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_SendGoal_Response * msg = (g1_interface_pkg__action__Herkanser_SendGoal_Response *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Response));
  bool success = g1_interface_pkg__action__Herkanser_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_SendGoal_Response__destroy(g1_interface_pkg__action__Herkanser_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__init(g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_SendGoal_Response * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_SendGoal_Response *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_SendGoal_Response__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__fini(g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_SendGoal_Response__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence *
g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence * array = (g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__destroy(g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence * lhs, const g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence * input,
  g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_SendGoal_Response * data =
      (g1_interface_pkg__action__Herkanser_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "g1_interface_pkg/action/detail/herkanser__functions.h"

bool
g1_interface_pkg__action__Herkanser_SendGoal_Event__init(g1_interface_pkg__action__Herkanser_SendGoal_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    g1_interface_pkg__action__Herkanser_SendGoal_Event__fini(msg);
    return false;
  }
  // request
  if (!g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__init(&msg->request, 0)) {
    g1_interface_pkg__action__Herkanser_SendGoal_Event__fini(msg);
    return false;
  }
  // response
  if (!g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__init(&msg->response, 0)) {
    g1_interface_pkg__action__Herkanser_SendGoal_Event__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_SendGoal_Event__fini(g1_interface_pkg__action__Herkanser_SendGoal_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__fini(&msg->request);
  // response
  g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__fini(&msg->response);
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Event__are_equal(const g1_interface_pkg__action__Herkanser_SendGoal_Event * lhs, const g1_interface_pkg__action__Herkanser_SendGoal_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Event__copy(
  const g1_interface_pkg__action__Herkanser_SendGoal_Event * input,
  g1_interface_pkg__action__Herkanser_SendGoal_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!g1_interface_pkg__action__Herkanser_SendGoal_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!g1_interface_pkg__action__Herkanser_SendGoal_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__action__Herkanser_SendGoal_Event *
g1_interface_pkg__action__Herkanser_SendGoal_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_SendGoal_Event * msg = (g1_interface_pkg__action__Herkanser_SendGoal_Event *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Event));
  bool success = g1_interface_pkg__action__Herkanser_SendGoal_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_SendGoal_Event__destroy(g1_interface_pkg__action__Herkanser_SendGoal_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_SendGoal_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence__init(g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_SendGoal_Event * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_SendGoal_Event *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_SendGoal_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_SendGoal_Event__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence__fini(g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_SendGoal_Event__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence *
g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence * array = (g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence__destroy(g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence * lhs, const g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_SendGoal_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence * input,
  g1_interface_pkg__action__Herkanser_SendGoal_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_SendGoal_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_SendGoal_Event * data =
      (g1_interface_pkg__action__Herkanser_SendGoal_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_SendGoal_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_SendGoal_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_SendGoal_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
g1_interface_pkg__action__Herkanser_GetResult_Request__init(g1_interface_pkg__action__Herkanser_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    g1_interface_pkg__action__Herkanser_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_GetResult_Request__fini(g1_interface_pkg__action__Herkanser_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Request__are_equal(const g1_interface_pkg__action__Herkanser_GetResult_Request * lhs, const g1_interface_pkg__action__Herkanser_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Request__copy(
  const g1_interface_pkg__action__Herkanser_GetResult_Request * input,
  g1_interface_pkg__action__Herkanser_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__action__Herkanser_GetResult_Request *
g1_interface_pkg__action__Herkanser_GetResult_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_GetResult_Request * msg = (g1_interface_pkg__action__Herkanser_GetResult_Request *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_GetResult_Request));
  bool success = g1_interface_pkg__action__Herkanser_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_GetResult_Request__destroy(g1_interface_pkg__action__Herkanser_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__init(g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_GetResult_Request * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_GetResult_Request *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_GetResult_Request__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__fini(g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_GetResult_Request__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence *
g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence * array = (g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__destroy(g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence * lhs, const g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence * input,
  g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_GetResult_Request * data =
      (g1_interface_pkg__action__Herkanser_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "g1_interface_pkg/action/detail/herkanser__functions.h"

bool
g1_interface_pkg__action__Herkanser_GetResult_Response__init(g1_interface_pkg__action__Herkanser_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!g1_interface_pkg__action__Herkanser_Result__init(&msg->result)) {
    g1_interface_pkg__action__Herkanser_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_GetResult_Response__fini(g1_interface_pkg__action__Herkanser_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  g1_interface_pkg__action__Herkanser_Result__fini(&msg->result);
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Response__are_equal(const g1_interface_pkg__action__Herkanser_GetResult_Response * lhs, const g1_interface_pkg__action__Herkanser_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!g1_interface_pkg__action__Herkanser_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Response__copy(
  const g1_interface_pkg__action__Herkanser_GetResult_Response * input,
  g1_interface_pkg__action__Herkanser_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!g1_interface_pkg__action__Herkanser_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__action__Herkanser_GetResult_Response *
g1_interface_pkg__action__Herkanser_GetResult_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_GetResult_Response * msg = (g1_interface_pkg__action__Herkanser_GetResult_Response *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_GetResult_Response));
  bool success = g1_interface_pkg__action__Herkanser_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_GetResult_Response__destroy(g1_interface_pkg__action__Herkanser_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__init(g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_GetResult_Response * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_GetResult_Response *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_GetResult_Response__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__fini(g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_GetResult_Response__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence *
g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence * array = (g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__destroy(g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence * lhs, const g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence * input,
  g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_GetResult_Response * data =
      (g1_interface_pkg__action__Herkanser_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "g1_interface_pkg/action/detail/herkanser__functions.h"

bool
g1_interface_pkg__action__Herkanser_GetResult_Event__init(g1_interface_pkg__action__Herkanser_GetResult_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    g1_interface_pkg__action__Herkanser_GetResult_Event__fini(msg);
    return false;
  }
  // request
  if (!g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__init(&msg->request, 0)) {
    g1_interface_pkg__action__Herkanser_GetResult_Event__fini(msg);
    return false;
  }
  // response
  if (!g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__init(&msg->response, 0)) {
    g1_interface_pkg__action__Herkanser_GetResult_Event__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_GetResult_Event__fini(g1_interface_pkg__action__Herkanser_GetResult_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__fini(&msg->request);
  // response
  g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__fini(&msg->response);
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Event__are_equal(const g1_interface_pkg__action__Herkanser_GetResult_Event * lhs, const g1_interface_pkg__action__Herkanser_GetResult_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Event__copy(
  const g1_interface_pkg__action__Herkanser_GetResult_Event * input,
  g1_interface_pkg__action__Herkanser_GetResult_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!g1_interface_pkg__action__Herkanser_GetResult_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!g1_interface_pkg__action__Herkanser_GetResult_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__action__Herkanser_GetResult_Event *
g1_interface_pkg__action__Herkanser_GetResult_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_GetResult_Event * msg = (g1_interface_pkg__action__Herkanser_GetResult_Event *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_GetResult_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_GetResult_Event));
  bool success = g1_interface_pkg__action__Herkanser_GetResult_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_GetResult_Event__destroy(g1_interface_pkg__action__Herkanser_GetResult_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_GetResult_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence__init(g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_GetResult_Event * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_GetResult_Event *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_GetResult_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_GetResult_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_GetResult_Event__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence__fini(g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_GetResult_Event__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence *
g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence * array = (g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence__destroy(g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence * lhs, const g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_GetResult_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence * input,
  g1_interface_pkg__action__Herkanser_GetResult_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_GetResult_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_GetResult_Event * data =
      (g1_interface_pkg__action__Herkanser_GetResult_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_GetResult_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_GetResult_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_GetResult_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "g1_interface_pkg/action/detail/herkanser__functions.h"

bool
g1_interface_pkg__action__Herkanser_FeedbackMessage__init(g1_interface_pkg__action__Herkanser_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    g1_interface_pkg__action__Herkanser_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!g1_interface_pkg__action__Herkanser_Feedback__init(&msg->feedback)) {
    g1_interface_pkg__action__Herkanser_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__action__Herkanser_FeedbackMessage__fini(g1_interface_pkg__action__Herkanser_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  g1_interface_pkg__action__Herkanser_Feedback__fini(&msg->feedback);
}

bool
g1_interface_pkg__action__Herkanser_FeedbackMessage__are_equal(const g1_interface_pkg__action__Herkanser_FeedbackMessage * lhs, const g1_interface_pkg__action__Herkanser_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!g1_interface_pkg__action__Herkanser_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_FeedbackMessage__copy(
  const g1_interface_pkg__action__Herkanser_FeedbackMessage * input,
  g1_interface_pkg__action__Herkanser_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!g1_interface_pkg__action__Herkanser_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__action__Herkanser_FeedbackMessage *
g1_interface_pkg__action__Herkanser_FeedbackMessage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_FeedbackMessage * msg = (g1_interface_pkg__action__Herkanser_FeedbackMessage *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__action__Herkanser_FeedbackMessage));
  bool success = g1_interface_pkg__action__Herkanser_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__action__Herkanser_FeedbackMessage__destroy(g1_interface_pkg__action__Herkanser_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__action__Herkanser_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence__init(g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_FeedbackMessage * data = NULL;

  if (size) {
    data = (g1_interface_pkg__action__Herkanser_FeedbackMessage *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__action__Herkanser_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__action__Herkanser_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__action__Herkanser_FeedbackMessage__fini(&data[i - 1]);
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
g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence__fini(g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence * array)
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
      g1_interface_pkg__action__Herkanser_FeedbackMessage__fini(&array->data[i]);
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

g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence *
g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence * array = (g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence__destroy(g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence__are_equal(const g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence * lhs, const g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence__copy(
  const g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence * input,
  g1_interface_pkg__action__Herkanser_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__action__Herkanser_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__action__Herkanser_FeedbackMessage * data =
      (g1_interface_pkg__action__Herkanser_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__action__Herkanser_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__action__Herkanser_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__action__Herkanser_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
