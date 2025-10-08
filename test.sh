#!/bin/bash

# 🧪 Universele ROS2 Test Runner
# Automatisch detecteert welke tests mogelijk zijn en voert ze uit
echo "🧪 ROS2 Unit Test Runner"
echo "======================="

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
NC='\033[0m'

cd /home/broodjesemih/eind\ shit/asssssss1/ass_ros2_ws

# Detecteer ROS2 systeem
echo -e "${BLUE}🔍 Checking ROS2 system...${NC}"
if ros2 service list 2>/dev/null | grep -q "calculate_final_cijfer"; then
    echo -e "${GREEN}✅ ROS2 system running - All tests available${NC}"
    BUILD_MODE="ALL"
    TEST_MODE="complete"
else
    echo -e "${YELLOW}⚠️  ROS2 system not running - Standalone tests only${NC}"
    BUILD_MODE="STANDALONE"
    TEST_MODE="standalone"
fi

# Build
echo -e "${BLUE}📦 Building...${NC}"
if [ "$BUILD_MODE" = "ALL" ]; then
    colcon build --packages-select g1_ass1_pkg --cmake-args -DBUILD_ALL_TESTS=ON
else
    colcon build --packages-select g1_ass1_pkg
fi

if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Build failed!${NC}"
    exit 1
fi

# Test
echo -e "${BLUE}🧪 Running tests...${NC}"
colcon test --packages-select g1_ass1_pkg

# Results
echo ""
echo -e "${BLUE}📊 Results:${NC}"
colcon test-result --verbose

# Summary
echo ""
echo -e "${GREEN}🎯 Summary:${NC}"
RESULT=$(colcon test-result --verbose | head -1)
echo -e "${GREEN}   $RESULT${NC}"

if [ "$TEST_MODE" = "complete" ]; then
    echo -e "${GREEN}   ✅ Full integration testing completed${NC}"
else
    echo -e "${YELLOW}   ⚠️  Standalone testing only${NC}"
    echo -e "${YELLOW}   💡 Start ROS2 system for integration tests:${NC}"
    echo -e "${YELLOW}      ./start_system.sh${NC}"
fi
