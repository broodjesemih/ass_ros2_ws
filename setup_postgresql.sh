#!/bin/bash

# PostgreSQL Setup Script for ROS2 Project
# This script installs and configures PostgreSQL with libpqxx for the grade calculator system

echo "=== PostgreSQL Setup for ROS2 Grade Calculator ==="
echo ""

# Check if PostgreSQL is already installed
if command -v psql >/dev/null 2>&1; then
    echo "PostgreSQL is already installed. Version:"
    psql --version
    echo ""
fi

# Install PostgreSQL and development libraries
echo "Installing PostgreSQL and development libraries..."
sudo apt update
sudo apt install -y postgresql postgresql-contrib postgresql-server-dev-all

# Install libpqxx (PostgreSQL C++ library)
echo "Installing libpqxx..."
sudo apt install -y libpqxx-dev

# Start PostgreSQL service
echo "Starting PostgreSQL service..."
sudo systemctl start postgresql
sudo systemctl enable postgresql

# Wait a moment for PostgreSQL to fully start
echo "Waiting for PostgreSQL to start..."
sleep 3

# Check if PostgreSQL is actually running
if ! sudo systemctl is-active --quiet postgresql; then
    echo "❌ PostgreSQL failed to start. Checking logs..."
    sudo journalctl -u postgresql --no-pager -n 10
    echo "Attempting alternative start methods..."
    
    # Try to start with specific version
    PG_VERSION=$(sudo -u postgres psql --version 2>/dev/null | grep -oE '[0-9]+\.[0-9]+' | head -1)
    if [ -n "$PG_VERSION" ]; then
        echo "Trying to start PostgreSQL $PG_VERSION..."
        sudo systemctl start postgresql@$PG_VERSION-main 2>/dev/null || true
    fi
fi

# Create database and user
echo "Setting up database..."

# First, ensure postgres user exists and create it if it doesn't
echo "Creating postgres user if it doesn't exist..."
sudo -u postgres createuser postgres 2>/dev/null || echo "User postgres already exists or is the default superuser"

# Alternative: create the database and user using the system postgres account
echo "Creating database and setting up user..."
sudo -u postgres psql << EOF
-- Create database if it doesn't exist
SELECT 'CREATE DATABASE student_grades' WHERE NOT EXISTS (SELECT FROM pg_database WHERE datname = 'student_grades')\gexec

-- Ensure postgres user exists and has the right permissions
DO \$\$
BEGIN
   IF NOT EXISTS (SELECT FROM pg_catalog.pg_user WHERE usename = 'postgres') THEN
      CREATE USER postgres WITH SUPERUSER CREATEDB CREATEROLE LOGIN;
   END IF;
END
\$\$;

-- Set password for postgres user
ALTER USER postgres PASSWORD 'password';

-- Grant all privileges on database
GRANT ALL PRIVILEGES ON DATABASE student_grades TO postgres;
EOF

# Set authentication method to md5 for localhost connections
echo "Configuring PostgreSQL authentication..."
PG_VERSION=$(sudo -u postgres psql -t -c "SELECT version();" | grep -oE '[0-9]+\.[0-9]+' | head -1)
PG_CONF_DIR="/etc/postgresql/${PG_VERSION}/main"

# Backup and update pg_hba.conf to allow password authentication
sudo cp "${PG_CONF_DIR}/pg_hba.conf" "${PG_CONF_DIR}/pg_hba.conf.backup" 2>/dev/null || true
sudo sed -i 's/local   all             postgres                                peer/local   all             postgres                                md5/' "${PG_CONF_DIR}/pg_hba.conf" 2>/dev/null || true
sudo sed -i 's/local   all             all                                     peer/local   all             all                                     md5/' "${PG_CONF_DIR}/pg_hba.conf" 2>/dev/null || true

# Restart PostgreSQL to apply changes
sudo systemctl restart postgresql

echo "PostgreSQL setup complete!"
echo "Database: student_grades"
echo "User: postgres"  
echo "Password: password"
echo "Host: localhost"
echo "Port: 5432 (default)"

echo ""
echo "Testing database connection..."

# Test multiple connection methods
CURRENT_USER=$(whoami)

echo "Method 1: Testing postgres user connection..."
if sudo -u postgres psql -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
    echo "✓ Method 1 successful: postgres user works"
    echo "Connection string: postgresql://postgres:password@localhost/student_grades"
else
    echo "✗ Method 1 failed: postgres user connection failed"
    
    echo "Method 2: Creating and testing current user ($CURRENT_USER)..."
    # Create current user as PostgreSQL user
    sudo -u postgres createuser "$CURRENT_USER" --superuser 2>/dev/null || echo "User $CURRENT_USER may already exist"
    sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE student_grades TO \"$CURRENT_USER\";" 2>/dev/null || true
    
    if psql -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
        echo "✓ Method 2 successful: current user ($CURRENT_USER) works"
        echo "Connection string: postgresql:///$CURRENT_USER"
    else
        echo "✗ Method 2 failed"
        
        echo "Method 3: Testing peer authentication..."
        if sudo -u postgres psql -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
            echo "✓ Method 3 successful: peer authentication works"
            echo "Connection string: postgresql://localhost/student_grades"
        else
            echo "✗ Method 3 failed"
            echo "⚠ All connection methods failed. Manual intervention required."
        fi
    fi
fi

echo ""
echo "=== Connection Test Results ==="
echo "Try these connection methods in order:"
echo "1. psql -h localhost -U postgres -d student_grades"
echo "2. psql -d student_grades"
echo "3. sudo -u postgres psql -d student_grades"
echo ""
echo "The C++ application will automatically try these methods."
