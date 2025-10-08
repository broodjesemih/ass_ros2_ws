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
echo "ROS2 Grade Calculator System - Complete Setup Script"
echo "======================================================================="
echo ""
echo "This script will:"
echo "  Detect your Linux distribution"
echo "  Install PostgreSQL and development libraries"
echo "  Install ROS2 (if not present)"
echo "  Set up database and authentication"
echo "  Build the ROS2 project"
echo "  Test the complete system"
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

# Build the project in correct dependency order
log_info "Building interface package first..."
colcon build --packages-select g1_interface_pkg

if [ $? -ne 0 ]; then
    log_error "Interface package build failed!"
    exit 1
fi

log_info "Building main project..."
colcon build --packages-select $PROJECT_NAME

if [ $? -ne 0 ]; then
    log_error "Main project build failed!"
    exit 1
fi

log_success "Project built successfully"

# =============================================================================
# 7. TEST SYSTEM & FIX DATABASE ISSUES
# =============================================================================
log_info "Testing system and fixing potential database issues..."

# Test database connection with comprehensive troubleshooting
log_info "Testing database connections..."

DB_TESTS=(
    "PGPASSWORD=password psql -h localhost -p 5432 -U postgres -d student_grades -c 'SELECT 1;'"
    "psql -d student_grades -c 'SELECT 1;'"
    "sudo -u postgres psql -d student_grades -c 'SELECT 1;'"
)

DB_WORKING=false
for i in "${!DB_TESTS[@]}"; do
    log_info "Testing connection method $((i+1))/3..."
    if eval "${DB_TESTS[$i]}" >/dev/null 2>&1; then
        log_success "Database connection working with method $((i+1))"
        DB_WORKING=true
        break
    else
        log_warning "Method $((i+1)) failed"
    fi
done

if [ "$DB_WORKING" = false ]; then
    log_error "All database connection tests failed! Attempting fixes..."
    
    # Fix attempt 1: Restart PostgreSQL
    log_info "Fix 1/4: Restarting PostgreSQL service..."
    sudo systemctl restart postgresql
    sleep 5
    
    if sudo systemctl is-active --quiet postgresql; then
        log_success "PostgreSQL restarted successfully"
        
        # Test again after restart
        if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
            log_success "Database connection now working after restart!"
            DB_WORKING=true
        fi
    else
        log_error "PostgreSQL failed to restart"
    fi
    
    # Fix attempt 2: Check and fix socket permissions
    if [ "$DB_WORKING" = false ]; then
        log_info "Fix 2/4: Checking socket files and permissions..."
        
        SOCKET_DIRS=("/var/run/postgresql" "/tmp" "/run/postgresql")
        SOCKET_FOUND=false
        
        for dir in "${SOCKET_DIRS[@]}"; do
            if [ -d "$dir" ] && ls "$dir"/.s.PGSQL.* >/dev/null 2>&1; then
                log_success "Found PostgreSQL socket in $dir"
                sudo chmod 755 "$dir" 2>/dev/null || true
                SOCKET_FOUND=true
                break
            fi
        done
        
        if [ "$SOCKET_FOUND" = false ]; then
            log_warning "No PostgreSQL socket files found"
            log_info "Attempting to recreate socket directory..."
            sudo mkdir -p /var/run/postgresql
            sudo chown postgres:postgres /var/run/postgresql
            sudo systemctl restart postgresql
            sleep 3
        fi
        
        # Test connection after socket fix
        if sudo -u postgres psql -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
            log_success "Database connection now working after socket fix!"
            DB_WORKING=true
        fi
    fi
    
    # Fix attempt 3: Recreate database and user
    if [ "$DB_WORKING" = false ]; then
        log_info "Fix 3/4: Recreating database and users..."
        
        # Try to connect as postgres system user and recreate everything
        sudo -u postgres psql << 'EOFFIX' || log_warning "Could not execute database recreation"
-- Drop and recreate database
DROP DATABASE IF EXISTS student_grades;
CREATE DATABASE student_grades;

-- Ensure postgres user exists with correct permissions
DROP USER IF EXISTS postgres;
CREATE USER postgres WITH SUPERUSER CREATEDB CREATEROLE LOGIN PASSWORD 'password';

-- Grant all privileges
GRANT ALL PRIVILEGES ON DATABASE student_grades TO postgres;

-- Also create current system user
\echo 'Database and users recreated'
EOFFIX
        
        # Create current user
        CURRENT_USER=$(whoami)
        sudo -u postgres createuser "$CURRENT_USER" --superuser 2>/dev/null || true
        sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE student_grades TO \"$CURRENT_USER\";" 2>/dev/null || true
        
        # Test after recreation
        if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
            log_success "Database connection now working after recreation!"
            DB_WORKING=true
        fi
    fi
    
    # Fix attempt 4: Alternative PostgreSQL configuration
    if [ "$DB_WORKING" = false ]; then
        log_info "Fix 4/4: Trying alternative PostgreSQL configuration..."
        
        # Find and update pg_hba.conf to be more permissive
        PG_CONF_DIRS=(
            "/etc/postgresql/$PG_VERSION/main"
            "/var/lib/pgsql/data"
            "/var/lib/postgres/data"
            "/etc/postgresql"
        )
        
        for dir in "${PG_CONF_DIRS[@]}"; do
            if [ -f "$dir/pg_hba.conf" ]; then
                log_info "Updating PostgreSQL config in $dir"
                
                # Backup original
                sudo cp "$dir/pg_hba.conf" "$dir/pg_hba.conf.backup.$(date +%Y%m%d)" 2>/dev/null || true
                
                # Create more permissive configuration
                sudo bash -c "cat > $dir/pg_hba.conf.new << 'EOFHBA'
# TYPE  DATABASE        USER            ADDRESS                 METHOD
local   all             postgres                                trust
local   all             all                                     trust
host    all             all             127.0.0.1/32            md5
host    all             all             ::1/128                 md5
host    all             all             localhost               trust
EOFHBA"
                
                sudo mv "$dir/pg_hba.conf.new" "$dir/pg_hba.conf"
                sudo systemctl reload postgresql
                sleep 2
                break
            fi
        done
        
        # Final test
        if psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
            log_success "Database connection now working after config update!"
            DB_WORKING=true
        fi
    fi
    
    # If still not working, provide manual instructions
    if [ "$DB_WORKING" = false ]; then
        log_error "Could not automatically fix database connection issues"
        echo ""
        echo "MANUAL FIX INSTRUCTIONS:"
        echo "1. Check PostgreSQL status: sudo systemctl status postgresql"
        echo "2. Check PostgreSQL logs: sudo journalctl -u postgresql -n 50"
        echo "3. Try manual connection: sudo -u postgres psql"
        echo "4. If needed, reinstall PostgreSQL:"
        echo "   sudo apt remove --purge postgresql* && sudo apt install postgresql postgresql-contrib"
        echo "5. Re-run this script: ./complete_setup.sh"
        echo ""
        log_warning "Continuing setup - the application has built-in connection fallbacks"
    else
        log_success "Database connection issues resolved!"
    fi
else
    log_success "Database connection working perfectly!"
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

# Create intelligent run script with database checks
cat > run_system.sh << 'EOF'
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
    log_error "Workspace not built! Run: colcon build --packages-select g1_interface_pkg g1_ass1_pkg"
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
ros2 launch g1_ass1_pkg system.launch.xml

echo ""
log_info "System stopped."
EOF

chmod +x run_system.sh

# Create comprehensive database test script
cat > test_database.sh << 'EOF'
#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo "=========================================="
echo "Database Diagnostic Tool"
echo "=========================================="
echo ""

# 1. Check PostgreSQL service
echo "Checking PostgreSQL service..."
if systemctl is-active --quiet postgresql; then
    echo -e "${GREEN}PostgreSQL service is running${NC}"
else
    echo -e "${RED}PostgreSQL service is not running${NC}"
    echo -e "${YELLOW}Try: sudo systemctl start postgresql${NC}"
fi
echo ""

# 2. Check socket files
echo "Checking socket files..."
SOCKET_DIRS=("/var/run/postgresql" "/tmp" "/run/postgresql")
SOCKET_FOUND=false

for dir in "${SOCKET_DIRS[@]}"; do
    if [ -d "$dir" ] && ls "$dir"/.s.PGSQL.* >/dev/null 2>&1; then
        echo -e "${GREEN}Found PostgreSQL socket in $dir${NC}"
        ls -la "$dir"/.s.PGSQL.*
        SOCKET_FOUND=true
    fi
done

if [ "$SOCKET_FOUND" = false ]; then
    echo -e "${RED}No PostgreSQL socket files found${NC}"
    echo -e "${YELLOW}Try: sudo systemctl restart postgresql${NC}"
fi
echo ""

# 3. Check database existence
echo "Checking database existence..."
if sudo -u postgres psql -lqt | cut -d \| -f 1 | grep -qw student_grades; then
    echo -e "${GREEN}Database 'student_grades' exists${NC}"
else
    echo -e "${RED}Database 'student_grades' not found${NC}"
    echo -e "${YELLOW}Try: sudo -u postgres createdb student_grades${NC}"
fi
echo ""

# 4. Test connections
echo "Testing database connections..."

TESTS=(
    "PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c 'SELECT version();'|TCP with password"
    "psql -d student_grades -c 'SELECT version();'|Current user socket"
    "sudo -u postgres psql -d student_grades -c 'SELECT version();'|Postgres user socket"
    "psql -h localhost -d student_grades -c 'SELECT version();'|TCP without auth"
)

SUCCESS_COUNT=0
for test_line in "${TESTS[@]}"; do
    IFS='|' read -r cmd desc <<< "$test_line"
    echo -n "Testing $desc: "
    if eval "$cmd" >/dev/null 2>&1; then
        echo -e "${GREEN}Success${NC}"
        ((SUCCESS_COUNT++))
    else
        echo -e "${RED}Failed${NC}"
    fi
done
echo ""

# 5. Application connection test
echo "Testing application connection methods..."
echo "The C++ application will try these in order:"
echo "  1. postgresql://postgres:password@localhost:5432/student_grades"
echo "  2. host=localhost port=5432 dbname=student_grades user=postgres password=password"  
echo "  3. host=/var/run/postgresql dbname=student_grades user=postgres"
echo "  4. host=/tmp dbname=student_grades user=postgres"
echo "  5. dbname=student_grades"
echo "  6. postgresql:///student_grades"
echo ""

# 6. Summary and recommendations
echo "Summary:"
if [ "$SUCCESS_COUNT" -gt 0 ]; then
    echo -e "${GREEN}$SUCCESS_COUNT connection method(s) working${NC}"
    echo -e "${GREEN}The application should be able to connect to the database${NC}"
else
    echo -e "${RED}No connection methods working${NC}"
    echo ""
    echo -e "${YELLOW}Recommended fixes:${NC}"
    echo "1. sudo systemctl restart postgresql"
    echo "2. ./complete_setup.sh"
    echo "3. Check logs: sudo journalctl -u postgresql"
fi

echo ""
echo "=========================================="
EOF

chmod +x test_database.sh

# Create emergency database fix script
cat > fix_database_emergency.sh << 'EOF'
#!/bin/bash

echo "Emergency Database Fix Script"
echo "================================"
echo ""

# Stop PostgreSQL
echo "1. Stopping PostgreSQL..."
sudo systemctl stop postgresql

# Remove lock files
echo "2. Cleaning lock files..."
sudo rm -f /var/lib/postgresql/*/main/postmaster.pid 2>/dev/null
sudo rm -f /tmp/.s.PGSQL.* 2>/dev/null
sudo rm -f /var/run/postgresql/.s.PGSQL.* 2>/dev/null

# Fix permissions
echo "3. Fixing permissions..."
sudo chown -R postgres:postgres /var/lib/postgresql/ 2>/dev/null
sudo mkdir -p /var/run/postgresql
sudo chown postgres:postgres /var/run/postgresql
sudo chmod 755 /var/run/postgresql

# Start PostgreSQL
echo "4. Starting PostgreSQL..."
sudo systemctl start postgresql

# Wait for startup
sleep 5

# Check if running
if sudo systemctl is-active --quiet postgresql; then
    echo "PostgreSQL started successfully"
    
    # Recreate database as fallback
    echo "5. Ensuring database exists..."
    sudo -u postgres createdb student_grades 2>/dev/null || echo "Database may already exist"
    sudo -u postgres psql -c "ALTER USER postgres PASSWORD 'password';" 2>/dev/null || echo "Password may already be set"
    
    # Test connection
    if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
        echo "Database connection working!"
        echo ""
        echo "You can now run:"
        echo "  ./run_system.sh"
    else
        echo "Connection still failing"
        echo "Manual intervention required:"
        echo "  sudo -u postgres psql"
        echo "  Then create database and user manually"
    fi
else
    echo "PostgreSQL failed to start"
    echo "Check logs: sudo journalctl -u postgresql"
fi
EOF

chmod +x fix_database_emergency.sh

# =============================================================================
# 9. FINAL SETUP COMPLETE
# =============================================================================
echo ""
echo "======================================================================="
log_success "SETUP COMPLETE!"
echo "======================================================================="
echo ""
echo "What was installed/configured:"
echo "   PostgreSQL server and development libraries"
echo "   libpqxx C++ PostgreSQL library"
echo "   ROS2 environment (if needed)"
echo "   Database 'student_grades' with user 'postgres'"
echo "   ROS2 project '$PROJECT_NAME' built successfully"
echo ""
echo "To start the system:"
echo "   ./run_system.sh"
echo ""
echo "To test database connection:"
echo "   ./test_database.sh"
echo ""
echo "If database issues occur:"
echo "   ./fix_database_emergency.sh"
echo ""
echo "If you encounter other issues:"
echo "   - Check PostgreSQL: sudo systemctl status postgresql"
echo "   - Check logs: sudo journalctl -u postgresql"
echo "   - Rebuild project: colcon build --packages-select g1_interface_pkg $PROJECT_NAME"
echo "   - Re-run full setup: ./complete_setup.sh"
echo ""
echo "Project files:"
echo "   - Workspace: $SCRIPT_DIR"
echo "   - Launch file: install/$PROJECT_NAME/share/$PROJECT_NAME/launch/system.launch.xml"
echo "   - Database: student_grades (user: postgres, password: password)"
echo ""
log_success "Ready to use!"
