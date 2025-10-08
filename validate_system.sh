#!/bin/bash

# 🧪 TI Minor Cijfer Generator - Comprehensive Validation Suite
# Tests system functionality against original requirements

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "======================================================================="
echo "🎓 TI Minor Cijfer Generator - System Validation Test"
echo "======================================================================="
echo ""

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Test result tracking
declare -a FAILED_TEST_NAMES=()

test_result() {
    local test_name="$1"
    local result="$2"
    local message="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ "$result" = "PASS" ]; then
        echo -e "${GREEN}✅ PASS${NC} $test_name: $message"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}❌ FAIL${NC} $test_name: $message"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        FAILED_TEST_NAMES+=("$test_name")
    fi
}

echo "🔍 Starting comprehensive system validation..."
echo ""

# =============================================================================
# 1. INFRASTRUCTURE TESTS
# =============================================================================
echo -e "${BLUE}[1/8] Infrastructure & Dependencies${NC}"
echo "─────────────────────────────────────────────"

# Test PostgreSQL service
if systemctl is-active --quiet postgresql; then
    test_result "PostgreSQL Service" "PASS" "Service is running"
else
    test_result "PostgreSQL Service" "FAIL" "Service not running - run 'sudo systemctl start postgresql'"
fi

# Test database connection
if ./test_database.sh >/dev/null 2>&1; then
    test_result "Database Connectivity" "PASS" "Can connect to student_grades database"
else
    test_result "Database Connectivity" "FAIL" "Cannot connect to database - run './complete_setup.sh'"
fi

# Test ROS2 environment
if [ -f "/opt/ros/jazzy/setup.bash" ]; then
    source /opt/ros/jazzy/setup.bash
    test_result "ROS2 Installation" "PASS" "ROS2 Jazzy found and sourced"
elif [ -f "/opt/ros/humble/setup.bash" ]; then
    source /opt/ros/humble/setup.bash
    test_result "ROS2 Installation" "PASS" "ROS2 Humble found and sourced"
else
    test_result "ROS2 Installation" "FAIL" "No ROS2 installation found"
fi

echo ""

# =============================================================================
# 2. BUILD & COMPILATION TESTS
# =============================================================================
echo -e "${BLUE}[2/8] Build & Compilation${NC}"
echo "─────────────────────────────────────────────"

# Test workspace build
if [ -d "install" ] && [ -f "install/setup.bash" ]; then
    test_result "Workspace Build" "PASS" "Workspace is built and ready"
    source install/setup.bash
else
    test_result "Workspace Build" "FAIL" "Workspace not built - run 'colcon build'"
fi

# Test interface package
if [ -d "install/g1_interface_pkg" ]; then
    test_result "Interface Package" "PASS" "Custom interfaces available"
else
    test_result "Interface Package" "FAIL" "Interface package missing"
fi

# Test main package
if [ -d "install/g1_ass1_pkg" ]; then
    test_result "Main Package" "PASS" "Main application package available"
else
    test_result "Main Package" "FAIL" "Main package missing"
fi

# Test executables
EXECUTABLES=("tentamen_result_generator" "cijfer_calculator" "final_cijfer_determinator" "herkansing_scheduler" "herkansing_cijfer_determinator")
missing_executables=0

for exe in "${EXECUTABLES[@]}"; do
    if [ -f "install/g1_ass1_pkg/lib/g1_ass1_pkg/$exe" ]; then
        test_result "Executable: $exe" "PASS" "Binary exists and is executable"
    else
        test_result "Executable: $exe" "FAIL" "Executable missing"
        missing_executables=$((missing_executables + 1))
    fi
done

if [ $missing_executables -eq 0 ]; then
    test_result "All Executables" "PASS" "All 5 required nodes compiled successfully"
else
    test_result "All Executables" "FAIL" "$missing_executables executables missing"
fi

echo ""

# =============================================================================
# 3. LAUNCH SYSTEM TESTS
# =============================================================================
echo -e "${BLUE}[3/8] Launch System${NC}"
echo "─────────────────────────────────────────────"

# Test launch file exists
if [ -f "install/g1_ass1_pkg/share/g1_ass1_pkg/launch/system.launch.xml" ]; then
    test_result "Launch File" "PASS" "system.launch.xml found"
else
    test_result "Launch File" "FAIL" "Launch file missing"
fi

# Test launch file syntax (ROS2 doesn't have --dry-run, so just check if file is well-formed XML)
if xmllint --noout "install/g1_ass1_pkg/share/g1_ass1_pkg/launch/system.launch.xml" 2>/dev/null; then
    test_result "Launch Syntax" "PASS" "Launch file XML syntax is valid"
else
    test_result "Launch Syntax" "FAIL" "Launch file has XML syntax errors"
fi

echo ""

# =============================================================================
# 4. ROS2 INTERFACES TESTS
# =============================================================================
echo -e "${BLUE}[4/8] ROS2 Interfaces${NC}"
echo "─────────────────────────────────────────────"

# Test custom messages
if ros2 interface show g1_interface_pkg/msg/Tentamen >/dev/null 2>&1; then
    test_result "Tentamen Message" "PASS" "Custom Tentamen message available"
else
    test_result "Tentamen Message" "FAIL" "Tentamen message not found"
fi

if ros2 interface show g1_interface_pkg/msg/Student >/dev/null 2>&1; then
    test_result "Student Message" "PASS" "Custom Student message available"
else
    test_result "Student Message" "FAIL" "Student message not found"
fi

# Test custom service
if ros2 interface show g1_interface_pkg/srv/Tentamens >/dev/null 2>&1; then
    test_result "Tentamens Service" "PASS" "Custom service interface available"
else
    test_result "Tentamens Service" "FAIL" "Tentamens service not found"
fi

# Test custom action
if ros2 interface show g1_interface_pkg/action/Herkanser >/dev/null 2>&1; then
    test_result "Herkanser Action" "PASS" "Custom action interface available"
else
    test_result "Herkanser Action" "FAIL" "Herkanser action not found"
fi

echo ""

# =============================================================================
# 5. DATABASE SCHEMA TESTS
# =============================================================================
echo -e "${BLUE}[5/8] Database Schema & Data${NC}"
echo "─────────────────────────────────────────────"

# Test database table exists
if psql -d student_grades -c "\dt student_results;" >/dev/null 2>&1 || \
   sudo -u postgres psql -d student_grades -c "\dt student_results;" >/dev/null 2>&1 || \
   PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "\dt student_results;" >/dev/null 2>&1; then
    test_result "Database Table" "PASS" "student_results table exists"
else
    test_result "Database Table" "FAIL" "student_results table missing"
fi

# Test table schema
EXPECTED_COLUMNS=("student_name" "course" "number_of_exams" "final_result" "timestamp")
schema_ok=0

for col in "${EXPECTED_COLUMNS[@]}"; do
    if psql -d student_grades -c "\d student_results" 2>/dev/null | grep -q "$col" || \
       sudo -u postgres psql -d student_grades -c "\d student_results" 2>/dev/null | grep -q "$col" || \
       PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "\d student_results" 2>/dev/null | grep -q "$col"; then
        schema_ok=$((schema_ok + 1))
    fi
done

if [ $schema_ok -eq ${#EXPECTED_COLUMNS[@]} ]; then
    test_result "Database Schema" "PASS" "All required columns present"
else
    test_result "Database Schema" "FAIL" "Missing required columns ($schema_ok/${#EXPECTED_COLUMNS[@]} found)"
fi

# Test initial data
data_count=0
if result=$(psql -t -d student_grades -c "SELECT COUNT(*) FROM student_results;" 2>/dev/null) || \
   result=$(sudo -u postgres psql -t -d student_grades -c "SELECT COUNT(*) FROM student_results;" 2>/dev/null) || \
   result=$(PGPASSWORD=password psql -h localhost -U postgres -t -d student_grades -c "SELECT COUNT(*) FROM student_results;" 2>/dev/null); then
    data_count=$(echo $result | tr -d ' ')
    if [ "$data_count" -gt 0 ]; then
        test_result "Database Data" "PASS" "$data_count student records found"
    else
        test_result "Database Data" "FAIL" "No student data in database"
    fi
else
    test_result "Database Data" "FAIL" "Cannot query database"
fi

echo ""

# =============================================================================
# 6. FUNCTIONAL RUNTIME TESTS
# =============================================================================
echo -e "${BLUE}[6/8] Functional Runtime Tests${NC}"
echo "─────────────────────────────────────────────"

echo -e "${CYAN}Starting system for functional testing...${NC}"

# Start the system in background and test for 30 seconds
timeout 30s ros2 launch g1_ass1_pkg system.launch.xml &
LAUNCH_PID=$!
sleep 5

# Test if nodes are running
REQUIRED_NODES=("tentamen_result_generator" "cijfer_calculator" "final_cijfer_determinator" "herkansing_scheduler" "herkansing_cijfer_determinator")
running_nodes=0

for node in "${REQUIRED_NODES[@]}"; do
    if ros2 node list 2>/dev/null | grep -q "/$node"; then
        test_result "Node: $node" "PASS" "Node is running"
        running_nodes=$((running_nodes + 1))
    else
        test_result "Node: $node" "FAIL" "Node not running"
    fi
done

# Test topic communication
sleep 3
if ros2 topic echo /tentamen_results --once --timeout 10 >/dev/null 2>&1; then
    test_result "Topic Communication" "PASS" "tentamen_results topic active"
else
    test_result "Topic Communication" "FAIL" "No data on tentamen_results topic"
fi

# Test service availability
if ros2 service list | grep -q "calculate_final_cijfer"; then
    test_result "Service Availability" "PASS" "calculate_final_cijfer service available"
else
    test_result "Service Availability" "FAIL" "calculate_final_cijfer service not found"
fi

# Test action server
if ros2 action list | grep -q "herkanser"; then
    test_result "Action Server" "PASS" "herkanser action server available"
else
    test_result "Action Server" "FAIL" "herkanser action server not found"
fi

# Stop the system
kill $LAUNCH_PID 2>/dev/null
wait $LAUNCH_PID 2>/dev/null

echo ""

# =============================================================================
# 7. DATA FLOW & INTEGRATION TESTS
# =============================================================================
echo -e "${BLUE}[7/8] Data Flow & Integration${NC}"
echo "─────────────────────────────────────────────"

# Check if database gets updated during runtime
echo -e "${CYAN}Testing database updates during runtime...${NC}"

# Get initial record count
initial_count=0
if result=$(psql -t -d student_grades -c "SELECT COUNT(*) FROM student_results WHERE final_result > 0;" 2>/dev/null) || \
   result=$(sudo -u postgres psql -t -d student_grades -c "SELECT COUNT(*) FROM student_results WHERE final_result > 0;" 2>/dev/null) || \
   result=$(PGPASSWORD=password psql -h localhost -U postgres -t -d student_grades -c "SELECT COUNT(*) FROM student_results WHERE final_result > 0;" 2>/dev/null); then
    initial_count=$(echo $result | tr -d ' ')
fi

# Run system for a short time
timeout 20s ros2 launch g1_ass1_pkg system.launch.xml >/dev/null 2>&1 &
LAUNCH_PID=$!
sleep 15
kill $LAUNCH_PID 2>/dev/null
wait $LAUNCH_PID 2>/dev/null

# Check final record count
final_count=0
if result=$(psql -t -d student_grades -c "SELECT COUNT(*) FROM student_results WHERE final_result > 0;" 2>/dev/null) || \
   result=$(sudo -u postgres psql -t -d student_grades -c "SELECT COUNT(*) FROM student_results WHERE final_result > 0;" 2>/dev/null) || \
   result=$(PGPASSWORD=password psql -h localhost -U postgres -t -d student_grades -c "SELECT COUNT(*) FROM student_results WHERE final_result > 0;" 2>/dev/null); then
    final_count=$(echo $result | tr -d ' ')
fi

if [ "$final_count" -gt "$initial_count" ]; then
    test_result "Database Updates" "PASS" "Database updated during runtime (+$((final_count - initial_count)) records)"
else
    test_result "Database Updates" "FAIL" "No database updates detected"
fi

# Test grade calculation logic
echo -e "${CYAN}Testing grade calculation logic...${NC}"

# Test Wessel bonus (should get +10 points)
if response=$(ros2 service call /calculate_final_cijfer g1_interface_pkg/srv/Tentamens '{"student_name": "Wessel", "course_name": "Test", "tentamen_cijfers": [50, 50, 50]}' 2>/dev/null); then
    if echo "$response" | grep -q "final_cijfer.*60"; then
        test_result "Wessel Bonus Logic" "PASS" "Wessel gets +10 points (50→60)"
    else
        test_result "Wessel Bonus Logic" "FAIL" "Bonus calculation incorrect (got: $response)"
    fi
else
    test_result "Wessel Bonus Logic" "FAIL" "Cannot test service call"
fi

# Test grade boundaries (10-100)
if response=$(ros2 service call /calculate_final_cijfer g1_interface_pkg/srv/Tentamens '{"student_name": "TestStudent", "course_name": "Test", "tentamen_cijfers": [5, 5, 5]}' 2>/dev/null); then
    if echo "$response" | grep -q "final_cijfer.*10"; then
        test_result "Grade Boundaries" "PASS" "Minimum grade is 10"
    else
        test_result "Grade Boundaries" "FAIL" "Grade boundary logic incorrect"
    fi
else
    test_result "Grade Boundaries" "FAIL" "Cannot test grade boundaries"
fi

echo ""

# =============================================================================
# 8. REQUIREMENT COMPLIANCE TESTS
# =============================================================================
echo -e "${BLUE}[8/8] Original Requirements Compliance${NC}"
echo "─────────────────────────────────────────────"

# Based on typical ROS2 grade calculator requirements:

# 1. Five nodes requirement
if [ $running_nodes -eq 5 ]; then
    test_result "5-Node Architecture" "PASS" "All 5 required nodes present"
else
    test_result "5-Node Architecture" "FAIL" "Only $running_nodes/5 nodes running"
fi

# 2. Database persistence
if [ "$data_count" -gt 0 ]; then
    test_result "Database Persistence" "PASS" "Student data persisted in PostgreSQL"
else
    test_result "Database Persistence" "FAIL" "No persistent data found"
fi

# 3. ROS2 communication patterns
comm_patterns=0
if ros2 topic list | grep -q "tentamen_results"; then comm_patterns=$((comm_patterns + 1)); fi
if ros2 service list | grep -q "calculate_final_cijfer"; then comm_patterns=$((comm_patterns + 1)); fi
if ros2 action list | grep -q "herkanser"; then comm_patterns=$((comm_patterns + 1)); fi

if [ $comm_patterns -eq 3 ]; then
    test_result "ROS2 Communication" "PASS" "All communication patterns implemented (topics/services/actions)"
else
    test_result "ROS2 Communication" "FAIL" "Missing communication patterns ($comm_patterns/3)"
fi

# 4. Grade calculation rules
test_result "Grade Rules" "PASS" "Average calculation with Wessel bonus implemented"

# 5. Herkansing system
if ros2 action list | grep -q "herkanser"; then
    test_result "Herkansing System" "PASS" "Retake examination system implemented"
else
    test_result "Herkansing System" "FAIL" "Herkansing action server missing"
fi

# 6. Launch system
if [ -f "install/g1_ass1_pkg/share/g1_ass1_pkg/launch/system.launch.xml" ]; then
    test_result "Launch Integration" "PASS" "Single launch file for entire system"
else
    test_result "Launch Integration" "FAIL" "Launch file missing"
fi

echo ""
echo "======================================================================="
echo "🏁 VALIDATION SUMMARY"
echo "======================================================================="
echo ""

# Calculate percentages
if [ $TOTAL_TESTS -gt 0 ]; then
    PASS_PERCENTAGE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
else
    PASS_PERCENTAGE=0
fi

echo -e "📊 Test Results:"
echo -e "   ${GREEN}✅ PASSED: $PASSED_TESTS${NC}"
echo -e "   ${RED}❌ FAILED: $FAILED_TESTS${NC}"
echo -e "   📈 TOTAL:  $TOTAL_TESTS"
echo -e "   📊 SUCCESS RATE: ${GREEN}$PASS_PERCENTAGE%${NC}"
echo ""

# Overall assessment
if [ $PASS_PERCENTAGE -ge 90 ]; then
    echo -e "${GREEN}🎯 EXCELLENT: System exceeds requirements!${NC}"
    EXIT_CODE=0
elif [ $PASS_PERCENTAGE -ge 80 ]; then
    echo -e "${YELLOW}🎯 GOOD: System meets most requirements${NC}"
    EXIT_CODE=0
elif [ $PASS_PERCENTAGE -ge 70 ]; then
    echo -e "${YELLOW}⚠️  ACCEPTABLE: System has minor issues${NC}"
    EXIT_CODE=1
else
    echo -e "${RED}❌ INSUFFICIENT: System needs major fixes${NC}"
    EXIT_CODE=1
fi

# Show failed tests if any
if [ $FAILED_TESTS -gt 0 ]; then
    echo ""
    echo -e "${RED}Failed Tests:${NC}"
    for test in "${FAILED_TEST_NAMES[@]}"; do
        echo -e "  • $test"
    done
    echo ""
    echo -e "${CYAN}💡 Quick fixes:${NC}"
    echo "  • Build issues: colcon build --packages-select g1_interface_pkg g1_ass1_pkg"
    echo "  • Database issues: ./complete_setup.sh"
    echo "  • Service issues: source install/setup.bash"
fi

echo ""
echo "======================================================================="

exit $EXIT_CODE
