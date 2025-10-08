#!/bin/bash

echo "=== PostgreSQL Socket Fix Script ==="
echo ""

# Check if running as root
if [ "$EUID" -eq 0 ]; then
    echo "❌ Don't run this script as root (sudo). Run as normal user."
    exit 1
fi

echo "🔧 Checking PostgreSQL service status..."
if sudo systemctl is-active --quiet postgresql; then
    echo "✅ PostgreSQL is running"
else
    echo "❌ PostgreSQL is not running. Starting it..."
    sudo systemctl start postgresql
    
    if sudo systemctl is-active --quiet postgresql; then
        echo "✅ PostgreSQL started successfully"
    else
        echo "❌ Failed to start PostgreSQL. Checking for issues..."
        
        # Check if PostgreSQL is installed
        if ! command -v psql >/dev/null 2>&1; then
            echo "❌ PostgreSQL is not installed. Run: ./setup_postgresql.sh"
            exit 1
        fi
        
        # Try alternative start methods
        echo "Trying alternative PostgreSQL start methods..."
        
        # Find PostgreSQL version and try version-specific service
        PG_VERSIONS=$(ls /etc/postgresql/ 2>/dev/null || echo "")
        for version in $PG_VERSIONS; do
            echo "Trying PostgreSQL version $version..."
            sudo systemctl start postgresql@${version}-main 2>/dev/null && break
        done
        
        # Final check
        if ! sudo systemctl is-active --quiet postgresql; then
            echo "❌ Could not start PostgreSQL. Manual intervention needed."
            echo "Check logs: sudo journalctl -u postgresql --no-pager -n 20"
            exit 1
        fi
    fi
fi

echo ""
echo "🔧 Checking socket files..."

# Common PostgreSQL socket locations
SOCKET_LOCATIONS=(
    "/var/run/postgresql"
    "/tmp"
    "/run/postgresql"
)

SOCKET_FOUND=false
for location in "${SOCKET_LOCATIONS[@]}"; do
    if ls "$location"/.s.PGSQL.* >/dev/null 2>&1; then
        echo "✅ Found PostgreSQL socket in $location"
        ls -la "$location"/.s.PGSQL.*
        SOCKET_FOUND=true
    fi
done

if [ "$SOCKET_FOUND" = false ]; then
    echo "⚠️  No PostgreSQL socket files found in common locations"
    echo "Checking PostgreSQL configuration..."
    
    PG_VERSION=$(sudo -u postgres psql -t -c "SHOW server_version;" 2>/dev/null | grep -oE '[0-9]+\.[0-9]+' | head -1)
    if [ -n "$PG_VERSION" ]; then
        CONFIG_FILE="/etc/postgresql/$PG_VERSION/main/postgresql.conf"
        if [ -f "$CONFIG_FILE" ]; then
            echo "Socket directory from config:"
            sudo grep "unix_socket_directories" "$CONFIG_FILE" || echo "unix_socket_directories not found in config"
        fi
    fi
fi

echo ""
echo "🔧 Testing database connections..."

# Test 1: TCP connection
echo "Test 1: TCP connection (localhost:5432)"
if PGPASSWORD=password psql -h localhost -p 5432 -U postgres -d postgres -c "SELECT 1;" >/dev/null 2>&1; then
    echo "✅ TCP connection works"
else
    echo "❌ TCP connection failed"
fi

# Test 2: Unix socket with postgres user
echo "Test 2: Unix socket with postgres user"
if sudo -u postgres psql -d postgres -c "SELECT 1;" >/dev/null 2>&1; then
    echo "✅ Unix socket with postgres user works"
else
    echo "❌ Unix socket with postgres user failed"
fi

# Test 3: Current user
echo "Test 3: Current user connection"
if psql -d postgres -c "SELECT 1;" >/dev/null 2>&1; then
    echo "✅ Current user connection works"
else
    echo "❌ Current user connection failed"
    
    # Try to create current user
    CURRENT_USER=$(whoami)
    echo "Creating PostgreSQL user for $CURRENT_USER..."
    sudo -u postgres createuser "$CURRENT_USER" --superuser 2>/dev/null || echo "User may already exist"
fi

echo ""
echo "🔧 Checking database existence..."
if sudo -u postgres psql -lqt | cut -d \| -f 1 | grep -qw student_grades; then
    echo "✅ Database 'student_grades' exists"
else
    echo "❌ Database 'student_grades' not found. Creating it..."
    sudo -u postgres createdb student_grades
    if [ $? -eq 0 ]; then
        echo "✅ Database 'student_grades' created"
    else
        echo "❌ Failed to create database"
    fi
fi

echo ""
echo "🚀 Final connection test..."
if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT version();" >/dev/null 2>&1; then
    echo "✅ Everything looks good! The database connection should work now."
    echo ""
    echo "You can now run:"
    echo "  ./start_system.sh"
    echo "or"
    echo "  colcon build --packages-select g1_ass1_pkg && ros2 launch g1_ass1_pkg system.launch.xml"
else
    echo "❌ Still having connection issues."
    echo ""
    echo "Manual steps to try:"
    echo "1. sudo systemctl restart postgresql"
    echo "2. ./setup_postgresql.sh"
    echo "3. Check logs: sudo journalctl -u postgresql"
    echo "4. Check PostgreSQL config: sudo nano /etc/postgresql/*/main/pg_hba.conf"
fi
