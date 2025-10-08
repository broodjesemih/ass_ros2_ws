#!/bin/bash

# Comprehensive database inspector
echo "🗄️  PostgreSQL Database Inspector"
echo "=================================="

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Function to try different connection methods
try_connection() {
    local cmd="$1"
    local method_name="$2"
    
    echo -e "\n${BLUE}🔄 Trying: $method_name${NC}"
    
    if eval "$cmd" 2>/dev/null; then
        echo -e "${GREEN}✅ Success with: $method_name${NC}"
        return 0
    else
        echo -e "${RED}❌ Failed: $method_name${NC}"
        return 1
    fi
}

# Database connection attempts
CONNECTION_METHODS=(
    "PGPASSWORD=password psql -h localhost -p 5432 -U postgres -d student_grades"
    "PGPASSWORD=password psql -h localhost -p 5433 -U postgres -d student_grades"
    "psql -d student_grades"
    "sudo -u postgres psql -d student_grades"
)

METHOD_NAMES=(
    "TCP Port 5432 with password"
    "TCP Port 5433 with password"
    "Default user connection"
    "PostgreSQL superuser"
)

CONNECTED=false
WORKING_CONNECTION=""

# Test connections
echo -e "\n${YELLOW}🔍 Testing database connections...${NC}"
for i in "${!CONNECTION_METHODS[@]}"; do
    if try_connection "${CONNECTION_METHODS[$i]} -c 'SELECT 1;'" "${METHOD_NAMES[$i]}"; then
        CONNECTED=true
        WORKING_CONNECTION="${CONNECTION_METHODS[$i]}"
        break
    fi
done

if [ "$CONNECTED" = false ]; then
    echo -e "\n${RED}❌ Could not connect to database!${NC}"
    echo -e "${YELLOW}💡 Troubleshooting steps:${NC}"
    echo "   1. Check if PostgreSQL is running: sudo systemctl status postgresql"
    echo "   2. Start PostgreSQL: sudo systemctl start postgresql"
    echo "   3. Run setup: ./complete_setup.sh"
    echo "   4. Check system: ./run_system.sh"
    exit 1
fi

echo -e "\n${GREEN}✅ Connected to PostgreSQL database!${NC}"
echo -e "${BLUE}📋 Database Information:${NC}"

# Show database info
eval "$WORKING_CONNECTION" << 'EOF'
-- Show current database and user
SELECT current_database() as "Current Database", current_user as "Current User", version() as "PostgreSQL Version";

-- Show all tables
\echo ''
\echo '📊 Tables in database:'
\dt

-- Show student_results table structure
\echo ''
\echo '🏗️  Table structure for student_results:'
\d student_results

-- Count total records
\echo ''
\echo '📈 Record counts:'
SELECT 
    COUNT(*) as "Total Records",
    COUNT(*) FILTER (WHERE final_result IS NOT NULL) as "Completed",
    COUNT(*) FILTER (WHERE final_result IS NULL) as "In Progress"
FROM student_results;

-- Show sample data
\echo ''
\echo '📋 Sample data (first 5 records):'
SELECT student_name, course, number_of_exams, final_result 
FROM student_results 
ORDER BY timestamp DESC 
LIMIT 5;

-- Show students and their progress
\echo ''
\echo '👥 Students and course progress:'
SELECT 
    student_name,
    COUNT(*) as "Total Courses",
    COUNT(*) FILTER (WHERE final_result IS NOT NULL) as "Completed",
    COUNT(*) FILTER (WHERE final_result IS NULL) as "In Progress"
FROM student_results 
GROUP BY student_name 
ORDER BY student_name;

-- Show courses and completion status
\echo ''
\echo '📚 Courses and completion rates:'
SELECT 
    course,
    COUNT(*) as "Total Students",
    COUNT(*) FILTER (WHERE final_result IS NOT NULL) as "Completed",
    ROUND(AVG(final_result)::numeric, 2) as "Average Grade"
FROM student_results 
GROUP BY course 
ORDER BY course;

EOF

echo -e "\n${GREEN}🎉 Database inspection completed!${NC}"
echo -e "${BLUE}💡 Tips:${NC}"
echo "   - Run ./run_system.sh to start the grade calculator"
echo "   - Check logs with: tail -f ~/.ros/log/latest/tentamen_result_generator*"
echo "   - Monitor database changes in real-time with: watch -n 2 './check_db.sh'"
