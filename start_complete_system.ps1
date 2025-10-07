# Complete Cijfer Generator System Launcher - PowerShell Version
# Dit script start alles wat je nodig hebt in de juiste volgorde

Write-Host "🚀 Starting Complete Cijfer Generator System" -ForegroundColor Green
Write-Host "=============================================" -ForegroundColor Green

# 1. Start PostgreSQL Database
Write-Host ""
Write-Host "🐘 Step 1: Starting PostgreSQL Database..." -ForegroundColor Yellow
Set-Location "C:\Users\semih\Assessment\1_ROS2\ass_ros2_ws"
docker-compose up -d postgres

# 2. Wait for database to be ready
Write-Host ""
Write-Host "⏳ Step 2: Waiting for database to be ready..." -ForegroundColor Yellow
for ($i = 1; $i -le 15; $i++) {
    try {
        docker exec cijfer_generator_db pg_isready -U cijfer_user | Out-Null
        if ($LASTEXITCODE -eq 0) {
            Write-Host "✅ PostgreSQL is ready!" -ForegroundColor Green
            break
        }
    }
    catch {
        # Continue waiting
    }
    Write-Host "   Attempt $i/15... waiting 2 seconds" -ForegroundColor Gray
    Start-Sleep -Seconds 2
}

# 3. Verify database connection
Write-Host ""
Write-Host "🔍 Step 3: Verifying database connection..." -ForegroundColor Yellow
try {
    docker exec cijfer_generator_db psql -U cijfer_user -d cijfer_generator -c "SELECT COUNT(*) FROM student_results;" | Out-Null
    if ($LASTEXITCODE -eq 0) {
        Write-Host "✅ Database connection verified!" -ForegroundColor Green
    }
    else {
        Write-Host "❌ Database connection failed!" -ForegroundColor Red
        exit 1
    }
}
catch {
    Write-Host "❌ Database connection failed!" -ForegroundColor Red
    exit 1
}

# 4. Show current database content
Write-Host ""
Write-Host "📊 Current database content:" -ForegroundColor Cyan
docker exec cijfer_generator_db psql -U cijfer_user -d cijfer_generator -c "SELECT student_name, course, number_of_exams, final_result FROM student_results ORDER BY student_name, course;"

# 5. Start WSL2 ROS2 system
Write-Host ""
Write-Host "🤖 Step 4: Starting ROS2 system in WSL2..." -ForegroundColor Yellow
Write-Host "   The system will run for 60 seconds then show results" -ForegroundColor Gray
Write-Host "   Press Ctrl+C to stop early" -ForegroundColor Gray
Write-Host ""

# Start ROS2 in WSL2 with environment variables
wsl -d Ubuntu -e bash -c "
cd ~/ros2_ws &&
source /opt/ros/jazzy/setup.bash &&
source install/setup.bash &&
export POSTGRES_HOST=10.255.255.254 &&
export POSTGRES_PORT=5432 &&
export POSTGRES_DB=cijfer_generator &&
export POSTGRES_USER=cijfer_user &&
export POSTGRES_PASSWORD=cijfer_password &&
echo '🚀 Starting ROS2 nodes with database connection...' &&
timeout 60s ros2 launch g1_ass1_pkg cijfer_system.launch.py
"

# 6. Show final results
Write-Host ""
Write-Host "📊 Final Results:" -ForegroundColor Green
Write-Host "=================" -ForegroundColor Green
docker exec cijfer_generator_db psql -U cijfer_user -d cijfer_generator -c "SELECT student_name, course, final_result, to_timestamp(timestamp) as completed_at FROM student_results WHERE final_result > 0 ORDER BY timestamp DESC;"

Write-Host ""
Write-Host "✅ System test completed!" -ForegroundColor Green
Write-Host "🐘 PostgreSQL container is still running - use 'docker-compose down' to stop" -ForegroundColor Yellow
