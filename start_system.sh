#!/bin/bash

echo "🚀 Starting ROS2 Cijfer Generator with PostgreSQL..."

# Check if PostgreSQL is running
if ! sudo systemctl is-active --quiet postgresql; then
    echo "📦 Starting PostgreSQL..."
    sudo systemctl start postgresql
fi

# Set up environment
cd "/home/broodjesemih/eind shit/asssssss1/ass_ros2_ws"
export PGPASSWORD=password

# Test database connection
if ! PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
    echo "❌ Database connection failed. Running setup..."
    ./setup_postgresql.sh
fi

# Source ROS2 and workspace
source /opt/ros/jazzy/setup.bash 2>/dev/null || echo "⚠️  ROS2 sourcing had warnings (but continuing...)"
source install/setup.bash 2>/dev/null || echo "⚠️  Workspace sourcing had warnings (but continuing...)"

echo "✅ Environment ready!"
echo "📊 Launching all nodes..."

# Launch the complete system
ros2 launch g1_ass1_pkg system.launch.xml
