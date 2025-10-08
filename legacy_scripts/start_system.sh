#!/bin/bash

echo "=== ROS2 Grade Calculator System Launcher ==="
echo ""

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo "Workspace directory: $SCRIPT_DIR"

# Check if we're in the right directory
if [ ! -f "$SCRIPT_DIR/src/g1_ass1_pkg/launch/system.launch.xml" ]; then
    echo "Error: system.launch.xml not found in expected location"
    echo "Make sure you're running this script from the workspace root"
    exit 1
fi

# Check if install directory exists
if [ ! -d "$SCRIPT_DIR/install" ]; then
    echo "Error: Install directory not found. Building project first..."
    cd "$SCRIPT_DIR"
    colcon build --packages-select g1_ass1_pkg
    if [ $? -ne 0 ]; then
        echo "Build failed!"
        exit 1
    fi
fi

# Check if PostgreSQL is running
echo "🔧 Checking PostgreSQL..."
if ! systemctl is-active --quiet postgresql; then
    echo "PostgreSQL is not running. Starting it..."
    sudo systemctl start postgresql
    
    if [ $? -ne 0 ]; then
        echo "Failed to start PostgreSQL. Please run: ./setup_postgresql.sh"
        exit 1
    fi
fi

# Test database connection
echo "🔧 Testing database connection..."
if ! ./debug_postgres.sh >/dev/null 2>&1; then
    echo "Database connection might have issues. Run ./debug_postgres.sh for details"
fi

# Set up environment
echo "Setting up ROS2 environment..."
cd "$SCRIPT_DIR"

# Source ROS2 setup
source /opt/ros/jazzy/setup.bash

# Source workspace
source install/setup.bash

echo "Starting the Grade Calculator System..."
echo ""
echo "All nodes will start:"
echo "  - tentamen_result_generator"
echo "  - cijfer_calculator"  
echo "  - final_cijfer_determinator"
echo "  - herkansing_scheduler"
echo "  - herkansing_cijfer_determinator"
echo ""
echo "Press Ctrl+C to stop all nodes"
echo ""

# Launch the system
ros2 launch g1_ass1_pkg system.launch.xml

echo ""
echo "System stopped."
