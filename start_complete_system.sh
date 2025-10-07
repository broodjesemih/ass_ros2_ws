#!/bin/bash

# Complete Cijfer Generator System Launcher
# Dit script start alles wat je nodig hebt in de juiste volgorde

set -e  # Stop bij eerste error

echo "🚀 Starting Complete Cijfer Generator System"
echo "============================================="

# Check if we're in WSL2
if grep -qi microsoft /proc/version; then
    echo "✅ Running in WSL2 environment"
    POSTGRES_HOST="10.255.255.254"  # Windows host IP
else
    echo "⚠️  Not in WSL2 - using localhost"
    POSTGRES_HOST="localhost"
fi

# 1. Start PostgreSQL Database
echo ""
echo "🐘 Step 1: Starting PostgreSQL Database..."
cd /mnt/c/Users/semih/Assessment/1_ROS2/ass_ros2_ws
powershell.exe -c "docker-compose up -d postgres"

# 2. Wait for database to be ready
echo ""
echo "⏳ Step 2: Waiting for database to be ready..."
for i in {1..15}; do
    if powershell.exe -c "docker exec cijfer_generator_db pg_isready -U cijfer_user" > /dev/null 2>&1; then
        echo "✅ PostgreSQL is ready!"
        break
    fi
    echo "   Attempt $i/15... waiting 2 seconds"
    sleep 2
done

# 3. Verify database connection
echo ""
echo "🔍 Step 3: Verifying database connection..."
if powershell.exe -c "docker exec cijfer_generator_db psql -U cijfer_user -d cijfer_generator -c 'SELECT COUNT(*) FROM student_results;'" > /dev/null 2>&1; then
    echo "✅ Database connection verified!"
else
    echo "❌ Database connection failed!"
    exit 1
fi

# 4. Setup ROS2 environment
echo ""
echo "🤖 Step 4: Setting up ROS2 environment..."
cd ~/ros2_ws
source /opt/ros/jazzy/setup.bash
source install/setup.bash

# 5. Set environment variables
echo ""
echo "🔧 Step 5: Configuring environment variables..."
export POSTGRES_HOST=$POSTGRES_HOST
export POSTGRES_PORT=5432
export POSTGRES_DB=cijfer_generator
export POSTGRES_USER=cijfer_user
export POSTGRES_PASSWORD=cijfer_password

echo "   POSTGRES_HOST: $POSTGRES_HOST"
echo "   POSTGRES_DB: $POSTGRES_DB"
echo "   POSTGRES_USER: $POSTGRES_USER"

# 6. Start ROS2 system
echo ""
echo "🎯 Step 6: Starting ROS2 Cijfer Generator System..."
echo "   Press Ctrl+C to stop the system"
echo ""

# Option 1: Use the complete launch file
if [ -f "/mnt/c/Users/semih/Assessment/1_ROS2/ass_ros2_ws/cijfer_complete_system.launch.py" ]; then
    echo "🚀 Using complete launch file..."
    ros2 launch /mnt/c/Users/semih/Assessment/1_ROS2/ass_ros2_ws/cijfer_complete_system.launch.py db_host:=$POSTGRES_HOST
else
    # Option 2: Use the regular launch file
    echo "🚀 Using regular launch file..."
    ros2 launch g1_ass1_pkg cijfer_system.launch.py
fi

echo ""
echo "🛑 System stopped."
echo ""
echo "📊 Final database status:"
powershell.exe -c "cd C:\Users\semih\Assessment\1_ROS2\ass_ros2_ws; docker exec cijfer_generator_db psql -U cijfer_user -d cijfer_generator -c 'SELECT student_name, course, final_result FROM student_results WHERE final_result > 0 ORDER BY student_name;'"
