#!/bin/bash

# Quick database checker script
echo "🔍 Checking database contents..."
echo ""

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Function to show database data
show_database_data() {
    local connection_cmd="$1"
    local method_name="$2"
    
    echo -e "${GREEN}✅ Connected via $method_name${NC}"
    echo ""
    
    $connection_cmd << 'EOF'
-- Show basic info
\echo '📊 Database Overview:'
SELECT current_database() as "Database", current_user as "User";

\echo ''
\echo '� Record Counts:'
SELECT 
    COUNT(*) as "Total Records",
    COUNT(*) FILTER (WHERE final_result IS NOT NULL) as "Completed",
    COUNT(*) FILTER (WHERE final_result IS NULL) as "In Progress"
FROM student_results;

\echo ''
\echo '👥 All Students and Their Current Progress:'
SELECT 
    student_name as "Student",
    course as "Course", 
    number_of_exams as "Exams",
    CASE 
        WHEN final_result IS NULL THEN 'In Progress'
        ELSE final_result::text 
    END as "Final Grade"
FROM student_results 
ORDER BY student_name, course;

\echo ''
\echo '🎯 Students Summary:'
SELECT 
    student_name as "Student",
    COUNT(*) as "Total Courses",
    COUNT(*) FILTER (WHERE final_result IS NOT NULL) as "Completed",
    COUNT(*) FILTER (WHERE final_result IS NULL) as "In Progress",
    ROUND(AVG(final_result), 1) as "Avg Grade"
FROM student_results 
GROUP BY student_name 
ORDER BY student_name;

\echo ''
\echo '📚 Course Summary:'
SELECT 
    course as "Course",
    COUNT(*) as "Students",
    COUNT(*) FILTER (WHERE final_result IS NOT NULL) as "Finished",
    ROUND(AVG(final_result), 1) as "Avg Grade"
FROM student_results 
GROUP BY course 
ORDER BY course;

EOF
}

# Try different connection methods
if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -t -q >/dev/null 2>&1; then
    show_database_data "PGPASSWORD=password psql -h localhost -U postgres -d student_grades" "TCP (password method)"
elif psql -d student_grades -t -q >/dev/null 2>&1; then
    show_database_data "psql -d student_grades" "default method"
elif sudo -u postgres psql -d student_grades -t -q >/dev/null 2>&1; then
    show_database_data "sudo -u postgres psql -d student_grades" "postgres user"
else
    echo "❌ Could not connect to database"
    echo "💡 Try running: ./run_system.sh first to setup the database"
fi
