#!/bin/bash
echo "Testing database connections..."

TESTS=(
    "psql -h localhost -U postgres -d student_grades -c 'SELECT version();'"
    "psql -d student_grades -c 'SELECT version();'"
    "sudo -u postgres psql -d student_grades -c 'SELECT version();'"
)

for i in "${!TESTS[@]}"; do
    echo "Test $((i+1)): ${TESTS[$i]}"
    if eval "PGPASSWORD=password ${TESTS[$i]}" >/dev/null 2>&1; then
        echo "✅ Success"
    else
        echo "❌ Failed"
    fi
done
