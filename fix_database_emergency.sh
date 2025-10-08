#!/bin/bash

echo "🚨 Emergency Database Fix Script"
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
    echo "✅ PostgreSQL started successfully"
    
    # Recreate database as fallback
    echo "5. Ensuring database exists..."
    sudo -u postgres createdb student_grades 2>/dev/null || echo "Database may already exist"
    sudo -u postgres psql -c "ALTER USER postgres PASSWORD 'password';" 2>/dev/null || echo "Password may already be set"
    
    # Test connection
    if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
        echo "✅ Database connection working!"
        echo ""
        echo "You can now run:"
        echo "  ./run_system.sh"
    else
        echo "❌ Connection still failing"
        echo "Manual intervention required:"
        echo "  sudo -u postgres psql"
        echo "  Then create database and user manually"
    fi
else
    echo "❌ PostgreSQL failed to start"
    echo "Check logs: sudo journalctl -u postgresql"
fi
