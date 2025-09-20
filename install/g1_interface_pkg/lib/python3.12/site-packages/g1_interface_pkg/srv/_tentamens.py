# generated from rosidl_generator_py/resource/_idl.py.em
# with input from g1_interface_pkg:srv/Tentamens.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

# Member 'tentamen_cijfers'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Tentamens_Request(type):
    """Metaclass of message 'Tentamens_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('g1_interface_pkg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'g1_interface_pkg.srv.Tentamens_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__tentamens__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__tentamens__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__tentamens__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__tentamens__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__tentamens__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Tentamens_Request(metaclass=Metaclass_Tentamens_Request):
    """Message class 'Tentamens_Request'."""

    __slots__ = [
        '_student_name',
        '_course_name',
        '_tentamen_cijfers',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'student_name': 'string',
        'course_name': 'string',
        'tentamen_cijfers': 'sequence<int32>',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.student_name = kwargs.get('student_name', str())
        self.course_name = kwargs.get('course_name', str())
        self.tentamen_cijfers = array.array('i', kwargs.get('tentamen_cijfers', []))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.student_name != other.student_name:
            return False
        if self.course_name != other.course_name:
            return False
        if self.tentamen_cijfers != other.tentamen_cijfers:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def student_name(self):
        """Message field 'student_name'."""
        return self._student_name

    @student_name.setter
    def student_name(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'student_name' field must be of type 'str'"
        self._student_name = value

    @builtins.property
    def course_name(self):
        """Message field 'course_name'."""
        return self._course_name

    @course_name.setter
    def course_name(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'course_name' field must be of type 'str'"
        self._course_name = value

    @builtins.property
    def tentamen_cijfers(self):
        """Message field 'tentamen_cijfers'."""
        return self._tentamen_cijfers

    @tentamen_cijfers.setter
    def tentamen_cijfers(self, value):
        if self._check_fields:
            if isinstance(value, array.array):
                assert value.typecode == 'i', \
                    "The 'tentamen_cijfers' array.array() must have the type code of 'i'"
                self._tentamen_cijfers = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'tentamen_cijfers' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._tentamen_cijfers = array.array('i', value)


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Tentamens_Response(type):
    """Metaclass of message 'Tentamens_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('g1_interface_pkg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'g1_interface_pkg.srv.Tentamens_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__tentamens__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__tentamens__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__tentamens__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__tentamens__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__tentamens__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Tentamens_Response(metaclass=Metaclass_Tentamens_Response):
    """Message class 'Tentamens_Response'."""

    __slots__ = [
        '_final_cijfer',
        '_message',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'final_cijfer': 'int32',
        'message': 'string',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.final_cijfer = kwargs.get('final_cijfer', int())
        self.message = kwargs.get('message', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.final_cijfer != other.final_cijfer:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def final_cijfer(self):
        """Message field 'final_cijfer'."""
        return self._final_cijfer

    @final_cijfer.setter
    def final_cijfer(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'final_cijfer' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'final_cijfer' field must be an integer in [-2147483648, 2147483647]"
        self._final_cijfer = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Tentamens_Event(type):
    """Metaclass of message 'Tentamens_Event'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('g1_interface_pkg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'g1_interface_pkg.srv.Tentamens_Event')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__tentamens__event
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__tentamens__event
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__tentamens__event
            cls._TYPE_SUPPORT = module.type_support_msg__srv__tentamens__event
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__tentamens__event

            from service_msgs.msg import ServiceEventInfo
            if ServiceEventInfo.__class__._TYPE_SUPPORT is None:
                ServiceEventInfo.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Tentamens_Event(metaclass=Metaclass_Tentamens_Event):
    """Message class 'Tentamens_Event'."""

    __slots__ = [
        '_info',
        '_request',
        '_response',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'info': 'service_msgs/ServiceEventInfo',
        'request': 'sequence<g1_interface_pkg/Tentamens_Request, 1>',
        'response': 'sequence<g1_interface_pkg/Tentamens_Response, 1>',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['service_msgs', 'msg'], 'ServiceEventInfo'),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['g1_interface_pkg', 'srv'], 'Tentamens_Request'), 1),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['g1_interface_pkg', 'srv'], 'Tentamens_Response'), 1),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from service_msgs.msg import ServiceEventInfo
        self.info = kwargs.get('info', ServiceEventInfo())
        self.request = kwargs.get('request', [])
        self.response = kwargs.get('response', [])

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.info != other.info:
            return False
        if self.request != other.request:
            return False
        if self.response != other.response:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def info(self):
        """Message field 'info'."""
        return self._info

    @info.setter
    def info(self, value):
        if self._check_fields:
            from service_msgs.msg import ServiceEventInfo
            assert \
                isinstance(value, ServiceEventInfo), \
                "The 'info' field must be a sub message of type 'ServiceEventInfo'"
        self._info = value

    @builtins.property
    def request(self):
        """Message field 'request'."""
        return self._request

    @request.setter
    def request(self, value):
        if self._check_fields:
            from g1_interface_pkg.srv import Tentamens_Request
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) <= 1 and
                 all(isinstance(v, Tentamens_Request) for v in value) and
                 True), \
                "The 'request' field must be a set or sequence with length <= 1 and each value of type 'Tentamens_Request'"
        self._request = value

    @builtins.property
    def response(self):
        """Message field 'response'."""
        return self._response

    @response.setter
    def response(self, value):
        if self._check_fields:
            from g1_interface_pkg.srv import Tentamens_Response
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) <= 1 and
                 all(isinstance(v, Tentamens_Response) for v in value) and
                 True), \
                "The 'response' field must be a set or sequence with length <= 1 and each value of type 'Tentamens_Response'"
        self._response = value


class Metaclass_Tentamens(type):
    """Metaclass of service 'Tentamens'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('g1_interface_pkg')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'g1_interface_pkg.srv.Tentamens')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__tentamens

            from g1_interface_pkg.srv import _tentamens
            if _tentamens.Metaclass_Tentamens_Request._TYPE_SUPPORT is None:
                _tentamens.Metaclass_Tentamens_Request.__import_type_support__()
            if _tentamens.Metaclass_Tentamens_Response._TYPE_SUPPORT is None:
                _tentamens.Metaclass_Tentamens_Response.__import_type_support__()
            if _tentamens.Metaclass_Tentamens_Event._TYPE_SUPPORT is None:
                _tentamens.Metaclass_Tentamens_Event.__import_type_support__()


class Tentamens(metaclass=Metaclass_Tentamens):
    from g1_interface_pkg.srv._tentamens import Tentamens_Request as Request
    from g1_interface_pkg.srv._tentamens import Tentamens_Response as Response
    from g1_interface_pkg.srv._tentamens import Tentamens_Event as Event

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
