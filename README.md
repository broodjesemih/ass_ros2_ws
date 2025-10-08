# ROS2 Grade Calculator System

Complete ROS2-based grade calculator with PostgreSQL database backend for automated student assessment Quick Fix:
Most issues can be resolved by running the setup script again:
```bash
./complete_setup.sh
```
This script automatically detects and fixes common PostgreSQL authentication and ROS2 workspace issues.ake management.

## Quick Start

```bash
# Complete setup (installs everything automatically)
./complete_setup.sh

# Start the system
./run_system.sh

# Test the system  
./test.sh

# Check database contents
./check_db.sh [rows]
```

## System Architecture

This system implements an automated grade calculator for students with comprehensive retake management:

### Core Components:
- **tentamen_result_generator**: Generates exam results for simulation
- **cijfer_calculator**: Calculates final grades based on exam results  
- **final_cijfer_determinator**: Determines final grades and triggers database storage
- **herkansing_scheduler**: Schedules retakes for failed students
- **herkansing_cijfer_determinator**: Handles retake grade calculations via ROS2 Actions

### ROS2 Nodes:
- `tentamen_result_generator` - Publishes exam results to topics
- `cijfer_calculator` - Service for grade calculations (Wessel gets +10 bonus!)
- `final_cijfer_determinator` - Subscribes to results and determines final grades
- `herkansing_scheduler` - Monitors database and schedules retakes
- `herkansing_cijfer_determinator` - Action server for retake processing

### Database Integration:
- PostgreSQL with `student_results` table for persistent storage
- Automatic connection detection with multiple fallback methods
- Real-time updates via ROS2 topic/service communication
- Thread-safe database operations with comprehensive error handling

## Dependencies

### System Requirements:
- **ROS2 Jazzy** (Ubuntu 24.04, Fedora 40, or compatible)
- **PostgreSQL** (version 12+ recommended)
- **libpqxx-dev** (C++ PostgreSQL client library)
- **Google Test** (for unit testing)

### PostgreSQL Setup:
The system requires a PostgreSQL database with proper authentication. The setup script handles this automatically, but manual setup requires:

```bash
# Install PostgreSQL
sudo apt install postgresql postgresql-contrib libpqxx-dev  # Ubuntu/Debian
sudo dnf install postgresql postgresql-server libpqxx-devel  # Fedora/RHEL

# Create database and user
sudo -u postgres createdb student_grades
sudo -u postgres psql -c "CREATE USER postgres WITH PASSWORD 'password';"
sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE student_grades TO postgres;"
```

## Available Commands

```bash
./complete_setup.sh     # Complete installation with dependency management
./run_system.sh        # Start ROS2 system with database validation
./test.sh             # Run comprehensive unit tests  
./check_db.sh [rows]  # Check database contents (default: 10 rows)
./test_database.sh    # Diagnostic tool for database connectivity
```

### Manual Building
```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select g1_ass1_pkg g1_interface_pkg
source install/setup.bash
```

### Manual System Start
```bash
source install/setup.bash
ros2 launch g1_ass1_pkg system.launch.xml
```

## Database Configuration

### Connection Details:
- **Database**: `student_grades` 
- **User**: `postgres`
- **Password**: `password`
- **Host**: `localhost:5432`
- **Backup Methods**: Unix sockets, peer authentication

### Connection Priority:
1. TCP connection with password authentication
2. Unix socket with current system user
3. PostgreSQL peer authentication
4. Simple local connection fallback

## Troubleshooting

### PostgreSQL Issues:
```bash
# Check service status
sudo systemctl status postgresql

# Restart PostgreSQL service
sudo systemctl restart postgresql

# View PostgreSQL logs
sudo journalctl -u postgresql -f

# Test database connectivity
./test_database.sh
```

### ROS2 Issues:
```bash
# Check ROS2 installation
ros2 doctor

# Rebuild workspace
colcon build --symlink-install

# Clear build cache if needed
rm -rf build/ install/ log/
```
## 💾 Database Info

- **Database**: `student_grades` 
- **User**: `postgres`
- **Password**: `password`
- **Host**: `localhost:5432`

## � Troubleshooting

Problems? Run `./complete_setup.sh` again - het lost de meeste problemen automatisch op.

## Development Guide

### Building and Testing:
```bash
# Build complete workspace
colcon build --packages-select g1_ass1_pkg g1_interface_pkg

# Run comprehensive tests  
colcon test --packages-select g1_ass1_pkg
colcon test-result --verbose

# Manual database testing
psql -h localhost -U postgres -d student_grades
```

### Custom ROS2 Interfaces:
The project uses custom ROS2 interfaces defined in `g1_interface_pkg`:
- **Messages**: `Tentamen`, `Student` 
- **Services**: `Tentamens` (grade calculation)
- **Actions**: `Herkanser` (retake processing)

### Database Schema:
```sql
CREATE TABLE student_results (
    id SERIAL PRIMARY KEY,
    student_name VARCHAR(255) NOT NULL,
    course VARCHAR(255) NOT NULL,
    number_of_exams INTEGER,
    final_result REAL,
    timestamp BIGINT
);
```

### Testing Framework:
- **Unit Tests**: Database operations, service calls, topic communication
- **Integration Tests**: End-to-end workflow validation  
- **System Tests**: Multi-node interaction and performance testing
- **Coverage**: Full ROS2 ecosystem with PostgreSQL integration

---

**Created for TI Minor Grade Generator System**  
Advanced ROS2 architecture with real-time database integration and comprehensive error handling.
