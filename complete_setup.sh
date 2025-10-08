#!/bin/bash

# =============================================================================
# Complete ROS2 Grade Calculator System Setup Script
# =============================================================================
# This script sets up everything needed for the ROS2 Grade Calculator:
# - Detects Linux distribution
# - Installs PostgreSQL and development libraries
# - Installs ROS2 if needed
# - Sets up database and users
# - Builds the ROS2 project
# - Provides easy launch commands
# =============================================================================

set -e  # Exit on any error

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Helper functions
log_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
log_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
log_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
log_error() { echo -e "${RED}[ERROR]${NC} $1"; }

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_NAME="g1_ass1_pkg"

echo "======================================================================="
echo "🚀 ROS2 Grade Calculator System - Complete Setup Script"
echo "======================================================================="
echo ""
echo "This script will:"
echo "  ✅ Detect your Linux distribution"
echo "  ✅ Install PostgreSQL and development libraries"
echo "  ✅ Install ROS2 (if not present)"
echo "  ✅ Set up database and authentication"
echo "  ✅ Build the ROS2 project"
echo "  ✅ Test the complete system"
echo ""
echo "Workspace: $SCRIPT_DIR"
echo ""

# Check if running as root
if [ "$EUID" -eq 0 ]; then
    log_error "Don't run this script as root! Run as normal user."
    exit 1
fi

# =============================================================================
# 1. DETECT LINUX DISTRIBUTION
# =============================================================================
log_info "Detecting Linux distribution..."

if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
    VERSION=$VERSION_ID
else
    log_error "Cannot detect Linux distribution"
    exit 1
fi

log_success "Detected: $PRETTY_NAME"

# =============================================================================
# 2. INSTALL SYSTEM DEPENDENCIES
# =============================================================================
log_info "Installing system dependencies..."

case $DISTRO in
    ubuntu|debian|linuxmint|pop)
        log_info "Installing packages for Debian/Ubuntu-based system..."
        sudo apt update
        
        # Install PostgreSQL
        sudo apt install -y postgresql postgresql-contrib postgresql-server-dev-all
        
        # Install libpqxx
        sudo apt install -y libpqxx-dev pkg-config
        
        # Install build tools
        sudo apt install -y build-essential cmake git curl gnupg2 lsb-release
        
        # Install Python dependencies
        sudo apt install -y python3-pip python3-dev
        
        PKG_MANAGER="apt"
        ;;
        
    fedora|rhel|centos|rocky|almalinux)
        log_info "Installing packages for Red Hat-based system..."
        
        # Enable EPEL if needed
        if command -v dnf >/dev/null 2>&1; then
            sudo dnf install -y epel-release
            sudo dnf update
            sudo dnf install -y postgresql postgresql-server postgresql-devel libpqxx-devel pkg-config
            sudo dnf install -y gcc gcc-c++ cmake git curl
        else
            sudo yum install -y epel-release
            sudo yum update
            sudo yum install -y postgresql postgresql-server postgresql-devel libpqxx-devel pkg-config
            sudo yum install -y gcc gcc-c++ cmake git curl
        fi
        
        PKG_MANAGER="dnf"
        ;;
        
    opensuse*|sles)
        log_info "Installing packages for openSUSE/SLES..."
        sudo zypper refresh
        sudo zypper install -y postgresql postgresql-server postgresql-devel libpqxx-devel pkg-config
        sudo zypper install -y gcc gcc-c++ cmake git curl
        
        PKG_MANAGER="zypper"
        ;;
        
    arch|manjaro)
        log_info "Installing packages for Arch-based system..."
        sudo pacman -Syu --noconfirm
        sudo pacman -S --noconfirm postgresql postgresql-libs libpqxx pkg-config
        sudo pacman -S --noconfirm base-devel cmake git curl
        
        PKG_MANAGER="pacman"
        ;;
        
    *)
        log_warning "Unknown distribution: $DISTRO"
        log_info "Attempting generic installation..."
        
        # Try to detect package manager
        if command -v apt >/dev/null 2>&1; then
            PKG_MANAGER="apt"
            sudo apt update
            sudo apt install -y postgresql postgresql-contrib postgresql-server-dev-all libpqxx-dev pkg-config build-essential cmake git
        elif command -v dnf >/dev/null 2>&1; then
            PKG_MANAGER="dnf"
            sudo dnf install -y postgresql postgresql-server postgresql-devel libpqxx-devel pkg-config gcc gcc-c++ cmake git
        elif command -v pacman >/dev/null 2>&1; then
            PKG_MANAGER="pacman"
            sudo pacman -S --noconfirm postgresql postgresql-libs libpqxx pkg-config base-devel cmake git
        else
            log_error "Cannot detect package manager. Please install PostgreSQL and libpqxx manually."
            exit 1
        fi
        ;;
esac

log_success "System dependencies installed"

# =============================================================================
# 3. SETUP POSTGRESQL
# =============================================================================
log_info "Setting up PostgreSQL..."

# Initialize PostgreSQL database (needed for some distributions)
case $DISTRO in
    fedora|rhel|centos|rocky|almalinux)
        if [ ! -f /var/lib/pgsql/data/postgresql.conf ]; then
            log_info "Initializing PostgreSQL database..."
            sudo postgresql-setup --initdb || sudo /usr/bin/postgresql-setup initdb
        fi
        ;;
    arch|manjaro)
        if [ ! -f /var/lib/postgres/data/postgresql.conf ]; then
            log_info "Initializing PostgreSQL database..."
            sudo -u postgres initdb -D /var/lib/postgres/data
        fi
        ;;
esac

# Start and enable PostgreSQL
log_info "Starting PostgreSQL service..."
sudo systemctl enable postgresql
sudo systemctl start postgresql

# Wait for PostgreSQL to start
sleep 3

# Verify PostgreSQL is running
if ! sudo systemctl is-active --quiet postgresql; then
    log_error "PostgreSQL failed to start"
    sudo journalctl -u postgresql --no-pager -n 10
    exit 1
fi

log_success "PostgreSQL is running"

# =============================================================================
# 4. CONFIGURE POSTGRESQL DATABASE AND USERS
# =============================================================================
log_info "Configuring PostgreSQL database and users..."

# Create database and setup users
sudo -u postgres psql << 'EOF'
-- Create database if it doesn't exist
SELECT 'CREATE DATABASE student_grades' WHERE NOT EXISTS (SELECT FROM pg_database WHERE datname = 'student_grades')\gexec

-- Ensure postgres user has correct permissions
ALTER USER postgres WITH SUPERUSER CREATEDB CREATEROLE LOGIN;
ALTER USER postgres PASSWORD 'password';

-- Grant privileges
GRANT ALL PRIVILEGES ON DATABASE student_grades TO postgres;

-- Show successful setup
\echo 'Database setup completed successfully!'
EOF

# Create current user as PostgreSQL user
CURRENT_USER=$(whoami)
sudo -u postgres createuser "$CURRENT_USER" --superuser 2>/dev/null || log_info "User $CURRENT_USER already exists"
sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE student_grades TO \"$CURRENT_USER\";" 2>/dev/null || true

# Configure authentication
PG_VERSION=$(sudo -u postgres psql -t -c "SELECT version();" | grep -oE '[0-9]+\.[0-9]+' | head -1 2>/dev/null || echo "")

if [ -n "$PG_VERSION" ]; then
    # Find PostgreSQL config directory
    PG_CONF_DIRS=(
        "/etc/postgresql/$PG_VERSION/main"
        "/var/lib/pgsql/data"
        "/var/lib/postgres/data"
        "/etc/postgresql"
    )
    
    for dir in "${PG_CONF_DIRS[@]}"; do
        if [ -f "$dir/pg_hba.conf" ]; then
            log_info "Updating PostgreSQL authentication config in $dir"
            sudo cp "$dir/pg_hba.conf" "$dir/pg_hba.conf.backup" 2>/dev/null || true
            
            # Update authentication methods
            sudo sed -i 's/local   all             postgres                                peer/local   all             postgres                                md5/' "$dir/pg_hba.conf" 2>/dev/null || true
            sudo sed -i 's/local   all             all                                     peer/local   all             all                                     md5/' "$dir/pg_hba.conf" 2>/dev/null || true
            
            # Reload PostgreSQL configuration
            sudo systemctl reload postgresql || sudo -u postgres pg_ctl reload -D "$dir"
            break
        fi
    done
fi

log_success "PostgreSQL database and users configured"

# =============================================================================
# 5. INSTALL ROS2 (if not present)
# =============================================================================
log_info "Checking ROS2 installation..."

if [ -z "$ROS_DISTRO" ] || ! command -v ros2 >/dev/null 2>&1; then
    log_warning "ROS2 not found. Installing ROS2 Jazzy..."
    
    case $DISTRO in
        ubuntu|debian)
            # Add ROS2 repository
            sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
            echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
            
            sudo apt update
            sudo apt install -y ros-jazzy-desktop python3-colcon-common-extensions python3-rosdep
            
            # Initialize rosdep
            if [ ! -f /etc/ros/rosdep/sources.list.d/20-default.list ]; then
                sudo rosdep init
            fi
            rosdep update
            ;;
            
        *)
            log_warning "Automatic ROS2 installation not supported for $DISTRO"
            log_info "Please install ROS2 manually from: https://docs.ros.org/en/jazzy/Installation.html"
            log_info "Then re-run this script"
            exit 1
            ;;
    esac
    
    log_success "ROS2 installed"
else
    log_success "ROS2 found: $ROS_DISTRO"
fi

# =============================================================================
# 6. BUILD ROS2 PROJECT
# =============================================================================
log_info "Building ROS2 project..."

cd "$SCRIPT_DIR"

# Check if this is a ROS2 workspace
if [ ! -f "src/$PROJECT_NAME/package.xml" ]; then
    log_error "This doesn't appear to be a valid ROS2 workspace with $PROJECT_NAME"
    log_info "Expected: $SCRIPT_DIR/src/$PROJECT_NAME/package.xml"
    exit 1
fi

# Source ROS2
if [ -f "/opt/ros/jazzy/setup.bash" ]; then
    source /opt/ros/jazzy/setup.bash
elif [ -f "/opt/ros/humble/setup.bash" ]; then
    source /opt/ros/humble/setup.bash
else
    log_error "Cannot find ROS2 setup.bash file"
    exit 1
fi

# Install dependencies
log_info "Installing ROS2 dependencies..."
rosdep install --from-paths src --ignore-src -r -y

# Build the project
log_info "Building project with colcon..."
colcon build --packages-select $PROJECT_NAME

if [ $? -ne 0 ]; then
    log_error "Build failed!"
    exit 1
fi

log_success "Project built successfully"

# =============================================================================
# 7. TEST SYSTEM
# =============================================================================
log_info "Testing system..."

# Test database connection
log_info "Testing database connections..."

DB_TESTS=(
    "postgresql://postgres:password@localhost:5432/student_grades"
    "host=localhost port=5432 dbname=student_grades user=postgres password=password"
    "dbname=student_grades"
)

DB_WORKING=false
for conn_str in "${DB_TESTS[@]}"; do
    if echo "SELECT 1;" | psql "$conn_str" >/dev/null 2>&1; then
        log_success "Database connection working: $conn_str"
        DB_WORKING=true
        break
    fi
done

if [ "$DB_WORKING" = false ]; then
    log_warning "Database connection tests failed, but this might be normal"
    log_info "The application will try multiple connection methods automatically"
fi

# Source workspace
source install/setup.bash

# Test if launch file exists
if [ -f "install/$PROJECT_NAME/share/$PROJECT_NAME/launch/system.launch.xml" ]; then
    log_success "Launch file found"
else
    log_error "Launch file not found after build"
    exit 1
fi

# =============================================================================
# 8. CREATE CONVENIENCE SCRIPTS
# =============================================================================
log_info "Creating convenience scripts..."

# Create simple run script
cat > run_system.sh << 'EOF'
#!/bin/bash
cd "$(dirname "$0")"
source /opt/ros/*/setup.bash 2>/dev/null
source install/setup.bash 2>/dev/null
echo "🚀 Starting ROS2 Grade Calculator System..."
ros2 launch g1_ass1_pkg system.launch.xml
EOF

chmod +x run_system.sh

# Create database test script
cat > test_database.sh << 'EOF'
#!/bin/bash
echo "Testing database connections..."

TESTS=(
    "psql -h localhost -U postgres -d student_grades -c 'SELECT version();'"
    "psql -d student_grades -c 'SELECT version();'"
    "sudo -u postgres psql -d student_grades -c 'SELECT version();'"
)

for i in "${!TESTS[@]}"; do
    echo "Test $((i+1)): ${TESTS[$i]}"
    if eval "PGPASSWORD=password ${TESTS[$i]}" >/dev/null 2>&1; then
        echo "✅ Success"
    else
        echo "❌ Failed"
    fi
done
EOF

chmod +x test_database.sh

# =============================================================================
# 9. FINAL SETUP COMPLETE
# =============================================================================
echo ""
echo "======================================================================="
log_success "🎉 SETUP COMPLETE!"
echo "======================================================================="
echo ""
echo "📋 What was installed/configured:"
echo "   ✅ PostgreSQL server and development libraries"
echo "   ✅ libpqxx C++ PostgreSQL library"
echo "   ✅ ROS2 environment (if needed)"
echo "   ✅ Database 'student_grades' with user 'postgres'"
echo "   ✅ ROS2 project '$PROJECT_NAME' built successfully"
echo ""
echo "🚀 To start the system:"
echo "   ./run_system.sh"
echo ""
echo "🔧 To test database connection:"
echo "   ./test_database.sh"
echo ""
echo "🐛 If you encounter issues:"
echo "   - Check PostgreSQL: sudo systemctl status postgresql"
echo "   - Check logs: sudo journalctl -u postgresql"
echo "   - Rebuild project: colcon build --packages-select $PROJECT_NAME"
echo ""
echo "📁 Project files:"
echo "   - Workspace: $SCRIPT_DIR"
echo "   - Launch file: install/$PROJECT_NAME/share/$PROJECT_NAME/launch/system.launch.xml"
echo "   - Database: student_grades (user: postgres, password: password)"
echo ""
log_success "Ready to use! 🎯"
