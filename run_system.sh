#!/bin/bash

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

echo "Starting ROS2 Grade Calculator System..."
echo ""

# Check PostgreSQL service
log_info "Checking PostgreSQL service..."
if ! sudo systemctl is-active --quiet postgresql; then
    log_warning "PostgreSQL is not running. Starting it..."
    sudo systemctl start postgresql
    sleep 3
    
    if ! sudo systemctl is-active --quiet postgresql; then
        log_error "Failed to start PostgreSQL!"
        log_info "Try running: ./complete_setup.sh"
        exit 1
    else
        log_success "PostgreSQL started successfully"
    fi
else
    log_success "PostgreSQL is running"
fi

# Quick database connectivity test
log_info "Testing database connection..."
DB_TESTS=(
    "PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c 'SELECT 1;'"
    "psql -d student_grades -c 'SELECT 1;'"
    "sudo -u postgres psql -d student_grades -c 'SELECT 1;'"
)

DB_OK=false
for test in "${DB_TESTS[@]}"; do
    if eval "$test" >/dev/null 2>&1; then
        log_success "Database connection verified"
        DB_OK=true
        break
    fi
done

if [ "$DB_OK" = false ]; then
    log_warning "Database connection issues detected"
    log_info "The application will try multiple connection methods automatically"
    log_info "If problems persist, run: ./complete_setup.sh"
fi

# Source ROS2 environment
log_info "Setting up ROS2 environment..."
if [ -f "/opt/ros/jazzy/setup.bash" ]; then
    source /opt/ros/jazzy/setup.bash
elif [ -f "/opt/ros/humble/setup.bash" ]; then
    source /opt/ros/humble/setup.bash
else
    log_error "Cannot find ROS2 setup file!"
    exit 1
fi

# Source workspace
if [ -f "install/setup.bash" ]; then
    source install/setup.bash
else
    log_error "Workspace not built! Run: colcon build --packages-select g1_25_assign1_interfaces_pkg g1_25_assign1_pkg"
    exit 1
fi

echo ""
log_success "Environment ready! Launching system..."
echo ""
echo "Starting all nodes:"
echo "  - tentamen_result_generator"
echo "  - cijfer_calculator"
echo "  - final_cijfer_determinator" 
echo "  - herkansing_scheduler"
echo "  - herkansing_cijfer_determinator"
echo ""
echo "Press Ctrl+C to stop all nodes"
echo ""

# Launch the system
ros2 launch g1_25_assign1_pkg system.launch.xml

echo ""
log_info "System stopped."
