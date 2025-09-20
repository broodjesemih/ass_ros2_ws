// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from g1_interface_pkg:action/Herkanser.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g1_interface_pkg/action/herkanser.hpp"


#ifndef G1_INTERFACE_PKG__ACTION__DETAIL__HERKANSER__BUILDER_HPP_
#define G1_INTERFACE_PKG__ACTION__DETAIL__HERKANSER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "g1_interface_pkg/action/detail/herkanser__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_Goal_course_name
{
public:
  explicit Init_Herkanser_Goal_course_name(::g1_interface_pkg::action::Herkanser_Goal & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::action::Herkanser_Goal course_name(::g1_interface_pkg::action::Herkanser_Goal::_course_name_type arg)
  {
    msg_.course_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_Goal msg_;
};

class Init_Herkanser_Goal_student_name
{
public:
  Init_Herkanser_Goal_student_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Herkanser_Goal_course_name student_name(::g1_interface_pkg::action::Herkanser_Goal::_student_name_type arg)
  {
    msg_.student_name = std::move(arg);
    return Init_Herkanser_Goal_course_name(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_Goal>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_Goal_student_name();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_Result_message
{
public:
  explicit Init_Herkanser_Result_message(::g1_interface_pkg::action::Herkanser_Result & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::action::Herkanser_Result message(::g1_interface_pkg::action::Herkanser_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_Result msg_;
};

class Init_Herkanser_Result_final_cijfer
{
public:
  Init_Herkanser_Result_final_cijfer()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Herkanser_Result_message final_cijfer(::g1_interface_pkg::action::Herkanser_Result::_final_cijfer_type arg)
  {
    msg_.final_cijfer = std::move(arg);
    return Init_Herkanser_Result_message(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_Result>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_Result_final_cijfer();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_Feedback_status
{
public:
  explicit Init_Herkanser_Feedback_status(::g1_interface_pkg::action::Herkanser_Feedback & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::action::Herkanser_Feedback status(::g1_interface_pkg::action::Herkanser_Feedback::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_Feedback msg_;
};

class Init_Herkanser_Feedback_progress
{
public:
  Init_Herkanser_Feedback_progress()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Herkanser_Feedback_status progress(::g1_interface_pkg::action::Herkanser_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_Herkanser_Feedback_status(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_Feedback>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_Feedback_progress();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_SendGoal_Request_goal
{
public:
  explicit Init_Herkanser_SendGoal_Request_goal(::g1_interface_pkg::action::Herkanser_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::action::Herkanser_SendGoal_Request goal(::g1_interface_pkg::action::Herkanser_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_SendGoal_Request msg_;
};

class Init_Herkanser_SendGoal_Request_goal_id
{
public:
  Init_Herkanser_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Herkanser_SendGoal_Request_goal goal_id(::g1_interface_pkg::action::Herkanser_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Herkanser_SendGoal_Request_goal(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_SendGoal_Request>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_SendGoal_Request_goal_id();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_SendGoal_Response_stamp
{
public:
  explicit Init_Herkanser_SendGoal_Response_stamp(::g1_interface_pkg::action::Herkanser_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::action::Herkanser_SendGoal_Response stamp(::g1_interface_pkg::action::Herkanser_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_SendGoal_Response msg_;
};

class Init_Herkanser_SendGoal_Response_accepted
{
public:
  Init_Herkanser_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Herkanser_SendGoal_Response_stamp accepted(::g1_interface_pkg::action::Herkanser_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_Herkanser_SendGoal_Response_stamp(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_SendGoal_Response>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_SendGoal_Response_accepted();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_SendGoal_Event_response
{
public:
  explicit Init_Herkanser_SendGoal_Event_response(::g1_interface_pkg::action::Herkanser_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::action::Herkanser_SendGoal_Event response(::g1_interface_pkg::action::Herkanser_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_SendGoal_Event msg_;
};

class Init_Herkanser_SendGoal_Event_request
{
public:
  explicit Init_Herkanser_SendGoal_Event_request(::g1_interface_pkg::action::Herkanser_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_Herkanser_SendGoal_Event_response request(::g1_interface_pkg::action::Herkanser_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Herkanser_SendGoal_Event_response(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_SendGoal_Event msg_;
};

class Init_Herkanser_SendGoal_Event_info
{
public:
  Init_Herkanser_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Herkanser_SendGoal_Event_request info(::g1_interface_pkg::action::Herkanser_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Herkanser_SendGoal_Event_request(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_SendGoal_Event>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_SendGoal_Event_info();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_GetResult_Request_goal_id
{
public:
  Init_Herkanser_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::g1_interface_pkg::action::Herkanser_GetResult_Request goal_id(::g1_interface_pkg::action::Herkanser_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_GetResult_Request>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_GetResult_Request_goal_id();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_GetResult_Response_result
{
public:
  explicit Init_Herkanser_GetResult_Response_result(::g1_interface_pkg::action::Herkanser_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::action::Herkanser_GetResult_Response result(::g1_interface_pkg::action::Herkanser_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_GetResult_Response msg_;
};

class Init_Herkanser_GetResult_Response_status
{
public:
  Init_Herkanser_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Herkanser_GetResult_Response_result status(::g1_interface_pkg::action::Herkanser_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_Herkanser_GetResult_Response_result(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_GetResult_Response>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_GetResult_Response_status();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_GetResult_Event_response
{
public:
  explicit Init_Herkanser_GetResult_Event_response(::g1_interface_pkg::action::Herkanser_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::action::Herkanser_GetResult_Event response(::g1_interface_pkg::action::Herkanser_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_GetResult_Event msg_;
};

class Init_Herkanser_GetResult_Event_request
{
public:
  explicit Init_Herkanser_GetResult_Event_request(::g1_interface_pkg::action::Herkanser_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_Herkanser_GetResult_Event_response request(::g1_interface_pkg::action::Herkanser_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_Herkanser_GetResult_Event_response(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_GetResult_Event msg_;
};

class Init_Herkanser_GetResult_Event_info
{
public:
  Init_Herkanser_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Herkanser_GetResult_Event_request info(::g1_interface_pkg::action::Herkanser_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_Herkanser_GetResult_Event_request(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_GetResult_Event>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_GetResult_Event_info();
}

}  // namespace g1_interface_pkg


namespace g1_interface_pkg
{

namespace action
{

namespace builder
{

class Init_Herkanser_FeedbackMessage_feedback
{
public:
  explicit Init_Herkanser_FeedbackMessage_feedback(::g1_interface_pkg::action::Herkanser_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::g1_interface_pkg::action::Herkanser_FeedbackMessage feedback(::g1_interface_pkg::action::Herkanser_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_FeedbackMessage msg_;
};

class Init_Herkanser_FeedbackMessage_goal_id
{
public:
  Init_Herkanser_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Herkanser_FeedbackMessage_feedback goal_id(::g1_interface_pkg::action::Herkanser_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_Herkanser_FeedbackMessage_feedback(msg_);
  }

private:
  ::g1_interface_pkg::action::Herkanser_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g1_interface_pkg::action::Herkanser_FeedbackMessage>()
{
  return g1_interface_pkg::action::builder::Init_Herkanser_FeedbackMessage_goal_id();
}

}  // namespace g1_interface_pkg

#endif  // G1_INTERFACE_PKG__ACTION__DETAIL__HERKANSER__BUILDER_HPP_
