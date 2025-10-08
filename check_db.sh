#!/bin/bash

# Quick database checker script
echo "🔍 Checking database contents..."

# Try different connection methods to connect to PostgreSQL
echo ""
echo "📊 Attempting to connect and show data..."

# Method 1: Standard connection
if PGPASSWORD=password psql -h localhost -U postgres -d student_grades -c "\dt; SELECT * FROM student_results LIMIT 10;" 2>/dev/null; then
    echo "✅ Connected via TCP (password method)"
elif psql -d student_grades -c "\dt; SELECT * FROM student_results LIMIT 10;" 2>/dev/null; then
    echo "✅ Connected via default method"
elif sudo -u postgres psql -d student_grades -c "\dt; SELECT * FROM student_results LIMIT 10;" 2>/dev/null; then
    echo "✅ Connected via postgres user"
else
    echo "❌ Could not connect to database"
    echo "💡 Try running: ./run_system.sh first to setup the database"
fi
