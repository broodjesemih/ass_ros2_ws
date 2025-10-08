#!/bin/bash

# =============================================================================
# ROS2 Grade Calculator - Test Script
# =============================================================================
# Simple test runner for the ROS2 Grade Calculator system
# =============================================================================

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
log_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
log_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
log_error() { echo -e "${RED}[ERROR]${NC} $1"; }

cd "$(dirname "$0")"

echo "Testing ROS2 Grade Calculator System..."
echo ""

# Quick system check
log_info "Checking system components..."

# Check PostgreSQL
if ! sudo systemctl is-active --quiet postgresql; then
    log_warning "PostgreSQL is not running. Starting it..."
    sudo systemctl start postgresql
    sleep 2
fi

# Check database connection
if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
    log_success "Database connection OK"
else
    log_error "Database connection failed"
    echo "Run './complete_setup.sh' to fix database issues"
    exit 1
fi

# Check ROS2 workspace
if [ ! -d "install" ]; then
    log_warning "ROS2 workspace not built. Building..."
    colcon build --packages-select g1_ass1_pkg
fi

# Source ROS2 environment
source /opt/ros/jazzy/setup.bash 2>/dev/null || source /opt/ros/humble/setup.bash 2>/dev/null || true
source install/setup.bash 2>/dev/null || true

# Run unit tests
log_info "Running unit tests..."
colcon test --packages-select g1_ass1_pkg

# Check test results
log_info "Test results:"
colcon test-result --verbose

echo ""
log_success "Test completed!"
echo ""
echo "Available commands:"
echo "  ./complete_setup.sh  - Full system setup"
echo "  ./run_system.sh     - Start the ROS2 system" 
echo "  ./check_db.sh       - Check database status"
echo "  ./test.sh           - Run this test script"
