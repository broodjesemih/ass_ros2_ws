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
if sudo -u postgres psql -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
    echo "✓ Database connection successful!"
    echo "You can test the connection with:"
    echo "psql -h localhost -U postgres -d student_grades"
else
    echo "⚠ Database connection test failed. Trying alternative setup..."
    
    # Alternative: use the system user that installed PostgreSQL
    CURRENT_USER=$(whoami)
    sudo -u postgres createuser "$CURRENT_USER" --superuser 2>/dev/null || true
    
    echo "Alternative connection method:"
    echo "psql -d student_grades"
    echo "or"  
    echo "sudo -u postgres psql -d student_grades"
fi
