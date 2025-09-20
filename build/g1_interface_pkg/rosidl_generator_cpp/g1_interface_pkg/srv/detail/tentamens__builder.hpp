// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from g1_interface_pkg:srv/Tentamens.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/srv/tentamens.hpp"


#ifndef G1_INTERFACE_PKG__SRV__DETAIL__TENTAMENS__BUILDER_HPP_
#define G1_INTERFACE_PKG__SRV__DETAIL__TENTAMENS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "g1_interface_pkg/srv/detail/tentamens__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace g1_interface_pkg
{

namespace srv
{

namespace builder
{

class Init_Tentamens_Request_tentamen_cijfers
{
public:
  explicit Init_Tentamens_Request_tentamen_cijfers(::g1_interface_pkg::srv::Tentamens_Request & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::srv::Tentamens_Request tentamen_cijfers(::g1_interface_pkg::srv::Tentamens_Request::_tentamen_cijfers_type arg)
  {
    msg_.tentamen_cijfers = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::srv::Tentamens_Request msg_;
};

class Init_Tentamens_Request_course_name
{
public:
  explicit Init_Tentamens_Request_course_name(::g1_interface_pkg::srv::Tentamens_Request & msg)
  : msg_(msg)
  {}
  Init_Tentamens_Request_tentamen_cijfers course_name(::g1_interface_pkg::srv::Tentamens_Request::_course_name_type arg)
  {
    msg_.course_name = std::move(arg);
    return Init_Tentamens_Request_tentamen_cijfers(msg_);
  }

private:
  ::g1_interface_pkg::srv::Tentamens_Request msg_;
};

class Init_Tentamens_Request_student_name
{
public:
  Init_Tentamens_Request_student_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Tentamens_Request_course_name student_name(::g1_interface_pkg::srv::Tentamens_Request::_student_name_type arg)
  {
    msg_.student_name = std::move(arg);
    return Init_Tentamens_Request_course_name(msg_);
  }

private:
  ::g1_interface_pkg::srv::Tentamens_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::srv::Tentamens_Request>()
{
  return g1_interface_pkg::srv::builder::Init_Tentamens_Request_student_name();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace srv
{

namespace builder
{

class Init_Tentamens_Response_message
{
public:
  explicit Init_Tentamens_Response_message(::g1_interface_pkg::srv::Tentamens_Response & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::srv::Tentamens_Response message(::g1_interface_pkg::srv::Tentamens_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::srv::Tentamens_Response msg_;
};

class Init_Tentamens_Response_final_cijfer
{
public:
  Init_Tentamens_Response_final_cijfer()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Tentamens_Response_message final_cijfer(::g1_interface_pkg::srv::Tentamens_Response::_final_cijfer_type arg)
  {
    msg_.final_cijfer = std::move(arg);
    return Init_Tentamens_Response_message(msg_);
  }

private:
  ::g1_interface_pkg::srv::Tentamens_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::srv::Tentamens_Response>()
{
  return g1_interface_pkg::srv::builder::Init_Tentamens_Response_final_cijfer();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace srv
{

namespace builder
{

class Init_Tentamens_Event_response
{
public:
  explicit Init_Tentamens_Event_response(::g1_interface_pkg::srv::Tentamens_Event & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::srv::Tentamens_Event response(::g1_interface_pkg::srv::Tentamens_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::srv::Tentamens_Event msg_;
};

class Init_Tentamens_Event_request
{
public:
  explicit Init_Tentamens_Event_request(::g1_interface_pkg::srv::Tentamens_Event & msg)
  : msg_(msg)
  {}
  Init_Tentamens_Event_response request(::g1_interface_pkg::srv::Tentamens_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Tentamens_Event_response(msg_);
  }

private:
  ::g1_interface_pkg::srv::Tentamens_Event msg_;
};

class Init_Tentamens_Event_info
{
public:
  Init_Tentamens_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Tentamens_Event_request info(::g1_interface_pkg::srv::Tentamens_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Tentamens_Event_request(msg_);
  }

private:
  ::g1_interface_pkg::srv::Tentamens_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::srv::Tentamens_Event>()
{
  return g1_interface_pkg::srv::builder::Init_Tentamens_Event_info();
}

}  // namespace g1_interface_pkg

#endif  // G1_INTERFACE_PKG__SRV__DETAIL__TENTAMENS__BUILDER_HPP_
