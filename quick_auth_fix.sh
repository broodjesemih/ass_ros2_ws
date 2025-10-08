#!/bin/bash

# =============================================================================
# Quick PostgreSQL# Create current user  
sudo -u postgres createuser "$CURRENT_USER" --superuser 2>/dev/null || true
sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE student_grades TO "$CURRENT_USER";" 2>/dev/null || trueor ROS2 Grade Calculator
# =============================================================================
# This script specifically fixes the password authentication and socket issues
# that cause "password authentication failed" and "socket not found" errors
# =============================================================================

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log_info() { echo -e "${BLUE}[INFO]${NC} $1"; }
log_success() { echo -e "${GREEN}[SUCCESS]${NC} $1"; }
log_warning() { echo -e "${YELLOW}[WARNING]${NC} $1"; }
log_error() { echo -e "${RED}[ERROR]${NC} $1"; }

echo "======================================================================="
echo "🔧 Quick PostgreSQL Authentication Fix"
echo "======================================================================="
echo ""
echo "This script fixes:"
echo "  ❌ password authentication failed for user \"postgres\""  
echo "  ❌ socket file not found errors"
echo "  ❌ connection refused errors"
echo ""

CURRENT_USER=$(whoami)

# 1. Check PostgreSQL status
log_info "Checking PostgreSQL status..."
if ! systemctl is-active --quiet postgresql; then
    log_warning "PostgreSQL not running. Starting..."
    sudo systemctl start postgresql
    sleep 3
    if ! systemctl is-active --quiet postgresql; then
        log_error "Cannot start PostgreSQL"
        exit 1
    fi
fi
log_success "PostgreSQL is running"

# 2. Fix authentication configuration first
log_info "Fixing PostgreSQL authentication configuration..."

# Find config directory
PG_CONFIG_DIR=""
POSSIBLE_DIRS=(
    "/etc/postgresql/*/main"
    "/var/lib/pgsql/data" 
    "/usr/local/var/postgres"
    "/opt/homebrew/var/postgres"
)

for pattern in "${POSSIBLE_DIRS[@]}"; do
    for dir in $pattern; do
        if [ -f "$dir/pg_hba.conf" ]; then
            PG_CONFIG_DIR="$dir"
            break 2
        fi
    done
done

if [ -n "$PG_CONFIG_DIR" ]; then
    log_success "Found PostgreSQL config in: $PG_CONFIG_DIR"
    
    # Backup current config
    sudo cp "$PG_CONFIG_DIR/pg_hba.conf" "$PG_CONFIG_DIR/pg_hba.conf.backup.$(date +%s)"
    
    # Create permissive configuration
    log_info "Creating permissive authentication configuration..."
    sudo tee "$PG_CONFIG_DIR/pg_hba.conf" > /dev/null << 'EOF'
# TYPE  DATABASE        USER            ADDRESS                 METHOD
# Trust local connections
local   all             postgres                                trust
local   all             all                                     trust

# Password authentication for TCP connections  
host    all             all             127.0.0.1/32            md5
host    all             all             ::1/128                 md5
host    all             all             localhost               md5

# Trust connections from localhost
host    all             all             127.0.0.1/32            trust
EOF

    # Reload PostgreSQL configuration
    log_info "Reloading PostgreSQL configuration..."
    sudo systemctl reload postgresql
    sleep 2
    
    log_success "Authentication configuration updated"
else
    log_warning "Could not find PostgreSQL configuration directory"
fi

# 3. Set up database and users
log_info "Setting up database and users..."

# Connect as postgres system user and set up everything
sudo -u postgres psql << EOFSQL
-- Set password for postgres user
ALTER USER postgres PASSWORD 'password';

-- Create database if not exists  
CREATE DATABASE IF NOT EXISTS student_grades;

-- Create current user if not exists
DO \$\$ 
BEGIN
    IF NOT EXISTS (SELECT FROM pg_catalog.pg_user WHERE usename = '$CURRENT_USER') THEN
        CREATE USER "$CURRENT_USER" WITH SUPERUSER CREATEDB CREATEROLE LOGIN;
    END IF;
END \$\$;

-- Grant permissions
GRANT ALL PRIVILEGES ON DATABASE student_grades TO postgres;
GRANT ALL PRIVILEGES ON DATABASE student_grades TO "$CURRENT_USER";

-- Show success
\echo 'Database setup completed!'
EOFSQL

if [ $? -eq 0 ]; then
    log_success "Database and users configured successfully"
else
    log_warning "Some database setup commands may have failed, but this is often normal"
fi

# 4. Test connections
log_info "Testing database connections..."

echo ""
echo "Testing connection methods:"

# Test 1: TCP with password
echo -n "1. TCP with password (postgres user): "
if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 'SUCCESS';" >/dev/null 2>&1; then
    echo -e "${GREEN}✅ Working${NC}"
    TCP_WORKS=true
else
    echo -e "${RED}❌ Failed${NC}"
    TCP_WORKS=false
fi

# Test 2: Local socket (current user)
echo -n "2. Local socket (current user): "
if psql -d student_grades -c "SELECT 'SUCCESS';" >/dev/null 2>&1; then
    echo -e "${GREEN}✅ Working${NC}"
    LOCAL_WORKS=true
else
    echo -e "${RED}❌ Failed${NC}"
    LOCAL_WORKS=false
fi

# Test 3: Local socket (postgres user)
echo -n "3. Local socket (postgres user): "
if sudo -u postgres psql -d student_grades -c "SELECT 'SUCCESS';" >/dev/null 2>&1; then
    echo -e "${GREEN}✅ Working${NC}"
    POSTGRES_WORKS=true
else
    echo -e "${RED}❌ Failed${NC}"
    POSTGRES_WORKS=false
fi

echo ""

# 5. Results and recommendations
if [ "$TCP_WORKS" = true ] || [ "$LOCAL_WORKS" = true ] || [ "$POSTGRES_WORKS" = true ]; then
    log_success "🎉 At least one connection method is working!"
    echo ""
    echo "✅ Your ROS2 application should now be able to connect to PostgreSQL"
    echo ""
    echo "You can now run:"
    echo "  ./run_system.sh"
    echo ""
    
    if [ "$TCP_WORKS" = true ]; then
        echo "💡 The application will use: postgresql://postgres:password@localhost/student_grades"
    elif [ "$LOCAL_WORKS" = true ]; then
        echo "💡 The application will use local socket connection with user: $CURRENT_USER"
    else
        echo "💡 The application will use postgres user via local socket"
    fi
else
    log_error "❌ All connection tests failed"
    echo ""
    echo "🔧 Additional troubleshooting needed:"
    echo "1. Check PostgreSQL logs: sudo journalctl -u postgresql -n 20"
    echo "2. Check PostgreSQL status: sudo systemctl status postgresql"
    echo "3. Try manual connection: sudo -u postgres psql"
    echo "4. Run full setup: ./complete_setup.sh"
    echo ""
    echo "If this is a fresh PostgreSQL installation, you may need to:"
    echo "  sudo -u postgres createdb student_grades"
    echo "  sudo -u postgres psql -c \"ALTER USER postgres PASSWORD 'password';\""
fi

echo ""
echo "======================================================================="
