// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from g1_interface_pkg:msg/Student.idl
// generated code does not contain a copyright notice

#include "g1_interface_pkg/msg/detail/student__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_g1_interface_pkg
const rosidl_type_hash_t *
g1_interface_pkg__msg__Student__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x15, 0xd8, 0x6c, 0xa8, 0x40, 0x42, 0x17, 0x31,
      0xa2, 0x3a, 0xc2, 0xac, 0xfb, 0x33, 0xe1, 0x90,
      0x8b, 0x59, 0x09, 0x7e, 0x32, 0xa1, 0xf3, 0x8a,
      0xa0, 0x2a, 0x22, 0xd1, 0x11, 0xd9, 0xf0, 0x8f,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
#endif

static char g1_interface_pkg__msg__Student__TYPE_NAME[] = "g1_interface_pkg/msg/Student";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";

// Define type names, field names, and default values
static char g1_interface_pkg__msg__Student__FIELD_NAME__stamp[] = "stamp";
static char g1_interface_pkg__msg__Student__FIELD_NAME__name[] = "name";
static char g1_interface_pkg__msg__Student__FIELD_NAME__course[] = "course";

static rosidl_runtime_c__type_description__Field g1_interface_pkg__msg__Student__FIELDS[] = {
  {
    {g1_interface_pkg__msg__Student__FIELD_NAME__stamp, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__msg__Student__FIELD_NAME__name, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__msg__Student__FIELD_NAME__course, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription g1_interface_pkg__msg__Student__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
g1_interface_pkg__msg__Student__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {g1_interface_pkg__msg__Student__TYPE_NAME, 28, 28},
      {g1_interface_pkg__msg__Student__FIELDS, 3, 3},
    },
    {g1_interface_pkg__msg__Student__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "builtin_interfaces/Time stamp\n"
  "string name\n"
  "string course";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
g1_interface_pkg__msg__Student__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {g1_interface_pkg__msg__Student__TYPE_NAME, 28, 28},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 55, 55},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
g1_interface_pkg__msg__Student__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *g1_interface_pkg__msg__Student__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
