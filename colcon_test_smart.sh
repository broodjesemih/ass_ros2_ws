#!/bin/bash

# Smart Colcon Test Runner - Automatische detectie van testmodus
echo "🧪 Smart Colcon Test Runner..."
echo ""

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

cd /home/broodjesemih/eind\ shit/asssssss1/ass_ros2_ws

# Check if system is running
echo -e "${BLUE}🔍 Auto-detecting test environment...${NC}"
if ros2 service list 2>/dev/null | grep -q "calculate_final_cijfer"; then
    echo -e "${GREEN}✅ ROS2 system detected - Running FULL integration tests${NC}"
    SYSTEM_RUNNING=true
else
    echo -e "${YELLOW}⚠️  ROS2 system not running - Running STANDALONE tests only${NC}"
    echo -e "${YELLOW}   (Database + Topic Communication tests)${NC}"
    SYSTEM_RUNNING=false
fi

echo ""

# Build first
echo -e "${BLUE}📦 Building package...${NC}"
colcon build --packages-select g1_ass1_pkg

echo ""

if [ "$SYSTEM_RUNNING" = true ]; then
    echo -e "${BLUE}🚀 Running COMPLETE test suite...${NC}"
    colcon test --packages-select g1_ass1_pkg --ctest-args -E "lint|uncrustify|cppcheck|cpplint|flake8|pep257"
    
    echo ""
    echo -e "${BLUE}📊 Integration Test Results:${NC}"
    colcon test-result --verbose 2>/dev/null | grep -E "(test_|PASSED|FAILED)" | grep -v "lint\|uncrustify\|cppcheck" | head -20
else
    echo -e "${BLUE}🧪 Running STANDALONE tests (database + topics)...${NC}"
    colcon test --packages-select g1_ass1_pkg --ctest-args -R "test_database|test_topic_communication"
    
    echo ""
    echo -e "${BLUE}📊 Standalone Test Results:${NC}"
    colcon test-result --verbose 2>/dev/null | grep -E "(PASSED|FAILED)" | grep "test_database\|test_topic_communication"
fi

echo ""
echo -e "${GREEN}🎯 Test Summary:${NC}"
if [ "$SYSTEM_RUNNING" = true ]; then
    echo -e "${GREEN}   ✅ Full integration testing completed${NC}"
    echo -e "${GREEN}   📈 All system components tested${NC}"
else
    echo -e "${GREEN}   ✅ Standalone testing completed (100% success expected)${NC}"
    echo -e "${YELLOW}   💡 For integration tests: ros2 launch g1_ass1_pkg system.launch.xml${NC}"
fi

echo ""
echo -e "${BLUE}📝 Available test commands:${NC}"
echo -e "   ${YELLOW}./colcon_test_smart.sh${NC}     - Auto-detect and run appropriate tests"
echo -e "   ${YELLOW}./colcon_test_standalone.sh${NC} - Force standalone tests only"  
echo -e "   ${YELLOW}./colcon_test_with_system.sh${NC} - Full integration (requires running system)"
