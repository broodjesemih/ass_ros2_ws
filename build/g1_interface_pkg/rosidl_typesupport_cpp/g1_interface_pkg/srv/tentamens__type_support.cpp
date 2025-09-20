// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from g1_interface_pkg:srv/Tentamens.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "g1_interface_pkg/srv/detail/tentamens__functions.h"
#include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace g1_interface_pkg
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _Tentamens_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Tentamens_Request_type_support_ids_t;

static const _Tentamens_Request_type_support_ids_t _Tentamens_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Tentamens_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Tentamens_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Tentamens_Request_type_support_symbol_names_t _Tentamens_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g1_interface_pkg, srv, Tentamens_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g1_interface_pkg, srv, Tentamens_Request)),
  }
};

typedef struct _Tentamens_Request_type_support_data_t
{
  void * data[2];
} _Tentamens_Request_type_support_data_t;

static _Tentamens_Request_type_support_data_t _Tentamens_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Tentamens_Request_message_typesupport_map = {
  2,
  "g1_interface_pkg",
  &_Tentamens_Request_message_typesupport_ids.typesupport_identifier[0],
  &_Tentamens_Request_message_typesupport_symbol_names.symbol_name[0],
  &_Tentamens_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Tentamens_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Tentamens_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g1_interface_pkg__srv__Tentamens_Request__get_type_hash,
  &g1_interface_pkg__srv__Tentamens_Request__get_type_description,
  &g1_interface_pkg__srv__Tentamens_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace g1_interface_pkg

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Request>()
{
  return &::g1_interface_pkg::srv::rosidl_typesupport_cpp::Tentamens_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g1_interface_pkg, srv, Tentamens_Request)() {
  return get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__functions.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g1_interface_pkg
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _Tentamens_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Tentamens_Response_type_support_ids_t;

static const _Tentamens_Response_type_support_ids_t _Tentamens_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Tentamens_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Tentamens_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Tentamens_Response_type_support_symbol_names_t _Tentamens_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g1_interface_pkg, srv, Tentamens_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g1_interface_pkg, srv, Tentamens_Response)),
  }
};

typedef struct _Tentamens_Response_type_support_data_t
{
  void * data[2];
} _Tentamens_Response_type_support_data_t;

static _Tentamens_Response_type_support_data_t _Tentamens_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Tentamens_Response_message_typesupport_map = {
  2,
  "g1_interface_pkg",
  &_Tentamens_Response_message_typesupport_ids.typesupport_identifier[0],
  &_Tentamens_Response_message_typesupport_symbol_names.symbol_name[0],
  &_Tentamens_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Tentamens_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Tentamens_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g1_interface_pkg__srv__Tentamens_Response__get_type_hash,
  &g1_interface_pkg__srv__Tentamens_Response__get_type_description,
  &g1_interface_pkg__srv__Tentamens_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace g1_interface_pkg

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Response>()
{
  return &::g1_interface_pkg::srv::rosidl_typesupport_cpp::Tentamens_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g1_interface_pkg, srv, Tentamens_Response)() {
  return get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__functions.h"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g1_interface_pkg
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _Tentamens_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Tentamens_Event_type_support_ids_t;

static const _Tentamens_Event_type_support_ids_t _Tentamens_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Tentamens_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Tentamens_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Tentamens_Event_type_support_symbol_names_t _Tentamens_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g1_interface_pkg, srv, Tentamens_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g1_interface_pkg, srv, Tentamens_Event)),
  }
};

typedef struct _Tentamens_Event_type_support_data_t
{
  void * data[2];
} _Tentamens_Event_type_support_data_t;

static _Tentamens_Event_type_support_data_t _Tentamens_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Tentamens_Event_message_typesupport_map = {
  2,
  "g1_interface_pkg",
  &_Tentamens_Event_message_typesupport_ids.typesupport_identifier[0],
  &_Tentamens_Event_message_typesupport_symbol_names.symbol_name[0],
  &_Tentamens_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t Tentamens_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Tentamens_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g1_interface_pkg__srv__Tentamens_Event__get_type_hash,
  &g1_interface_pkg__srv__Tentamens_Event__get_type_description,
  &g1_interface_pkg__srv__Tentamens_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace g1_interface_pkg

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Event>()
{
  return &::g1_interface_pkg::srv::rosidl_typesupport_cpp::Tentamens_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g1_interface_pkg, srv, Tentamens_Event)() {
  return get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g1_interface_pkg
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _Tentamens_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _Tentamens_type_support_ids_t;

static const _Tentamens_type_support_ids_t _Tentamens_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _Tentamens_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _Tentamens_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _Tentamens_type_support_symbol_names_t _Tentamens_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g1_interface_pkg, srv, Tentamens)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g1_interface_pkg, srv, Tentamens)),
  }
};

typedef struct _Tentamens_type_support_data_t
{
  void * data[2];
} _Tentamens_type_support_data_t;

static _Tentamens_type_support_data_t _Tentamens_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _Tentamens_service_typesupport_map = {
  2,
  "g1_interface_pkg",
  &_Tentamens_service_typesupport_ids.typesupport_identifier[0],
  &_Tentamens_service_typesupport_symbol_names.symbol_name[0],
  &_Tentamens_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t Tentamens_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_Tentamens_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<g1_interface_pkg::srv::Tentamens_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<g1_interface_pkg::srv::Tentamens>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<g1_interface_pkg::srv::Tentamens>,
  &g1_interface_pkg__srv__Tentamens__get_type_hash,
  &g1_interface_pkg__srv__Tentamens__get_type_description,
  &g1_interface_pkg__srv__Tentamens__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace g1_interface_pkg

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<g1_interface_pkg::srv::Tentamens>()
{
  return &::g1_interface_pkg::srv::rosidl_typesupport_cpp::Tentamens_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, g1_interface_pkg, srv, Tentamens)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<g1_interface_pkg::srv::Tentamens>();
}

#ifdef __cplusplus
}
#endif
