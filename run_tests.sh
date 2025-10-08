#!/bin/bash

# 🧪 ROS2 Grade Calculator - Unit Test Runner
# Comprehensive test suite voor het complete systeem

# Colors
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
echo "🧪 ROS2 Grade Calculator - Unit Test Suite"
echo "======================================================================="
echo ""

# Test configuration
RUN_UNIT_TESTS=true
RUN_INTEGRATION_TESTS=false  # Requires running system
RUN_DATABASE_TESTS=true
VERBOSE_OUTPUT=false

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --integration)
            RUN_INTEGRATION_TESTS=true
            shift
            ;;
        --no-database)
            RUN_DATABASE_TESTS=false
            shift
            ;;
        --verbose|-v)
            VERBOSE_OUTPUT=true
            shift
            ;;
        --help|-h)
            echo "Usage: $0 [options]"
            echo ""
            echo "Options:"
            echo "  --integration    Run integration tests (requires system to be running)"
            echo "  --no-database    Skip database tests"
            echo "  --verbose, -v    Verbose test output"
            echo "  --help, -h       Show this help message"
            echo ""
            echo "Test Categories:"
            echo "  Unit Tests       - Individual component tests (always run)"
            echo "  Database Tests   - Database operation tests (run by default)"
            echo "  Integration Tests- Full system tests (opt-in with --integration)"
            echo ""
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            echo "Use --help for usage information"
            exit 1
            ;;
    esac
done

# Helper functions
log_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

log_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

log_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

log_error() {
    echo -e "${RED}❌ $1${NC}"
}

log_test_category() {
    echo -e "${MAGENTA}🔬 $1${NC}"
    echo "─────────────────────────────────────────────"
}

# Test counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
SKIPPED_TESTS=0

run_test() {
    local test_name="$1"
    local test_command="$2"
    local required="$3"  # "true" or "false"
    
    echo -e "${CYAN}Running: $test_name${NC}"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    if [ "$VERBOSE_OUTPUT" = true ]; then
        echo "Command: $test_command"
        echo ""
    fi
    
    # Run the test
    if [ "$VERBOSE_OUTPUT" = true ]; then
        eval "$test_command"
        test_result=$?
    else
        eval "$test_command" >/dev/null 2>&1
        test_result=$?
    fi
    
    if [ $test_result -eq 0 ]; then
        log_success "$test_name: PASSED"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        if [ "$required" = "true" ]; then
            log_error "$test_name: FAILED"
            FAILED_TESTS=$((FAILED_TESTS + 1))
        else
            log_warning "$test_name: SKIPPED (optional dependency missing)"
            SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
        fi
    fi
    
    echo ""
}

# =============================================================================
# 1. ENVIRONMENT VERIFICATION
# =============================================================================
log_test_category "Environment Verification"

# Check ROS2 environment
if [ -f "/opt/ros/jazzy/setup.bash" ]; then
    source /opt/ros/jazzy/setup.bash
    log_success "ROS2 Jazzy environment sourced"
elif [ -f "/opt/ros/humble/setup.bash" ]; then
    source /opt/ros/humble/setup.bash
    log_success "ROS2 Humble environment sourced"
else
    log_error "No ROS2 installation found!"
    exit 1
fi

# Check workspace build
if [ -f "install/setup.bash" ]; then
    source install/setup.bash
    log_success "Workspace environment sourced"
else
    log_error "Workspace not built! Run: colcon build --packages-select g1_interface_pkg g1_ass1_pkg"
    exit 1
fi

# Check if tests are built
if [ ! -d "install/g1_ass1_pkg/lib/g1_ass1_pkg" ]; then
    log_warning "Test executables not found. Building tests..."
    colcon build --packages-select g1_ass1_pkg --cmake-args -DBUILD_TESTING=ON
    if [ $? -ne 0 ]; then
        log_error "Failed to build tests!"
        exit 1
    fi
    source install/setup.bash
fi

echo ""

# =============================================================================
# 2. UNIT TESTS
# =============================================================================
if [ "$RUN_UNIT_TESTS" = true ]; then
    log_test_category "Unit Tests"
    
    # Test 1: Cijfer Calculator Service Tests
    if [ -f "install/g1_ass1_pkg/lib/g1_ass1_pkg/test_cijfer_calculator" ]; then
        run_test "Cijfer Calculator Tests" \
                "timeout 30s install/g1_ass1_pkg/lib/g1_ass1_pkg/test_cijfer_calculator" \
                "true"
    else
        log_warning "Cijfer calculator test executable not found"
        SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
    fi
    
    # Test 2: Topic Communication Tests
    if [ -f "install/g1_ass1_pkg/lib/g1_ass1_pkg/test_topic_communication" ]; then
        run_test "Topic Communication Tests" \
                "timeout 30s install/g1_ass1_pkg/lib/g1_ass1_pkg/test_topic_communication" \
                "true"
    else
        log_warning "Topic communication test executable not found"
        SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
    fi
    
    # Test 3: Herkansing Action Tests
    if [ -f "install/g1_ass1_pkg/lib/g1_ass1_pkg/test_herkansing_action" ]; then
        run_test "Herkansing Action Tests" \
                "timeout 60s install/g1_ass1_pkg/lib/g1_ass1_pkg/test_herkansing_action" \
                "true"
    else
        log_warning "Herkansing action test executable not found"
        SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
    fi
else
    log_warning "Unit tests skipped"
fi

# =============================================================================
# 3. DATABASE TESTS
# =============================================================================
if [ "$RUN_DATABASE_TESTS" = true ]; then
    log_test_category "Database Tests"
    
    # Check PostgreSQL availability
    if systemctl is-active --quiet postgresql 2>/dev/null; then
        log_success "PostgreSQL is running"
        
        # Test database connectivity first
        if psql -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
            log_success "Database connection available"
            
            # Run database tests
            if [ -f "install/g1_ass1_pkg/lib/g1_ass1_pkg/test_database" ]; then
                run_test "Database Operation Tests" \
                        "timeout 60s install/g1_ass1_pkg/lib/g1_ass1_pkg/test_database" \
                        "false"
            else
                log_warning "Database test executable not found"
                SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
            fi
        else
            log_warning "Cannot connect to student_grades database"
            log_info "Run './complete_setup.sh' to setup database"
            SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
        fi
    else
        log_warning "PostgreSQL is not running - database tests skipped"
        log_info "Start PostgreSQL: sudo systemctl start postgresql"
        SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
    fi
else
    log_warning "Database tests skipped (--no-database flag)"
fi

# =============================================================================
# 4. INTEGRATION TESTS
# =============================================================================
if [ "$RUN_INTEGRATION_TESTS" = true ]; then
    log_test_category "Integration Tests"
    
    # Check if system is running
    if ros2 node list 2>/dev/null | grep -q "tentamen_result_generator\|cijfer_calculator"; then
        log_success "ROS2 system appears to be running"
        
        if [ -f "install/g1_ass1_pkg/lib/g1_ass1_pkg/test_system_integration" ]; then
            run_test "System Integration Tests" \
                    "timeout 120s install/g1_ass1_pkg/lib/g1_ass1_pkg/test_system_integration" \
                    "false"
        else
            log_warning "Integration test executable not found"
            SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
        fi
    else
        log_warning "ROS2 system not running - integration tests skipped"
        log_info "Start system with: ros2 launch g1_ass1_pkg system.launch.xml"
        SKIPPED_TESTS=$((SKIPPED_TESTS + 1))
    fi
else
    log_warning "Integration tests skipped (use --integration to enable)"
fi

# =============================================================================
# 5. TEST SUMMARY
# =============================================================================
echo ""
echo "======================================================================="
echo "🏁 TEST SUMMARY"
echo "======================================================================="
echo ""

# Calculate percentages
if [ $TOTAL_TESTS -gt 0 ]; then
    PASS_PERCENTAGE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
else
    PASS_PERCENTAGE=0
fi

echo -e "📊 Test Results:"
echo -e "   ${GREEN}✅ PASSED:  $PASSED_TESTS${NC}"
echo -e "   ${RED}❌ FAILED:  $FAILED_TESTS${NC}"
echo -e "   ${YELLOW}⏭️  SKIPPED: $SKIPPED_TESTS${NC}"
echo -e "   📈 TOTAL:   $TOTAL_TESTS"
echo -e "   📊 SUCCESS RATE: ${GREEN}$PASS_PERCENTAGE%${NC}"
echo ""

# Overall assessment
if [ $FAILED_TESTS -eq 0 ] && [ $PASSED_TESTS -gt 0 ]; then
    log_success "🎯 EXCELLENT: All available tests passed!"
    EXIT_CODE=0
elif [ $FAILED_TESTS -eq 0 ]; then
    log_warning "⚠️  NO TESTS RUN: Check test availability and dependencies"
    EXIT_CODE=1
else
    log_error "❌ FAILED: $FAILED_TESTS test(s) failed"
    EXIT_CODE=1
fi

echo ""
echo "💡 Quick Tips:"
echo "   • Build tests: colcon build --cmake-args -DBUILD_TESTING=ON"
echo "   • Verbose output: $0 --verbose"
echo "   • Integration tests: $0 --integration (requires running system)"
echo "   • Database tests: Ensure PostgreSQL is running and configured"
echo ""

if [ $RUN_INTEGRATION_TESTS = false ]; then
    echo "🔄 To run comprehensive testing:"
    echo "   1. Start system: ros2 launch g1_ass1_pkg system.launch.xml"
    echo "   2. In new terminal: $0 --integration"
fi

echo ""
echo "======================================================================="

exit $EXIT_CODE
