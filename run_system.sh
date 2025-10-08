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

echo "🚀 Starting ROS2 Grade Calculator System..."
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

# Quick database connectivity test and auto-fix
log_info "Testing database connection..."
DB_TESTS=(
    "PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c 'SELECT 1;'"
    "psql -d student_grades -c 'SELECT 1;'"
    "sudo -u postgres psql -d student_grades -c 'SELECT 1;'"
)

DB_OK=false
for i in "${!DB_TESTS[@]}"; do
    if eval "${DB_TESTS[$i]}" >/dev/null 2>&1; then
        log_success "Database connection verified (method $((i+1)))"
        DB_OK=true
        break
    fi
done

if [ "$DB_OK" = false ]; then
    log_warning "Database connection issues detected - attempting auto-fix..."
    
        # Auto-fix attempt 1: Check if database exists and create user/password
    CURRENT_USER=$(whoami)
    log_info "Auto-fix 1/3: Setting up database and user ($CURRENT_USER)..."
    sudo -u postgres psql << EOFFIX 2>/dev/null || log_warning "Could not access postgres user directly"
-- Create database if it doesn't exist
CREATE DATABASE IF NOT EXISTS student_grades;
-- Ensure postgres user exists with correct password
ALTER USER postgres PASSWORD 'password';
-- Create current user as superuser
DO \$\$ 
BEGIN
    IF NOT EXISTS (SELECT FROM pg_catalog.pg_user WHERE usename = '$CURRENT_USER') THEN
        CREATE USER "$CURRENT_USER" WITH SUPERUSER;
    END IF;
END \$\$;
-- Grant privileges
GRANT ALL PRIVILEGES ON DATABASE student_grades TO postgres;
GRANT ALL PRIVILEGES ON DATABASE student_grades TO "$CURRENT_USER";
EOFFIX
    
    # Test after fix 1
    if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
        log_success "Auto-fix 1 successful!"
        DB_OK=true
    else
        # Auto-fix attempt 2: Fix authentication configuration
        log_info "Auto-fix 2/3: Fixing authentication configuration..."
        
        # Find PostgreSQL config directory
        PG_CONF_DIRS=(
            "/etc/postgresql/*/main"
            "/var/lib/pgsql/data"
            "/usr/local/var/postgres"
        )
        
        for pattern in "${PG_CONF_DIRS[@]}"; do
            for dir in $pattern; do
                if [ -f "$dir/pg_hba.conf" ]; then
                    log_info "Updating auth config in $dir"
                    
                    # Backup and update pg_hba.conf
                    sudo cp "$dir/pg_hba.conf" "$dir/pg_hba.conf.backup.$(date +%s)" 2>/dev/null
                    
                    # Create new config with trust authentication
                    sudo tee "$dir/pg_hba.conf.new" > /dev/null << 'EOFHBA'
# TYPE  DATABASE        USER            ADDRESS                 METHOD
local   all             postgres                                trust
local   all             all                                     trust  
host    all             all             127.0.0.1/32            md5
host    all             all             ::1/128                 md5
host    all             all             localhost               trust
EOFHBA
                    
                    sudo mv "$dir/pg_hba.conf.new" "$dir/pg_hba.conf"
                    sudo systemctl reload postgresql
                    sleep 2
                    break 2
                fi
            done
        done
        
        # Test after fix 2
        if psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
            log_success "Auto-fix 2 successful!"
            DB_OK=true
        else
            # Auto-fix attempt 3: Emergency database reset
            log_info "Auto-fix 3/3: Emergency database setup..."
            
            # Use current user instead of postgres user
            CURRENT_USER=$(whoami)
            sudo -u postgres createuser "$CURRENT_USER" --superuser 2>/dev/null || true
            sudo -u postgres createdb student_grades 2>/dev/null || true
            sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE student_grades TO \"$CURRENT_USER\";" 2>/dev/null || true
            
            # Test with current user
            if psql -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
                log_success "Auto-fix 3 successful! Using current user ($CURRENT_USER)"
                DB_OK=true
            fi
        fi
    fi
    
    if [ "$DB_OK" = false ]; then
        log_error "All auto-fixes failed!"
        log_info "Manual intervention required:"
        echo "  1. Run: ./fix_database_emergency.sh"
        echo "  2. Or run: ./complete_setup.sh"
        echo "  3. Check PostgreSQL status: sudo systemctl status postgresql"
        
        read -p "Do you want to continue anyway? The app will try its own connection methods. (y/N): " -n 1 -r
        echo
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            exit 1
        fi
    else
        log_success "Database connection fixed automatically!"
    fi
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
    log_error "Workspace not built! Run: colcon build --packages-select g1_ass1_pkg"
    exit 1
fi

echo ""
log_success "Environment ready! Launching system..."
echo ""
echo "� Starting all nodes:"
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
