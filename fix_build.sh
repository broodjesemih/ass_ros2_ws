#!/bin/bash

# Quick build fix for WSL dependency issue
# This script builds packages in the correct order

echo "🔧 Fixing ROS2 build dependency order..."

# Source ROS2 environment
if [ -f "/opt/ros/jazzy/setup.bash" ]; then
    source /opt/ros/jazzy/setup.bash
    echo "✅ Sourced ROS2 Jazzy"
elif [ -f "/opt/ros/humble/setup.bash" ]; then
    source /opt/ros/humble/setup.bash
    echo "✅ Sourced ROS2 Humble"
else
    echo "❌ Cannot find ROS2 setup file"
    exit 1
fi

# Clean previous build if it exists
if [ -d "build" ] || [ -d "install" ]; then
    echo "🧹 Cleaning previous build..."
    rm -rf build/ install/ log/
fi

echo "📦 Building g1_interface_pkg first (contains message definitions)..."
colcon build --packages-select g1_interface_pkg

if [ $? -ne 0 ]; then
    echo "❌ Interface package build failed!"
    exit 1
fi

echo "✅ Interface package built successfully"

# Source the built interface package
if [ -f "install/setup.bash" ]; then
    source install/setup.bash
    echo "✅ Sourced built interface package"
fi

echo "📦 Building g1_ass1_pkg (main application)..."
colcon build --packages-select g1_ass1_pkg

if [ $? -ne 0 ]; then
    echo "❌ Main package build failed!"
    exit 1
fi

echo "✅ All packages built successfully!"
echo ""
echo "🚀 You can now run the system with: ./run_system.sh"
