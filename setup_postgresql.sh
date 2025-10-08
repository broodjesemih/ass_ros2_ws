#!/bin/bash

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
sudo -u postgres psql -c "CREATE DATABASE student_grades;" || echo "Database may already exist"
sudo -u postgres psql -c "ALTER USER postgres PASSWORD 'password';" || echo "Password already set"
sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE student_grades TO postgres;" || echo "Privileges may already be granted"

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
echo "You can test the connection with:"
echo "psql -h localhost -U postgres -d student_grades"
