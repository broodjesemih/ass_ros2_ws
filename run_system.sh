#!/bin/bash
cd "$(dirname "$0")"
source /opt/ros/*/setup.bash 2>/dev/null
source install/setup.bash 2>/dev/null
echo "🚀 Starting ROS2 Grade Calculator System..."
ros2 launch g1_ass1_pkg system.launch.xml
