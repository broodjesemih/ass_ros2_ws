#!/bin/bash

# Super Simple Complete System Launcher
echo "🚀 Complete Cijfer Generator System"
echo "==================================="

# 1. Start database
echo "🐘 Starting PostgreSQL..."
cd /mnt/c/Users/semih/Assessment/1_ROS2/ass_ros2_ws
powershell.exe -c "docker-compose up -d postgres"

# 2. Wait for database
echo "⏳ Waiting for database (10 seconds)..."
sleep 10

# 3. Set environment variables
export POSTGRES_HOST=10.255.255.254
export POSTGRES_PORT=5432
export POSTGRES_DB=cijfer_generator
export POSTGRES_USER=cijfer_user
export POSTGRES_PASSWORD=cijfer_password

# 4. Start ROS2
echo "🤖 Starting ROS2 system..."
cd ~/ros2_ws
source /opt/ros/jazzy/setup.bash
source install/setup.bash

echo "✅ System ready! Running for 60 seconds..."
timeout 60s ros2 launch g1_ass1_pkg cijfer_system.launch.py

# 5. Show results
echo ""
echo "📊 Final Results:"
powershell.exe -c "cd C:\Users\semih\Assessment\1_ROS2\ass_ros2_ws; docker exec cijfer_generator_db psql -U cijfer_user -d cijfer_generator -c 'SELECT student_name, course, final_result FROM student_results WHERE final_result > 0 ORDER BY student_name;'"

echo ""
echo "✅ Test completed!"
