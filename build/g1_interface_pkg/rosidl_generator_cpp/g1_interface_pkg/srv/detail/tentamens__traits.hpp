// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from g1_interface_pkg:srv/Tentamens.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/srv/tentamens.hpp"


#ifndef G1_INTERFACE_PKG__SRV__DETAIL__TENTAMENS__TRAITS_HPP_
#define G1_INTERFACE_PKG__SRV__DETAIL__TENTAMENS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace g1_interface_pkg
{

namespace srv
{

inline void to_flow_style_yaml(
  const Tentamens_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: student_name
  {
    out << "student_name: ";
    rosidl_generator_traits::value_to_yaml(msg.student_name, out);
    out << ", ";
  }

  // member: course_name
  {
    out << "course_name: ";
    rosidl_generator_traits::value_to_yaml(msg.course_name, out);
    out << ", ";
  }

  // member: tentamen_cijfers
  {
    if (msg.tentamen_cijfers.size() == 0) {
      out << "tentamen_cijfers: []";
    } else {
      out << "tentamen_cijfers: [";
      size_t pending_items = msg.tentamen_cijfers.size();
      for (auto item : msg.tentamen_cijfers) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Tentamens_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: student_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "student_name: ";
    rosidl_generator_traits::value_to_yaml(msg.student_name, out);
    out << "\n";
  }

  // member: course_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "course_name: ";
    rosidl_generator_traits::value_to_yaml(msg.course_name, out);
    out << "\n";
  }

  // member: tentamen_cijfers
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.tentamen_cijfers.size() == 0) {
      out << "tentamen_cijfers: []\n";
    } else {
      out << "tentamen_cijfers:\n";
      for (auto item : msg.tentamen_cijfers) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Tentamens_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace g1_interface_pkg

namespace rosidl_generator_traits
{

[[deprecated("use g1_interface_pkg::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g1_interface_pkg::srv::Tentamens_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  g1_interface_pkg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g1_interface_pkg::srv::to_yaml() instead")]]
inline std::string to_yaml(const g1_interface_pkg::srv::Tentamens_Request & msg)
{
  return g1_interface_pkg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<g1_interface_pkg::srv::Tentamens_Request>()
{
  return "g1_interface_pkg::srv::Tentamens_Request";
}

template<>
inline const char * name<g1_interface_pkg::srv::Tentamens_Request>()
{
  return "g1_interface_pkg/srv/Tentamens_Request";
}

template<>
struct has_fixed_size<g1_interface_pkg::srv::Tentamens_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g1_interface_pkg::srv::Tentamens_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<g1_interface_pkg::srv::Tentamens_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace g1_interface_pkg
{

namespace srv
{

inline void to_flow_style_yaml(
  const Tentamens_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: final_cijfer
  {
    out << "final_cijfer: ";
    rosidl_generator_traits::value_to_yaml(msg.final_cijfer, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Tentamens_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: final_cijfer
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_cijfer: ";
    rosidl_generator_traits::value_to_yaml(msg.final_cijfer, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Tentamens_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace g1_interface_pkg

namespace rosidl_generator_traits
{

[[deprecated("use g1_interface_pkg::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g1_interface_pkg::srv::Tentamens_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  g1_interface_pkg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g1_interface_pkg::srv::to_yaml() instead")]]
inline std::string to_yaml(const g1_interface_pkg::srv::Tentamens_Response & msg)
{
  return g1_interface_pkg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<g1_interface_pkg::srv::Tentamens_Response>()
{
  return "g1_interface_pkg::srv::Tentamens_Response";
}

template<>
inline const char * name<g1_interface_pkg::srv::Tentamens_Response>()
{
  return "g1_interface_pkg/srv/Tentamens_Response";
}

template<>
struct has_fixed_size<g1_interface_pkg::srv::Tentamens_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g1_interface_pkg::srv::Tentamens_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<g1_interface_pkg::srv::Tentamens_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace g1_interface_pkg
{

namespace srv
{

inline void to_flow_style_yaml(
  const Tentamens_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Tentamens_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Tentamens_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace g1_interface_pkg

namespace rosidl_generator_traits
{

[[deprecated("use g1_interface_pkg::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g1_interface_pkg::srv::Tentamens_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  g1_interface_pkg::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g1_interface_pkg::srv::to_yaml() instead")]]
inline std::string to_yaml(const g1_interface_pkg::srv::Tentamens_Event & msg)
{
  return g1_interface_pkg::srv::to_yaml(msg);
}

template<>
inline const char * data_type<g1_interface_pkg::srv::Tentamens_Event>()
{
  return "g1_interface_pkg::srv::Tentamens_Event";
}

template<>
inline const char * name<g1_interface_pkg::srv::Tentamens_Event>()
{
  return "g1_interface_pkg/srv/Tentamens_Event";
}

template<>
struct has_fixed_size<g1_interface_pkg::srv::Tentamens_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g1_interface_pkg::srv::Tentamens_Event>
  : std::integral_constant<bool, has_bounded_size<g1_interface_pkg::srv::Tentamens_Request>::value && has_bounded_size<g1_interface_pkg::srv::Tentamens_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<g1_interface_pkg::srv::Tentamens_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<g1_interface_pkg::srv::Tentamens>()
{
  return "g1_interface_pkg::srv::Tentamens";
}

template<>
inline const char * name<g1_interface_pkg::srv::Tentamens>()
{
  return "g1_interface_pkg/srv/Tentamens";
}

template<>
struct has_fixed_size<g1_interface_pkg::srv::Tentamens>
  : std::integral_constant<
    bool,
    has_fixed_size<g1_interface_pkg::srv::Tentamens_Request>::value &&
    has_fixed_size<g1_interface_pkg::srv::Tentamens_Response>::value
  >
{
};

template<>
struct has_bounded_size<g1_interface_pkg::srv::Tentamens>
  : std::integral_constant<
    bool,
    has_bounded_size<g1_interface_pkg::srv::Tentamens_Request>::value &&
    has_bounded_size<g1_interface_pkg::srv::Tentamens_Response>::value
  >
{
};

template<>
struct is_service<g1_interface_pkg::srv::Tentamens>
  : std::true_type
{
};

template<>
struct is_service_request<g1_interface_pkg::srv::Tentamens_Request>
  : std::true_type
{
};

template<>
struct is_service_response<g1_interface_pkg::srv::Tentamens_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // G1_INTERFACE_PKG__SRV__DETAIL__TENTAMENS__TRAITS_HPP_
