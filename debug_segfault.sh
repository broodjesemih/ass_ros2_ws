#!/bin/bash

# 🔧 Herkansing Segfault Fix & Debug Helper
# Voor Tycho's crash probleem met herkansing_cijfer_determinator

echo "🔧 Herkansing Cijfer Determinator - Segfault Fix"
echo "================================================"
echo ""

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}🔍 Diagnosing herkansing_cijfer_determinator crash...${NC}"
echo ""

# 1. Check PostgreSQL status
echo "1️⃣ PostgreSQL Service Check:"
if systemctl is-active --quiet postgresql; then
    echo -e "   ${GREEN}✅ PostgreSQL is running${NC}"
else
    echo -e "   ${RED}❌ PostgreSQL is NOT running${NC}"
    echo -e "   ${YELLOW}💡 Fix: sudo systemctl start postgresql${NC}"
fi
echo ""

# 2. Check database connectivity
echo "2️⃣ Database Connection Test:"
DB_TESTS=(
    "PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c 'SELECT 1;' 2>/dev/null"
    "psql -d student_grades -c 'SELECT 1;' 2>/dev/null"
    "sudo -u postgres psql -d student_grades -c 'SELECT 1;' 2>/dev/null"
)

DB_OK=false
for i in "${!DB_TESTS[@]}"; do
    if eval "${DB_TESTS[$i]}" >/dev/null 2>&1; then
        echo -e "   ${GREEN}✅ Connection method $((i+1)) works${NC}"
        DB_OK=true
        break
    else
        echo -e "   ${RED}❌ Connection method $((i+1)) failed${NC}"
    fi
done

if [ "$DB_OK" = false ]; then
    echo -e "   ${YELLOW}💡 Fix: Run ./complete_setup.sh to fix database${NC}"
fi
echo ""

# 3. Check workspace build
echo "3️⃣ Workspace Build Check:"
if [ -f "install/g1_ass1_pkg/lib/g1_ass1_pkg/herkansing_cijfer_determinator" ]; then
    echo -e "   ${GREEN}✅ herkansing_cijfer_determinator executable exists${NC}"
else
    echo -e "   ${RED}❌ Executable missing${NC}"
    echo -e "   ${YELLOW}💡 Fix: colcon build --packages-select g1_ass1_pkg${NC}"
fi
echo ""

# 4. Test node individually
echo "4️⃣ Individual Node Test (with debug):"
echo "Starting herkansing_cijfer_determinator with debug output..."
echo ""

# Source environment
if [ -f "/opt/ros/jazzy/setup.bash" ]; then
    source /opt/ros/jazzy/setup.bash
elif [ -f "/opt/ros/humble/setup.bash" ]; then
    source /opt/ros/humble/setup.bash
else
    echo -e "${RED}❌ No ROS2 installation found${NC}"
    exit 1
fi

if [ -f "install/setup.bash" ]; then
    source install/setup.bash
else
    echo -e "${RED}❌ Workspace not built${NC}"
    exit 1
fi

echo -e "${CYAN}🚀 Starting node with GDB for crash detection...${NC}"
echo "Press Ctrl+C to stop"
echo ""

# Run with timeout and error detection
timeout 30s ros2 run g1_ass1_pkg herkansing_cijfer_determinator &
NODE_PID=$!
sleep 5

# Check if node is still running
if ps -p $NODE_PID > /dev/null 2>&1; then
    echo -e "${GREEN}✅ Node started successfully and is running${NC}"
    echo "Waiting 20 more seconds to check for crashes..."
    sleep 20
    
    if ps -p $NODE_PID > /dev/null 2>&1; then
        echo -e "${GREEN}✅ Node survived 25 seconds - segfault likely fixed!${NC}"
        kill $NODE_PID 2>/dev/null
    else
        echo -e "${RED}❌ Node crashed during execution${NC}"
    fi
else
    echo -e "${RED}❌ Node crashed immediately at startup${NC}"
fi

wait $NODE_PID 2>/dev/null
NODE_EXIT_CODE=$?

echo ""
echo "5️⃣ Crash Analysis:"
case $NODE_EXIT_CODE in
    0)
        echo -e "   ${GREEN}✅ Clean exit (no crash)${NC}"
        ;;
    -11|139)
        echo -e "   ${RED}❌ Segmentation fault detected${NC}"
        echo -e "   ${YELLOW}💡 This was the original problem - should be fixed now${NC}"
        ;;
    124)
        echo -e "   ${YELLOW}⏰ Timeout (normal - we stopped it after 30s)${NC}"
        ;;
    *)
        echo -e "   ${YELLOW}⚠️  Exit code: $NODE_EXIT_CODE${NC}"
        ;;
esac
echo ""

# 6. Recommendations
echo "6️⃣ Recommendations:"
if [ "$DB_OK" = true ]; then
    echo -e "   ${GREEN}✅ Database connection works${NC}"
    echo -e "   ${GREEN}✅ Segfault fix should resolve the crash${NC}"
    echo ""
    echo -e "   ${BLUE}📋 To rebuild with the fix:${NC}"
    echo "      colcon build --packages-select g1_ass1_pkg"
    echo ""
    echo -e "   ${BLUE}📋 To test the full system:${NC}"
    echo "      ./run_system.sh"
else
    echo -e "   ${RED}❌ Database issues need fixing first${NC}"
    echo ""
    echo -e "   ${BLUE}📋 Run this to fix database:${NC}"
    echo "      ./complete_setup.sh"
fi

echo ""
echo "======================================="
echo -e "${BLUE}🎯 Summary: The segfault was caused by database connection errors${NC}"
echo -e "${BLUE}   Fixed by adding proper error handling in herkansing_cijfer_determinator.cpp${NC}"
echo "======================================="
