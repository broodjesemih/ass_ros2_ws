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
echo "1. Checking PostgreSQL service..."
if systemctl is-active --quiet postgresql; then
    echo -e "${GREEN}PostgreSQL service is running${NC}"
else
    echo -e "${RED}PostgreSQL service is not running${NC}"
    echo -e "${YELLOW}Try: sudo systemctl start postgresql${NC}"
fi
echo ""

# 2. Check socket files
echo "2. Checking socket files..."
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
echo "3. Checking database existence..."
if sudo -u postgres psql -lqt | cut -d \| -f 1 | grep -qw student_grades; then
    echo -e "${GREEN}Database 'student_grades' exists${NC}"
else
    echo -e "${RED}Database 'student_grades' not found${NC}"
    echo -e "${YELLOW}Try: sudo -u postgres createdb student_grades${NC}"
fi
echo ""

# 4. Test connections
echo "4. Testing database connections..."

TESTS=(
    "PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c 'SELECT version();'|TCP with password"
    "psql -d student_grades -c 'SELECT version();'|Current user socket"
    "sudo -u postgres psql -d student_grades -c 'SELECT version();'|Postgres user socket"
    "timeout 3s psql -h localhost -d student_grades -c 'SELECT version();' </dev/null|TCP without auth"
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
echo "5. Testing application connection methods..."
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
