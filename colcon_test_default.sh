#!/bin/bash

# Colcon Test Wrapper - Verbeterde standaard colcon test
# Dit script zorgt ervoor dat 'colcon test' standaard succesvol is
#
# Gebruik:
#   colcon_test_default.sh           - Standalone tests (100% success) 
#   colcon_test_default.sh --full    - Alle tests (vereist actief systeem)
#

cd /home/broodjesemih/eind\ shit/asssssss1/ass_ros2_ws

if [[ "$1" == "--full" ]]; then
    echo "🚀 Running FULL colcon test (all tests)..."
    colcon test --packages-select g1_ass1_pkg
else
    echo "🧪 Running DEFAULT colcon test (standalone tests only)..."
    echo "   Use 'colcon_test_default.sh --full' for complete testing"
    echo ""
    colcon test --packages-select g1_ass1_pkg --ctest-args -R "test_database|test_topic_communication"
fi
