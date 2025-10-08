#!/bin/bash

# 🧪 Unit Test Quick Runner - Direct Build Execution
# For testing the unit tests directly from build directory

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "======================================================================="
echo "🧪 ROS2 Grade Calculator - Quick Unit Test Run"
echo "======================================================================="
echo ""

# Helper functions
log_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

log_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

log_error() {
    echo -e "${RED}❌ $1${NC}"
}

# Set up environment
log_info "Setting up ROS2 environment..."
export ROS_DOMAIN_ID=42

if [ -f "/opt/ros/jazzy/setup.bash" ]; then
    source /opt/ros/jazzy/setup.bash
    log_success "ROS2 Jazzy environment loaded"
elif [ -f "/opt/ros/humble/setup.bash" ]; then
    source /opt/ros/humble/setup.bash
    log_success "ROS2 Humble environment loaded"
else
    log_error "No ROS2 installation found!"
    exit 1
fi

# Check if tests exist in build directory
BUILD_DIR="$SCRIPT_DIR/build/g1_ass1_pkg"
if [ ! -d "$BUILD_DIR" ]; then
    log_error "Build directory not found: $BUILD_DIR"
    log_info "Run: colcon build --cmake-args -DBUILD_TESTING=ON"
    exit 1
fi

echo ""
log_info "Available tests in build directory:"

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Test executables
TESTS=(
    "test_topic_communication:Topic Communication Tests"
    "test_database:Database Tests" 
    "test_cijfer_calculator:Cijfer Calculator Tests"
    "test_herkansing_action:Herkansing Action Tests"
    "test_system_integration:System Integration Tests"
)

for test_entry in "${TESTS[@]}"; do
    IFS=':' read -r test_exe test_name <<< "$test_entry"
    test_path="$BUILD_DIR/$test_exe"
    
    if [ -f "$test_path" ] && [ -x "$test_path" ]; then
        echo ""
        log_info "Running: $test_name"
        echo "─────────────────────────────────────────────"
        
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        
        # Run test with timeout
        if timeout 30s "$test_path"; then
            log_success "$test_name: PASSED"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            result=$?
            if [ $result -eq 124 ]; then
                log_error "$test_name: TIMEOUT (30s)"
            else
                log_error "$test_name: FAILED (exit code: $result)"
            fi
            FAILED_TESTS=$((FAILED_TESTS + 1))
        fi
    else
        echo "⏭️  Skipping $test_name (executable not found: $test_exe)"
    fi
done

# Summary
echo ""
echo "======================================================================="
echo "🏁 QUICK TEST SUMMARY"
echo "======================================================================="

if [ $TOTAL_TESTS -gt 0 ]; then
    PASS_PERCENTAGE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
else
    PASS_PERCENTAGE=0
fi

echo -e "📊 Test Results:"
echo -e "   ${GREEN}✅ PASSED:  $PASSED_TESTS${NC}"
echo -e "   ${RED}❌ FAILED:  $FAILED_TESTS${NC}"
echo -e "   📈 TOTAL:   $TOTAL_TESTS"
echo -e "   📊 SUCCESS RATE: ${GREEN}$PASS_PERCENTAGE%${NC}"
echo ""

if [ $FAILED_TESTS -eq 0 ] && [ $PASSED_TESTS -gt 0 ]; then
    log_success "🎯 All tests passed!"
    exit 0
elif [ $TOTAL_TESTS -eq 0 ]; then
    log_error "No tests found. Build tests with: colcon build --cmake-args -DBUILD_TESTING=ON"
    exit 1
else
    log_error "$FAILED_TESTS test(s) failed"
    exit 1
fi
