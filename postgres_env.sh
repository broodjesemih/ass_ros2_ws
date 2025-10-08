# PostgreSQL Environment Variables for ROS2 Project
# Source this file before running the application

export PGHOST=localhost
export PGPORT=5432
export PGDATABASE=student_grades  
export PGUSER=postgres
export PGPASSWORD=password

echo "PostgreSQL environment variables set:"
echo "  Host: $PGHOST"
echo "  Port: $PGPORT"
echo "  Database: $PGDATABASE"
echo "  User: $PGUSER"
