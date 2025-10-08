#!/bin/bash

# 🔨 Build Script voor Unit Tests - ROS2 Grade Calculator System

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "======================================================================="
echo "🔨 ROS2 Grade Calculator - Build with Unit Tests"
echo "======================================================================="
echo ""

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

# Parse command line arguments
CLEAN_BUILD=false
BUILD_TESTS=true
VERBOSE=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --clean)
            CLEAN_BUILD=true
            shift
            ;;
        --no-tests)
            BUILD_TESTS=false
            shift
            ;;
        --verbose|-v)
            VERBOSE=true
            shift
            ;;
        --help|-h)
            echo "Usage: $0 [options]"
            echo ""
            echo "Options:"
            echo "  --clean      Clean build (remove build/install directories)"
            echo "  --no-tests   Build without unit tests"
            echo "  --verbose    Verbose build output"
            echo "  --help       Show this help message"
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

# =============================================================================
# 1. ENVIRONMENT SETUP
# =============================================================================
log_info "Setting up build environment..."

# Check ROS2 environment
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

# Check dependencies
log_info "Checking build dependencies..."

# Check colcon
if ! command -v colcon &> /dev/null; then
    log_error "colcon not found! Install with: pip3 install colcon-common-extensions"
    exit 1
fi

# Check if we have gtest (for unit tests)
if [ "$BUILD_TESTS" = true ]; then
    if ! pkg-config --exists gtest; then
        log_warning "GTest not found. Installing..."
        sudo apt update
        sudo apt install -y libgtest-dev cmake
        
        # Build gtest if needed
        if [ ! -f /usr/lib/libgtest.a ]; then
            log_info "Building GTest from source..."
            cd /usr/src/gtest
            sudo cmake CMakeLists.txt
            sudo make
            sudo cp lib/*.a /usr/lib/
            cd "$SCRIPT_DIR"
        fi
        log_success "GTest installed"
    else
        log_success "GTest found"
    fi
fi

# Check PostgreSQL development headers
if ! pkg-config --exists libpqxx; then
    log_warning "libpqxx development headers not found"
    log_info "Installing PostgreSQL development packages..."
    sudo apt update
    sudo apt install -y libpqxx-dev libpq-dev
    log_success "PostgreSQL development packages installed"
fi

# =============================================================================
# 2. CLEAN BUILD (if requested)
# =============================================================================
if [ "$CLEAN_BUILD" = true ]; then
    log_info "Performing clean build..."
    
    if [ -d "build" ]; then
        rm -rf build
        log_success "Removed build directory"
    fi
    
    if [ -d "install" ]; then
        rm -rf install
        log_success "Removed install directory"
    fi
    
    if [ -d "log" ]; then
        rm -rf log
        log_success "Removed log directory"
    fi
fi

# =============================================================================
# 3. BUILD CONFIGURATION
# =============================================================================
log_info "Configuring build..."

# Build arguments
BUILD_ARGS=""

if [ "$BUILD_TESTS" = true ]; then
    BUILD_ARGS="$BUILD_ARGS -DBUILD_TESTING=ON"
    log_info "Unit tests ENABLED"
else
    BUILD_ARGS="$BUILD_ARGS -DBUILD_TESTING=OFF"
    log_info "Unit tests DISABLED"
fi

if [ "$VERBOSE" = true ]; then
    BUILD_ARGS="$BUILD_ARGS --event-handlers console_direct+"
    log_info "Verbose output ENABLED"
fi

# =============================================================================
# 4. BUILD PROCESS
# =============================================================================
echo ""
log_info "Starting build process..."

# Step 1: Build interface package first
log_info "Building g1_interface_pkg (ROS2 interfaces)..."
colcon build --packages-select g1_interface_pkg --cmake-args $BUILD_ARGS

if [ $? -ne 0 ]; then
    log_error "Interface package build FAILED!"
    exit 1
fi
log_success "Interface package build completed"

# Source the interface package for main package build
if [ -f "install/setup.bash" ]; then
    source install/setup.bash
    log_info "Sourced interface package"
fi

# Step 2: Build main package with tests
log_info "Building g1_ass1_pkg (main application + tests)..."
colcon build --packages-select g1_ass1_pkg --cmake-args $BUILD_ARGS

if [ $? -ne 0 ]; then
    log_error "Main package build FAILED!"
    exit 1
fi
log_success "Main package build completed"

# =============================================================================
# 5. BUILD VERIFICATION
# =============================================================================
log_info "Verifying build results..."

# Check executables
EXECUTABLES=(
    "tentamen_result_generator"
    "cijfer_calculator" 
    "final_cijfer_determinator"
    "herkansing_scheduler"
    "herkansing_cijfer_determinator"
)

missing_executables=0
for exe in "${EXECUTABLES[@]}"; do
    if [ -f "install/g1_ass1_pkg/lib/g1_ass1_pkg/$exe" ]; then
        log_success "Executable: $exe"
    else
        log_error "Missing executable: $exe"
        missing_executables=$((missing_executables + 1))
    fi
done

# Check test executables (if tests were built)
if [ "$BUILD_TESTS" = true ]; then
    TEST_EXECUTABLES=(
        "test_cijfer_calculator"
        "test_topic_communication" 
        "test_herkansing_action"
        "test_database"
        "test_system_integration"
    )
    
    missing_tests=0
    for test_exe in "${TEST_EXECUTABLES[@]}"; do
        if [ -f "install/g1_ass1_pkg/lib/g1_ass1_pkg/$test_exe" ]; then
            log_success "Test executable: $test_exe"
        else
            log_warning "Missing test executable: $test_exe"
            missing_tests=$((missing_tests + 1))
        fi
    done
    
    if [ $missing_tests -eq 0 ]; then
        log_success "All test executables built successfully"
    else
        log_warning "$missing_tests test executables missing (may be due to missing dependencies)"
    fi
fi

# Check launch file
if [ -f "install/g1_ass1_pkg/share/g1_ass1_pkg/launch/system.launch.xml" ]; then
    log_success "Launch file: system.launch.xml"
else
    log_error "Missing launch file: system.launch.xml"
    missing_executables=$((missing_executables + 1))
fi

# =============================================================================
# 6. BUILD SUMMARY
# =============================================================================
echo ""
echo "======================================================================="
echo "🏁 BUILD SUMMARY"
echo "======================================================================="

if [ $missing_executables -eq 0 ]; then
    log_success "🎯 BUILD SUCCESSFUL! All components built correctly."
    
    echo ""
    echo "📦 What was built:"
    echo "   • 5 ROS2 node executables"
    echo "   • Launch system configuration"
    if [ "$BUILD_TESTS" = true ]; then
        echo "   • $((${#TEST_EXECUTABLES[@]} - missing_tests)) unit test executables"
    fi
    
    echo ""
    echo "🚀 Next steps:"
    echo "   • Source environment: source install/setup.bash"
    echo "   • Start system: ros2 launch g1_ass1_pkg system.launch.xml"
    if [ "$BUILD_TESTS" = true ]; then
        echo "   • Run tests: ./run_tests.sh"
    fi
    
    EXIT_CODE=0
else
    log_error "❌ BUILD ISSUES: $missing_executables critical components missing"
    
    echo ""
    echo "🔧 Troubleshooting:"
    echo "   • Check build logs: colcon build --packages-select g1_ass1_pkg"
    echo "   • Clean build: $0 --clean"
    echo "   • Check dependencies: rosdep install --from-paths src --ignore-src -r -y"
    
    EXIT_CODE=1
fi

# Final workspace sourcing reminder
echo ""
echo "💡 Remember to source the workspace:"
echo "   source install/setup.bash"

# Test running instructions
if [ "$BUILD_TESTS" = true ] && [ $missing_tests -lt ${#TEST_EXECUTABLES[@]} ]; then
    echo ""
    echo "🧪 Test execution:"
    echo "   ./run_tests.sh              # Run all available tests"
    echo "   ./run_tests.sh --verbose    # Verbose test output"
    echo "   ./run_tests.sh --integration# Run with system integration tests"
fi

echo ""
echo "======================================================================="

exit $EXIT_CODE
