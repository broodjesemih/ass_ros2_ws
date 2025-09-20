// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from g1_interface_pkg:srv/Tentamens.idl
// generated code does not contain a copyright notice
#include "g1_interface_pkg/srv/detail/tentamens__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `student_name`
// Member `course_name`
#include "rosidl_runtime_c/string_functions.h"
// Member `tentamen_cijfers`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
g1_interface_pkg__srv__Tentamens_Request__init(g1_interface_pkg__srv__Tentamens_Request * msg)
{
  if (!msg) {
    return false;
  }
  // student_name
  if (!rosidl_runtime_c__String__init(&msg->student_name)) {
    g1_interface_pkg__srv__Tentamens_Request__fini(msg);
    return false;
  }
  // course_name
  if (!rosidl_runtime_c__String__init(&msg->course_name)) {
    g1_interface_pkg__srv__Tentamens_Request__fini(msg);
    return false;
  }
  // tentamen_cijfers
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->tentamen_cijfers, 0)) {
    g1_interface_pkg__srv__Tentamens_Request__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__srv__Tentamens_Request__fini(g1_interface_pkg__srv__Tentamens_Request * msg)
{
  if (!msg) {
    return;
  }
  // student_name
  rosidl_runtime_c__String__fini(&msg->student_name);
  // course_name
  rosidl_runtime_c__String__fini(&msg->course_name);
  // tentamen_cijfers
  rosidl_runtime_c__int32__Sequence__fini(&msg->tentamen_cijfers);
}

bool
g1_interface_pkg__srv__Tentamens_Request__are_equal(const g1_interface_pkg__srv__Tentamens_Request * lhs, const g1_interface_pkg__srv__Tentamens_Request * rhs)
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
  // tentamen_cijfers
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->tentamen_cijfers), &(rhs->tentamen_cijfers)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__srv__Tentamens_Request__copy(
  const g1_interface_pkg__srv__Tentamens_Request * input,
  g1_interface_pkg__srv__Tentamens_Request * output)
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
  // tentamen_cijfers
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->tentamen_cijfers), &(output->tentamen_cijfers)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__srv__Tentamens_Request *
g1_interface_pkg__srv__Tentamens_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__srv__Tentamens_Request * msg = (g1_interface_pkg__srv__Tentamens_Request *)allocator.allocate(sizeof(g1_interface_pkg__srv__Tentamens_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__srv__Tentamens_Request));
  bool success = g1_interface_pkg__srv__Tentamens_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__srv__Tentamens_Request__destroy(g1_interface_pkg__srv__Tentamens_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__srv__Tentamens_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__srv__Tentamens_Request__Sequence__init(g1_interface_pkg__srv__Tentamens_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__srv__Tentamens_Request * data = NULL;

  if (size) {
    data = (g1_interface_pkg__srv__Tentamens_Request *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__srv__Tentamens_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__srv__Tentamens_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__srv__Tentamens_Request__fini(&data[i - 1]);
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
g1_interface_pkg__srv__Tentamens_Request__Sequence__fini(g1_interface_pkg__srv__Tentamens_Request__Sequence * array)
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
      g1_interface_pkg__srv__Tentamens_Request__fini(&array->data[i]);
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

g1_interface_pkg__srv__Tentamens_Request__Sequence *
g1_interface_pkg__srv__Tentamens_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__srv__Tentamens_Request__Sequence * array = (g1_interface_pkg__srv__Tentamens_Request__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__srv__Tentamens_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__srv__Tentamens_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__srv__Tentamens_Request__Sequence__destroy(g1_interface_pkg__srv__Tentamens_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__srv__Tentamens_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__srv__Tentamens_Request__Sequence__are_equal(const g1_interface_pkg__srv__Tentamens_Request__Sequence * lhs, const g1_interface_pkg__srv__Tentamens_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__srv__Tentamens_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__srv__Tentamens_Request__Sequence__copy(
  const g1_interface_pkg__srv__Tentamens_Request__Sequence * input,
  g1_interface_pkg__srv__Tentamens_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__srv__Tentamens_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__srv__Tentamens_Request * data =
      (g1_interface_pkg__srv__Tentamens_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__srv__Tentamens_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__srv__Tentamens_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__srv__Tentamens_Request__copy(
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
g1_interface_pkg__srv__Tentamens_Response__init(g1_interface_pkg__srv__Tentamens_Response * msg)
{
  if (!msg) {
    return false;
  }
  // final_cijfer
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    g1_interface_pkg__srv__Tentamens_Response__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__srv__Tentamens_Response__fini(g1_interface_pkg__srv__Tentamens_Response * msg)
{
  if (!msg) {
    return;
  }
  // final_cijfer
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
g1_interface_pkg__srv__Tentamens_Response__are_equal(const g1_interface_pkg__srv__Tentamens_Response * lhs, const g1_interface_pkg__srv__Tentamens_Response * rhs)
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
g1_interface_pkg__srv__Tentamens_Response__copy(
  const g1_interface_pkg__srv__Tentamens_Response * input,
  g1_interface_pkg__srv__Tentamens_Response * output)
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

g1_interface_pkg__srv__Tentamens_Response *
g1_interface_pkg__srv__Tentamens_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__srv__Tentamens_Response * msg = (g1_interface_pkg__srv__Tentamens_Response *)allocator.allocate(sizeof(g1_interface_pkg__srv__Tentamens_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__srv__Tentamens_Response));
  bool success = g1_interface_pkg__srv__Tentamens_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__srv__Tentamens_Response__destroy(g1_interface_pkg__srv__Tentamens_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__srv__Tentamens_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__srv__Tentamens_Response__Sequence__init(g1_interface_pkg__srv__Tentamens_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__srv__Tentamens_Response * data = NULL;

  if (size) {
    data = (g1_interface_pkg__srv__Tentamens_Response *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__srv__Tentamens_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__srv__Tentamens_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__srv__Tentamens_Response__fini(&data[i - 1]);
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
g1_interface_pkg__srv__Tentamens_Response__Sequence__fini(g1_interface_pkg__srv__Tentamens_Response__Sequence * array)
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
      g1_interface_pkg__srv__Tentamens_Response__fini(&array->data[i]);
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

g1_interface_pkg__srv__Tentamens_Response__Sequence *
g1_interface_pkg__srv__Tentamens_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__srv__Tentamens_Response__Sequence * array = (g1_interface_pkg__srv__Tentamens_Response__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__srv__Tentamens_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__srv__Tentamens_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__srv__Tentamens_Response__Sequence__destroy(g1_interface_pkg__srv__Tentamens_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__srv__Tentamens_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__srv__Tentamens_Response__Sequence__are_equal(const g1_interface_pkg__srv__Tentamens_Response__Sequence * lhs, const g1_interface_pkg__srv__Tentamens_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__srv__Tentamens_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__srv__Tentamens_Response__Sequence__copy(
  const g1_interface_pkg__srv__Tentamens_Response__Sequence * input,
  g1_interface_pkg__srv__Tentamens_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__srv__Tentamens_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__srv__Tentamens_Response * data =
      (g1_interface_pkg__srv__Tentamens_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__srv__Tentamens_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__srv__Tentamens_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__srv__Tentamens_Response__copy(
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
// #include "g1_interface_pkg/srv/detail/tentamens__functions.h"

bool
g1_interface_pkg__srv__Tentamens_Event__init(g1_interface_pkg__srv__Tentamens_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    g1_interface_pkg__srv__Tentamens_Event__fini(msg);
    return false;
  }
  // request
  if (!g1_interface_pkg__srv__Tentamens_Request__Sequence__init(&msg->request, 0)) {
    g1_interface_pkg__srv__Tentamens_Event__fini(msg);
    return false;
  }
  // response
  if (!g1_interface_pkg__srv__Tentamens_Response__Sequence__init(&msg->response, 0)) {
    g1_interface_pkg__srv__Tentamens_Event__fini(msg);
    return false;
  }
  return true;
}

void
g1_interface_pkg__srv__Tentamens_Event__fini(g1_interface_pkg__srv__Tentamens_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  g1_interface_pkg__srv__Tentamens_Request__Sequence__fini(&msg->request);
  // response
  g1_interface_pkg__srv__Tentamens_Response__Sequence__fini(&msg->response);
}

bool
g1_interface_pkg__srv__Tentamens_Event__are_equal(const g1_interface_pkg__srv__Tentamens_Event * lhs, const g1_interface_pkg__srv__Tentamens_Event * rhs)
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
  if (!g1_interface_pkg__srv__Tentamens_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!g1_interface_pkg__srv__Tentamens_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
g1_interface_pkg__srv__Tentamens_Event__copy(
  const g1_interface_pkg__srv__Tentamens_Event * input,
  g1_interface_pkg__srv__Tentamens_Event * output)
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
  if (!g1_interface_pkg__srv__Tentamens_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!g1_interface_pkg__srv__Tentamens_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

g1_interface_pkg__srv__Tentamens_Event *
g1_interface_pkg__srv__Tentamens_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__srv__Tentamens_Event * msg = (g1_interface_pkg__srv__Tentamens_Event *)allocator.allocate(sizeof(g1_interface_pkg__srv__Tentamens_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g1_interface_pkg__srv__Tentamens_Event));
  bool success = g1_interface_pkg__srv__Tentamens_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g1_interface_pkg__srv__Tentamens_Event__destroy(g1_interface_pkg__srv__Tentamens_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g1_interface_pkg__srv__Tentamens_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g1_interface_pkg__srv__Tentamens_Event__Sequence__init(g1_interface_pkg__srv__Tentamens_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__srv__Tentamens_Event * data = NULL;

  if (size) {
    data = (g1_interface_pkg__srv__Tentamens_Event *)allocator.zero_allocate(size, sizeof(g1_interface_pkg__srv__Tentamens_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g1_interface_pkg__srv__Tentamens_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g1_interface_pkg__srv__Tentamens_Event__fini(&data[i - 1]);
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
g1_interface_pkg__srv__Tentamens_Event__Sequence__fini(g1_interface_pkg__srv__Tentamens_Event__Sequence * array)
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
      g1_interface_pkg__srv__Tentamens_Event__fini(&array->data[i]);
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

g1_interface_pkg__srv__Tentamens_Event__Sequence *
g1_interface_pkg__srv__Tentamens_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g1_interface_pkg__srv__Tentamens_Event__Sequence * array = (g1_interface_pkg__srv__Tentamens_Event__Sequence *)allocator.allocate(sizeof(g1_interface_pkg__srv__Tentamens_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g1_interface_pkg__srv__Tentamens_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g1_interface_pkg__srv__Tentamens_Event__Sequence__destroy(g1_interface_pkg__srv__Tentamens_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g1_interface_pkg__srv__Tentamens_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g1_interface_pkg__srv__Tentamens_Event__Sequence__are_equal(const g1_interface_pkg__srv__Tentamens_Event__Sequence * lhs, const g1_interface_pkg__srv__Tentamens_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g1_interface_pkg__srv__Tentamens_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g1_interface_pkg__srv__Tentamens_Event__Sequence__copy(
  const g1_interface_pkg__srv__Tentamens_Event__Sequence * input,
  g1_interface_pkg__srv__Tentamens_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g1_interface_pkg__srv__Tentamens_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g1_interface_pkg__srv__Tentamens_Event * data =
      (g1_interface_pkg__srv__Tentamens_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g1_interface_pkg__srv__Tentamens_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g1_interface_pkg__srv__Tentamens_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g1_interface_pkg__srv__Tentamens_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
