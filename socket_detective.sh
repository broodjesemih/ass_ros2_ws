#!/bin/bash

# =============================================================================
# PostgreSQL Socket Location Fix for Nout
# =============================================================================
# This script specifically addresses the "socket not found" issue
# by finding where PostgreSQL actually puts its socket files
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
echo "🔍 PostgreSQL Socket Detective - Finding Socket Files"
echo "======================================================================="
echo ""

# 1. Check if PostgreSQL is running
log_info "Checking PostgreSQL status..."
if ! systemctl is-active --quiet postgresql; then
    log_error "PostgreSQL is not running!"
    echo "Start it with: sudo systemctl start postgresql"
    exit 1
fi
log_success "PostgreSQL is running"

# 2. Find socket files
log_info "Searching for PostgreSQL socket files..."
echo ""

SOCKET_LOCATIONS=(
    "/var/run/postgresql"
    "/tmp"
    "/run/postgresql"  
    "/var/lib/postgresql"
    "/usr/local/var/postgres"
    "/opt/homebrew/var/postgres"
)

FOUND_SOCKETS=()
for location in "${SOCKET_LOCATIONS[@]}"; do
    if [ -d "$location" ]; then
        sockets=$(find "$location" -name ".s.PGSQL.*" 2>/dev/null)
        if [ -n "$sockets" ]; then
            echo "✅ Found socket(s) in: $location"
            for socket in $sockets; do
                echo "   📍 $socket"
                FOUND_SOCKETS+=("$location")
            done
        else
            echo "❌ No sockets in: $location"
        fi
    else
        echo "❌ Directory doesn't exist: $location"
    fi
done

echo ""

if [ ${#FOUND_SOCKETS[@]} -eq 0 ]; then
    log_error "No PostgreSQL socket files found!"
    log_info "This could mean PostgreSQL is not accepting local connections"
    
    # Try to find PostgreSQL process and its socket config
    log_info "Checking PostgreSQL process..."
    PG_PROCESS=$(ps aux | grep postgres | grep -v grep | head -1)
    if [ -n "$PG_PROCESS" ]; then
        echo "PostgreSQL process: $PG_PROCESS"
    fi
    
    # Check PostgreSQL configuration
    log_info "Checking PostgreSQL configuration..."
    CONFIGS=$(find /etc -name "postgresql.conf" 2>/dev/null)
    for config in $CONFIGS; do
        echo "Config file: $config"
        if [ -f "$config" ]; then
            socket_dir=$(grep "^unix_socket_directories" "$config" 2>/dev/null || echo "not found")
            echo "  Socket directories: $socket_dir"
        fi
    done
    
else
    log_success "Found socket files! Testing connections..."
    echo ""
    
    # Test connections using found socket locations
    for socket_dir in "${FOUND_SOCKETS[@]}"; do
        echo "Testing connection via: $socket_dir"
        
        # Test with different users
        USERS=("nout" "postgres" "$(whoami)")
        for user in "${USERS[@]}"; do
            echo -n "  User '$user': "
            if psql "host=$socket_dir dbname=postgres user=$user" -c "SELECT 'SUCCESS';" >/dev/null 2>&1; then
                echo -e "${GREEN}✅ Works${NC}"
                
                # Test with student_grades database
                echo -n "  User '$user' + student_grades DB: "
                if psql "host=$socket_dir dbname=student_grades user=$user" -c "SELECT 'SUCCESS';" >/dev/null 2>&1; then
                    echo -e "${GREEN}✅ Works${NC}"
                    WORKING_CONNECTION="host=$socket_dir dbname=student_grades user=$user"
                else
                    echo -e "${YELLOW}⚠ DB not found${NC}"
                    
                    # Try to create database
                    if psql "host=$socket_dir dbname=postgres user=$user" -c "CREATE DATABASE student_grades;" >/dev/null 2>&1; then
                        echo -e "${GREEN}✅ Created student_grades DB${NC}"
                        WORKING_CONNECTION="host=$socket_dir dbname=student_grades user=$user"
                    fi
                fi
            else
                echo -e "${RED}❌ Failed${NC}"
            fi
        done
        echo ""
    done
fi

# 3. Configure PostgreSQL for easier access
log_info "Setting up easier database access..."

# Create current user as PostgreSQL user if not exists
CURRENT_USER=$(whoami)
echo -n "Creating PostgreSQL user '$CURRENT_USER': "
if sudo -u postgres createuser "$CURRENT_USER" --superuser 2>/dev/null; then
    echo -e "${GREEN}✅ Created${NC}"
elif sudo -u postgres psql -c "ALTER USER \"$CURRENT_USER\" WITH SUPERUSER;" 2>/dev/null; then
    echo -e "${GREEN}✅ Updated${NC}"
else
    echo -e "${YELLOW}⚠ May already exist${NC}"
fi

# Create database if not exists
echo -n "Creating database 'student_grades': "
if sudo -u postgres createdb student_grades 2>/dev/null; then
    echo -e "${GREEN}✅ Created${NC}"
else
    echo -e "${YELLOW}⚠ May already exist${NC}"
fi

# Grant permissions
echo -n "Granting permissions to $CURRENT_USER: "
if sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE student_grades TO \"$CURRENT_USER\";" 2>/dev/null; then
    echo -e "${GREEN}✅ Granted${NC}"
else
    echo -e "${YELLOW}⚠ May already have permissions${NC}"
fi

# 4. Final test with recommended connection strings
echo ""
log_info "Testing recommended connection strings..."
echo ""

RECOMMENDED_CONNECTIONS=(
    "dbname=student_grades user=$CURRENT_USER"
    "host=/var/run/postgresql dbname=student_grades user=$CURRENT_USER"
    "host=/tmp dbname=student_grades user=$CURRENT_USER"  
    "host=/run/postgresql dbname=student_grades user=$CURRENT_USER"
    "postgresql://$CURRENT_USER@localhost/student_grades"
)

WORKING_CONNECTIONS=()
for conn in "${RECOMMENDED_CONNECTIONS[@]}"; do
    echo -n "Testing: $conn ... "
    if echo "SELECT 'SUCCESS';" | psql "$conn" >/dev/null 2>&1; then
        echo -e "${GREEN}✅ WORKS${NC}"
        WORKING_CONNECTIONS+=("$conn")
    else
        echo -e "${RED}❌ Failed${NC}"
    fi
done

# 5. Results and next steps
echo ""
echo "======================================================================="
log_info "Results Summary"
echo "======================================================================="
echo ""

if [ ${#WORKING_CONNECTIONS[@]} -gt 0 ]; then
    log_success "🎉 Found ${#WORKING_CONNECTIONS[@]} working connection method(s)!"
    echo ""
    echo "Working connections:"
    for conn in "${WORKING_CONNECTIONS[@]}"; do
        echo "  ✅ $conn"
    done
    
    echo ""
    log_success "Your ROS2 application should now work!"
    echo ""
    echo "🚀 Try running the system now:"
    echo "  ./run_system.sh"
    echo ""
    log_info "The C++ application will automatically try these working methods"
    
else
    log_error "❌ No working connections found"
    echo ""
    echo "🔧 Manual troubleshooting needed:"
    echo "1. Check PostgreSQL logs: sudo journalctl -u postgresql -n 30"
    echo "2. Check PostgreSQL config: sudo find /etc -name postgresql.conf"
    echo "3. Try connecting manually: sudo -u postgres psql"
    echo "4. Restart PostgreSQL: sudo systemctl restart postgresql"
    echo ""
    echo "If PostgreSQL was installed via snap:"
    echo "  sudo snap connect postgresql:network-bind"
    echo "  sudo systemctl restart snap.postgresql.postgresql"
fi

echo "======================================================================="
