#!/bin/bash

# ROS2 Grade Calculator System Launcher Script
# This script handles the complete startup sequence for the grade calculator system
# including PostgreSQL validation, ROS2 environment setup, and system launch

# Define color codes for formatted console output
RED='\033[0;31m'      # Red color for error messages
GREEN='\033[0;32m'    # Green color for success messages
YELLOW='\033[1;33m'   # Yellow color for warning messages
BLUE='\033[0;34m'     # Blue color for info messages
NC='\033[0m'          # No Color - resets to default

# Logging helper functions for consistent output formatting
log_info() { echo -e "${BLUE}[INFO]${NC} $1"; }        # Display informational messages
log_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }  # Display success confirmations
log_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; } # Display warning notifications
log_error() { echo -e "${RED}[ERROR]${NC} $1"; }       # Display error messages

# Change to the script's directory to ensure relative paths work correctly
# This allows the script to be run from any location while maintaining proper file access
cd "$(dirname "$0")"

echo "Starting ROS2 Grade Calculator System..."
echo ""

# STEP 1: PostgreSQL Service Validation and Startup
# The system requires PostgreSQL to be running for database operations
log_info "Checking PostgreSQL service..."
if ! sudo systemctl is-active --quiet postgresql; then
    # PostgreSQL is not running - attempt to start it
    log_warning "PostgreSQL is not running. Starting it..."
    sudo systemctl start postgresql
    sleep 3  # Wait 3 seconds for service to initialize
    
    # Verify that PostgreSQL started successfully
    if ! sudo systemctl is-active --quiet postgresql; then
        log_error "Failed to start PostgreSQL!"
        log_info "Try running: ./complete_setup.sh"
        exit 1  # Exit with error code if PostgreSQL cannot be started
    else
        log_success "PostgreSQL started successfully"
    fi
else
    # PostgreSQL is already running - no action needed
    log_success "PostgreSQL is running"
fi

# STEP 2: Database Connectivity Pre-flight Check
# Test multiple connection methods to ensure the C++ application can connect to PostgreSQL
# This matches the connection priority order used in database.cpp
log_info "Testing database connection..."
DB_TESTS=(
    # Method 1: TCP connection with password authentication (most common)
    "PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c 'SELECT 1;'"
    # Method 2: Unix socket connection with current system user
    "psql -d student_grades -c 'SELECT 1;'"
    # Method 3: Unix socket connection using postgres system user
    "sudo -u postgres psql -d student_grades -c 'SELECT 1;'"
)

# Flag to track if any connection method succeeds
DB_OK=false
# Iterate through connection methods until one succeeds
for test in "${DB_TESTS[@]}"; do
    # Execute connection test, suppressing output to avoid clutter
    if eval "$test" >/dev/null 2>&1; then
        log_success "Database connection verified"
        DB_OK=true
        break  # Stop testing once a working connection is found
    fi
done

# Handle case where no connection methods work
if [ "$DB_OK" = false ]; then
    log_warning "Database connection issues detected"
    log_info "The application will try multiple connection methods automatically"
    log_info "If problems persist, run: ./complete_setup.sh"
    # Note: We don't exit here because the C++ application has more comprehensive fallbacks
fi

# STEP 3: ROS2 Environment Setup
# Source the appropriate ROS2 distribution setup file to configure environment variables
log_info "Setting up ROS2 environment..."
if [ -f "/opt/ros/jazzy/setup.bash" ]; then
    # ROS2 Jazzy is installed - source its environment (preferred version)
    source /opt/ros/jazzy/setup.bash
elif [ -f "/opt/ros/humble/setup.bash" ]; then
    # Fallback to ROS2 Humble if Jazzy is not available
    source /opt/ros/humble/setup.bash
else
    # No compatible ROS2 installation found - cannot proceed
    log_error "Cannot find ROS2 setup file!"
    exit 1
fi

# STEP 4: Workspace Environment Setup  
# Source the local workspace setup to make our custom packages available
if [ -f "install/setup.bash" ]; then
    # Workspace has been built - source the install space
    source install/setup.bash
else
    # Workspace not built - provide clear instructions for user
    log_error "Workspace not built! Run: colcon build --packages-select g1_interface_pkg g1_ass1_pkg"
    exit 1
fi

echo ""
log_success "Environment ready! Launching system..."
echo ""
# STEP 5: System Launch Information Display
# Provide user with clear information about what nodes will be started
echo "Starting all ROS2 nodes for the Grade Calculator System:"
echo "  - tentamen_result_generator    (generates exam results for simulation)"
echo "  - cijfer_calculator           (calculates final grades with Wessel bonus)"
echo "  - final_cijfer_determinator   (orchestrates grade determination workflow)" 
echo "  - herkansing_scheduler        (monitors database and schedules retakes)"
echo "  - herkansing_cijfer_determinator (processes retake actions)"
echo ""
echo "Press Ctrl+C to stop all nodes"
echo ""

# STEP 6: Launch ROS2 System
# Execute the launch file which starts all nodes in the correct order
# The launch file handles node dependencies and communication setup
ros2 launch g1_ass1_pkg system.launch.xml

# STEP 7: Cleanup and Exit Message
# This executes after the launch file terminates (user pressed Ctrl+C)
echo ""
log_info "System stopped."
