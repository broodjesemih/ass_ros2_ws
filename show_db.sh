#!/bin/bash

# Simple database viewer
echo "🗄️  Database Contents Viewer"
echo "=========================="

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Direct database query function
query_db() {
    echo -e "${BLUE}📊 Connecting to database...${NC}"
    
    # Try the working connection method directly
    PGPASSWORD=password psql -h localhost -p 5432 -U postgres -d student_grades << 'EOF'
\timing off
\echo '✅ Connected to student_grades database'
\echo ''

\echo '📈 Quick Stats:'
SELECT 
    COUNT(*) as "Total Records",
    COUNT(DISTINCT student_name) as "Students",
    COUNT(DISTINCT course) as "Courses",
    COUNT(*) FILTER (WHERE final_result IS NOT NULL) as "Completed Exams",
    COUNT(*) FILTER (WHERE final_result IS NULL) as "In Progress"
FROM student_results;

\echo ''
\echo '👥 ALL STUDENTS - COMPLETE LIST:'
\echo '======================================'
SELECT 
    ROW_NUMBER() OVER (ORDER BY student_name, course) as "#",
    student_name as "Student Name",
    course as "Course", 
    number_of_exams as "Exams Done",
    CASE 
        WHEN final_result IS NULL THEN '⏳ In Progress'
        ELSE '✅ ' || final_result::text 
    END as "Status/Grade",
    to_timestamp(timestamp) as "Last Updated"
FROM student_results 
ORDER BY student_name, course;

\echo ''
\echo '📊 STUDENT PROGRESS SUMMARY:'
\echo '=============================='
SELECT 
    student_name as "👤 Student",
    COUNT(*) as "📚 Courses",
    COUNT(*) FILTER (WHERE final_result IS NOT NULL) as "✅ Done",
    COUNT(*) FILTER (WHERE final_result IS NULL) as "⏳ Progress",
    CASE 
        WHEN AVG(final_result) IS NOT NULL 
        THEN '🎯 ' || ROUND(AVG(final_result), 1)::text
        ELSE '⏳ N/A'
    END as "Average"
FROM student_results 
GROUP BY student_name 
ORDER BY student_name;

\echo ''
\echo '📚 COURSE COMPLETION RATES:'
\echo '==========================='
SELECT 
    course as "📖 Course",
    COUNT(*) as "👥 Students",
    COUNT(*) FILTER (WHERE final_result IS NOT NULL) as "✅ Finished",
    COUNT(*) FILTER (WHERE final_result IS NULL) as "⏳ Active",
    CASE 
        WHEN AVG(final_result) IS NOT NULL 
        THEN '📊 ' || ROUND(AVG(final_result), 1)::text
        ELSE '⏳ N/A'
    END as "Avg Grade"
FROM student_results 
GROUP BY course 
ORDER BY course;

EOF
}

# Try alternative connection if first fails
query_db_alt() {
    echo -e "${YELLOW}Trying alternative connection...${NC}"
    
    PGPASSWORD=password psql -h localhost -p 5433 -U postgres -d student_grades << 'EOF'
SELECT 'Connected via port 5433' as status;
SELECT * FROM student_results ORDER BY student_name, course;
EOF
}

# Execute query
if ! query_db 2>/dev/null; then
    if ! query_db_alt 2>/dev/null; then
        echo -e "${RED}❌ Could not connect to database${NC}"
        echo "💡 Make sure PostgreSQL is running and the database exists"
        echo "🔧 Try: ./run_system.sh"
    fi
fi

echo ""
echo -e "${GREEN}💡 Tip: Run 'watch -n 3 ./show_db.sh' to see live updates!${NC}"
