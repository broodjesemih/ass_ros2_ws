#!/bin/bash

echo "=== PostgreSQL Debug Information ==="
echo ""

echo "1. PostgreSQL Service Status:"
systemctl status postgresql --no-pager -l || echo "PostgreSQL service not found"
echo ""

echo "2. PostgreSQL Version:"
sudo -u postgres psql --version 2>/dev/null || echo "Cannot access postgres user"
echo ""

echo "3. Available PostgreSQL Users:"
sudo -u postgres psql -t -c "SELECT usename FROM pg_user;" 2>/dev/null || echo "Cannot query users"
echo ""

echo "4. Available Databases:"
sudo -u postgres psql -t -c "SELECT datname FROM pg_database WHERE datistemplate = false;" 2>/dev/null || echo "Cannot query databases"
echo ""

echo "5. Testing Connection Methods:"
echo ""

echo "Method A: postgres user with password"
if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
    echo "✓ postgres user with password: SUCCESS"
else
    echo "✗ postgres user with password: FAILED"
fi

echo "Method B: current user peer authentication"
if psql -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
    echo "✓ current user peer auth: SUCCESS"
else
    echo "✗ current user peer auth: FAILED"
fi

echo "Method C: postgres user peer authentication"
if sudo -u postgres psql -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
    echo "✓ postgres user peer auth: SUCCESS"
else
    echo "✗ postgres user peer auth: FAILED"
fi

echo ""
echo "6. PostgreSQL Configuration Files:"
PG_VERSION=$(sudo -u postgres psql -t -c "SHOW server_version;" 2>/dev/null | grep -oE '[0-9]+\.[0-9]+' | head -1)
if [ -n "$PG_VERSION" ]; then
    echo "PostgreSQL Version: $PG_VERSION"
    CONFIG_DIR="/etc/postgresql/$PG_VERSION/main"
    if [ -d "$CONFIG_DIR" ]; then
        echo "Config directory: $CONFIG_DIR"
        echo "Authentication config (pg_hba.conf):"
        sudo cat "$CONFIG_DIR/pg_hba.conf" | grep -E "^(local|host)" | head -5
    else
        echo "Config directory not found at expected location"
    fi
else
    echo "Cannot determine PostgreSQL version"
fi

echo ""
echo "=== Recommended Actions ==="
echo "If connections fail, try:"
echo "1. sudo systemctl restart postgresql"
echo "2. ./setup_postgresql.sh"
echo "3. Check /var/log/postgresql/ for error logs"
