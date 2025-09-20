// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from g1_interface_pkg:srv/Tentamens.idl
// generated code does not contain a copyright notice

#include "g1_interface_pkg/srv/detail/tentamens__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_g1_interface_pkg
const rosidl_type_hash_t *
g1_interface_pkg__srv__Tentamens__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf2, 0x2a, 0xbc, 0xc1, 0x02, 0x30, 0xb4, 0x6f,
      0x5e, 0xaa, 0x62, 0x3a, 0x1d, 0x04, 0x87, 0x74,
      0x0e, 0x7f, 0xc6, 0x87, 0xc9, 0xfa, 0x63, 0x05,
      0x61, 0xcf, 0x20, 0x33, 0x98, 0xd9, 0xee, 0x8f,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_g1_interface_pkg
const rosidl_type_hash_t *
g1_interface_pkg__srv__Tentamens_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xdb, 0xb3, 0x49, 0xe6, 0x39, 0x01, 0xd4, 0x12,
      0x73, 0xa2, 0x1c, 0xe2, 0x5e, 0x6f, 0x3f, 0xf1,
      0x3c, 0x91, 0xf2, 0x94, 0xf9, 0xa0, 0xac, 0x5b,
      0xcf, 0xd1, 0x98, 0xcb, 0x84, 0x22, 0xf7, 0x1e,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_g1_interface_pkg
const rosidl_type_hash_t *
g1_interface_pkg__srv__Tentamens_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x43, 0xe3, 0xfd, 0x0d, 0x40, 0x9f, 0x17, 0x05,
      0x34, 0x83, 0x60, 0x80, 0x72, 0x04, 0x07, 0xb6,
      0x3d, 0xf7, 0x24, 0xd6, 0xab, 0x42, 0x30, 0xa1,
      0xcb, 0x51, 0x00, 0x2b, 0x5b, 0x54, 0x2a, 0x90,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_g1_interface_pkg
const rosidl_type_hash_t *
g1_interface_pkg__srv__Tentamens_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xfb, 0xc6, 0xfe, 0x45, 0x4f, 0x27, 0x94, 0xcc,
      0xaa, 0x05, 0xd2, 0x83, 0xaa, 0x4c, 0x77, 0x98,
      0xb6, 0x19, 0xf1, 0xd9, 0x2a, 0x89, 0x85, 0x1c,
      0x05, 0x74, 0xf5, 0x36, 0x37, 0x67, 0xef, 0x45,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char g1_interface_pkg__srv__Tentamens__TYPE_NAME[] = "g1_interface_pkg/srv/Tentamens";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char g1_interface_pkg__srv__Tentamens_Event__TYPE_NAME[] = "g1_interface_pkg/srv/Tentamens_Event";
static char g1_interface_pkg__srv__Tentamens_Request__TYPE_NAME[] = "g1_interface_pkg/srv/Tentamens_Request";
static char g1_interface_pkg__srv__Tentamens_Response__TYPE_NAME[] = "g1_interface_pkg/srv/Tentamens_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char g1_interface_pkg__srv__Tentamens__FIELD_NAME__request_message[] = "request_message";
static char g1_interface_pkg__srv__Tentamens__FIELD_NAME__response_message[] = "response_message";
static char g1_interface_pkg__srv__Tentamens__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field g1_interface_pkg__srv__Tentamens__FIELDS[] = {
  {
    {g1_interface_pkg__srv__Tentamens__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {g1_interface_pkg__srv__Tentamens_Request__TYPE_NAME, 38, 38},
    },
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {g1_interface_pkg__srv__Tentamens_Response__TYPE_NAME, 39, 39},
    },
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {g1_interface_pkg__srv__Tentamens_Event__TYPE_NAME, 36, 36},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription g1_interface_pkg__srv__Tentamens__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Event__TYPE_NAME, 36, 36},
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Request__TYPE_NAME, 38, 38},
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Response__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
g1_interface_pkg__srv__Tentamens__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {g1_interface_pkg__srv__Tentamens__TYPE_NAME, 30, 30},
      {g1_interface_pkg__srv__Tentamens__FIELDS, 3, 3},
    },
    {g1_interface_pkg__srv__Tentamens__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = g1_interface_pkg__srv__Tentamens_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = g1_interface_pkg__srv__Tentamens_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = g1_interface_pkg__srv__Tentamens_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char g1_interface_pkg__srv__Tentamens_Request__FIELD_NAME__student_name[] = "student_name";
static char g1_interface_pkg__srv__Tentamens_Request__FIELD_NAME__course_name[] = "course_name";
static char g1_interface_pkg__srv__Tentamens_Request__FIELD_NAME__tentamen_cijfers[] = "tentamen_cijfers";

static rosidl_runtime_c__type_description__Field g1_interface_pkg__srv__Tentamens_Request__FIELDS[] = {
  {
    {g1_interface_pkg__srv__Tentamens_Request__FIELD_NAME__student_name, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Request__FIELD_NAME__course_name, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Request__FIELD_NAME__tentamen_cijfers, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
g1_interface_pkg__srv__Tentamens_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {g1_interface_pkg__srv__Tentamens_Request__TYPE_NAME, 38, 38},
      {g1_interface_pkg__srv__Tentamens_Request__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char g1_interface_pkg__srv__Tentamens_Response__FIELD_NAME__final_cijfer[] = "final_cijfer";
static char g1_interface_pkg__srv__Tentamens_Response__FIELD_NAME__message[] = "message";

static rosidl_runtime_c__type_description__Field g1_interface_pkg__srv__Tentamens_Response__FIELDS[] = {
  {
    {g1_interface_pkg__srv__Tentamens_Response__FIELD_NAME__final_cijfer, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Response__FIELD_NAME__message, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
g1_interface_pkg__srv__Tentamens_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {g1_interface_pkg__srv__Tentamens_Response__TYPE_NAME, 39, 39},
      {g1_interface_pkg__srv__Tentamens_Response__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char g1_interface_pkg__srv__Tentamens_Event__FIELD_NAME__info[] = "info";
static char g1_interface_pkg__srv__Tentamens_Event__FIELD_NAME__request[] = "request";
static char g1_interface_pkg__srv__Tentamens_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field g1_interface_pkg__srv__Tentamens_Event__FIELDS[] = {
  {
    {g1_interface_pkg__srv__Tentamens_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {g1_interface_pkg__srv__Tentamens_Request__TYPE_NAME, 38, 38},
    },
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {g1_interface_pkg__srv__Tentamens_Response__TYPE_NAME, 39, 39},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription g1_interface_pkg__srv__Tentamens_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Request__TYPE_NAME, 38, 38},
    {NULL, 0, 0},
  },
  {
    {g1_interface_pkg__srv__Tentamens_Response__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
g1_interface_pkg__srv__Tentamens_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {g1_interface_pkg__srv__Tentamens_Event__TYPE_NAME, 36, 36},
      {g1_interface_pkg__srv__Tentamens_Event__FIELDS, 3, 3},
    },
    {g1_interface_pkg__srv__Tentamens_Event__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = g1_interface_pkg__srv__Tentamens_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = g1_interface_pkg__srv__Tentamens_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string student_name\n"
  "string course_name\n"
  "int32[] tentamen_cijfers\n"
  "---\n"
  "int32 final_cijfer\n"
  "string message";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
g1_interface_pkg__srv__Tentamens__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {g1_interface_pkg__srv__Tentamens__TYPE_NAME, 30, 30},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 101, 101},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
g1_interface_pkg__srv__Tentamens_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {g1_interface_pkg__srv__Tentamens_Request__TYPE_NAME, 38, 38},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
g1_interface_pkg__srv__Tentamens_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {g1_interface_pkg__srv__Tentamens_Response__TYPE_NAME, 39, 39},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
g1_interface_pkg__srv__Tentamens_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {g1_interface_pkg__srv__Tentamens_Event__TYPE_NAME, 36, 36},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
g1_interface_pkg__srv__Tentamens__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *g1_interface_pkg__srv__Tentamens__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *g1_interface_pkg__srv__Tentamens_Event__get_individual_type_description_source(NULL);
    sources[3] = *g1_interface_pkg__srv__Tentamens_Request__get_individual_type_description_source(NULL);
    sources[4] = *g1_interface_pkg__srv__Tentamens_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
g1_interface_pkg__srv__Tentamens_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *g1_interface_pkg__srv__Tentamens_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
g1_interface_pkg__srv__Tentamens_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *g1_interface_pkg__srv__Tentamens_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
g1_interface_pkg__srv__Tentamens_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *g1_interface_pkg__srv__Tentamens_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *g1_interface_pkg__srv__Tentamens_Request__get_individual_type_description_source(NULL);
    sources[3] = *g1_interface_pkg__srv__Tentamens_Response__get_individual_type_description_source(NULL);
    sources[4] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
