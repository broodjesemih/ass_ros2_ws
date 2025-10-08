#!/bin/bash

# Simple database checker script
echo "🔍 Checking database contents..."
echo ""

# Colors
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

# Try to connect and show data
if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "SELECT 1;" >/dev/null 2>&1; then
    echo -e "${GREEN}✅ Connected to database${NC}"
    echo ""
    
    echo -e "${BLUE}📊 Quick Overview:${NC}"
    PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "
    SELECT 
        COUNT(*) as \"Total Records\",
        COUNT(*) FILTER (WHERE final_result IS NOT NULL) as \"Completed\",
        COUNT(*) FILTER (WHERE final_result IS NULL) as \"In Progress\"
    FROM student_results;
    "
    
    echo -e "${BLUE}👥 Students in Progress:${NC}"
    PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "
    SELECT 
        student_name as \"Student\",
        course as \"Course\"
    FROM student_results 
    WHERE final_result IS NULL 
    ORDER BY student_name, course;
    "
    
    echo -e "${BLUE}🎯 Latest Completions (Last 5):${NC}"
    PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "
    SELECT 
        student_name as \"Student\",
        course as \"Course\",
        final_result as \"Grade\",
        to_timestamp(timestamp) as \"Completed\"
    FROM student_results 
    WHERE final_result IS NOT NULL 
    ORDER BY timestamp DESC 
    LIMIT 5;
    "

else
    echo "❌ Could not connect to database"
    echo "💡 Try running: ./run_system.sh first to setup the database"
    echo "💡 Or check PostgreSQL status: sudo systemctl status postgresql"
fi
