#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import ExecuteProcess, TimerAction
from launch_ros.actions import Node

def generate_launch_description():
    """
    Complete Launch File - Eenvoudige versie die alles start
    """
    
    return LaunchDescription([
        # 1. Start PostgreSQL Database Container
        ExecuteProcess(
            cmd=[
                'powershell.exe', '-c',
                'cd C:\\Users\\semih\\Assessment\\1_ROS2\\ass_ros2_ws; docker-compose up -d postgres'
            ],
            name='start_postgres',
            output='screen'
        ),
        
        # 2. Wait and start ROS2 nodes
        TimerAction(
            period=10.0,  # Wait 10 seconds for database
            actions=[
                # Cijfer Calculator Service
                Node(
                    package='g1_ass1_pkg',
                    executable='cijfer_calculator',
                    name='cijfer_calculator',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0
                )
            ]
        ),
        
        # 3. Tentamen Result Generator
        TimerAction(
            period=13.0,
            actions=[
                Node(
                    package='g1_ass1_pkg',
                    executable='tentamen_result_generator',
                    name='tentamen_result_generator',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0
                )
            ]
        ),
        
        # 4. Final Cijfer Determinator
        TimerAction(
            period=16.0,
            actions=[
                Node(
                    package='g1_ass1_pkg',
                    executable='final_cijfer_determinator',
                    name='final_cijfer_determinator',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0
                )
            ]
        ),
        
        # 5. Herkansing Cijfer Determinator
        TimerAction(
            period=19.0,
            actions=[
                Node(
                    package='g1_ass1_pkg',
                    executable='herkansing_cijfer_determinator',
                    name='herkansing_cijfer_determinator',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0
                )
            ]
        ),
        
        # 6. Herkansing Scheduler
        TimerAction(
            period=22.0,
            actions=[
                Node(
                    package='g1_ass1_pkg',
                    executable='herkansing_scheduler',
                    name='herkansing_scheduler',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0
                )
            ]
        ),
        
        # 7. Database Status Monitor
        TimerAction(
            period=25.0,
            actions=[
                ExecuteProcess(
                    cmd=[
                        'bash', '-c',
                        'echo "🔍 Database Monitor Started - checking every 15 seconds" && ' +
                        'while true; do ' +
                        'echo "📊 $(date): Checking database..."; ' +
                        'powershell.exe -c "cd C:\\Users\\semih\\Assessment\\1_ROS2\\ass_ros2_ws; docker exec cijfer_generator_db psql -U cijfer_user -d cijfer_generator -c \\"SELECT COUNT(*) as completed_students FROM student_results WHERE final_result > 0;\\""; ' +
                        'sleep 15; done'
                    ],
                    name='database_monitor',
                    output='screen'
                )
            ]
        )
    ])
