#!/usr/bin/env python3

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, TimerAction, OpaqueFunction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import os
import time

def generate_launch_description():
    """
    Complete Launch File voor Cijfer Generator System
    - Start PostgreSQL database container
    - Wacht tot database ready is
    - Start alle ROS2 nodes met juiste timing
    - Configureer environment variabelen
    """
    
    return LaunchDescription([
        # Launch arguments
        DeclareLaunchArgument(
            'use_docker',
            default_value='true',
            description='Start PostgreSQL via Docker (true/false)'
        ),
        
        DeclareLaunchArgument(
            'db_host',
            default_value='10.255.255.254',  # Windows host IP voor WSL2
            description='PostgreSQL host address'
        ),
        
        DeclareLaunchArgument(
            'timeout',
            default_value='120',
            description='Maximum runtime in seconds'
        ),
        
        # 1. Start PostgreSQL Database Container
        ExecuteProcess(
            cmd=[
                'powershell.exe', '-c',
                'cd C:\\Users\\semih\\Assessment\\1_ROS2\\ass_ros2_ws; docker-compose up -d postgres'
            ],
            name='start_postgres',
            output='screen',
            shell=False
        ),
        
        # 2. Wait for database to be ready
        TimerAction(
            period=8.0,  # Wait 8 seconds for container startup
            actions=[
                ExecuteProcess(
                    cmd=[
                        'bash', '-c',
                        'echo "🔄 Waiting for PostgreSQL to be ready..." && ' +
                        'for i in {1..10}; do ' +
                        'if powershell.exe -c "cd C:\\Users\\semih\\Assessment\\1_ROS2\\ass_ros2_ws; docker exec cijfer_generator_db pg_isready -U cijfer_user"; then ' +
                        'echo "✅ PostgreSQL is ready!"; break; fi; ' +
                        'echo "⏳ Attempt $i/10..."; sleep 2; done'
                    ],
                    name='wait_for_db',
                    output='screen'
                )
            ]
        ),
        
        # 3. Set environment variables and start ROS2 nodes
        TimerAction(
            period=15.0,  # Start ROS2 nodes after 15 seconds
            actions=[
                # Cijfer Calculator Service (starts first)
                Node(
                    package='g1_ass1_pkg',
                    executable='cijfer_calculator',
                    name='cijfer_calculator',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0,
                    environment={
                        'POSTGRES_HOST': LaunchConfiguration('db_host'),
                        'POSTGRES_PORT': '5432',
                        'POSTGRES_DB': 'cijfer_generator',
                        'POSTGRES_USER': 'cijfer_user',
                        'POSTGRES_PASSWORD': 'cijfer_password'
                    }
                )
            ]
        ),
        
        # 4. Tentamen Result Generator (starts after calculator)
        TimerAction(
            period=18.0,
            actions=[
                Node(
                    package='g1_ass1_pkg',
                    executable='tentamen_result_generator',
                    name='tentamen_result_generator',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0,
                    environment={
                        'POSTGRES_HOST': LaunchConfiguration('db_host'),
                        'POSTGRES_PORT': '5432',
                        'POSTGRES_DB': 'cijfer_generator',
                        'POSTGRES_USER': 'cijfer_user',
                        'POSTGRES_PASSWORD': 'cijfer_password'
                    }
                )
            ]
        ),
        
        # 5. Final Cijfer Determinator (starts after tentamen generator)
        TimerAction(
            period=21.0,
            actions=[
                Node(
                    package='g1_ass1_pkg',
                    executable='final_cijfer_determinator',
                    name='final_cijfer_determinator',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0,
                    environment={
                        'POSTGRES_HOST': LaunchConfiguration('db_host'),
                        'POSTGRES_PORT': '5432',
                        'POSTGRES_DB': 'cijfer_generator',
                        'POSTGRES_USER': 'cijfer_user',
                        'POSTGRES_PASSWORD': 'cijfer_password'
                    }
                )
            ]
        ),
        
        # 6. Herkansing Cijfer Determinator (Action Server)
        TimerAction(
            period=24.0,
            actions=[
                Node(
                    package='g1_ass1_pkg',
                    executable='herkansing_cijfer_determinator',
                    name='herkansing_cijfer_determinator',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0,
                    environment={
                        'POSTGRES_HOST': LaunchConfiguration('db_host'),
                        'POSTGRES_PORT': '5432',
                        'POSTGRES_DB': 'cijfer_generator',
                        'POSTGRES_USER': 'cijfer_user',
                        'POSTGRES_PASSWORD': 'cijfer_password'
                    }
                )
            ]
        ),
        
        # 7. Herkansing Scheduler (starts last)
        TimerAction(
            period=27.0,
            actions=[
                Node(
                    package='g1_ass1_pkg',
                    executable='herkansing_scheduler',
                    name='herkansing_scheduler',
                    output='screen',
                    respawn=True,
                    respawn_delay=2.0,
                    environment={
                        'POSTGRES_HOST': LaunchConfiguration('db_host'),
                        'POSTGRES_PORT': '5432',
                        'POSTGRES_DB': 'cijfer_generator',
                        'POSTGRES_USER': 'cijfer_user',
                        'POSTGRES_PASSWORD': 'cijfer_password'
                    }
                )
            ]
        ),
        
        # 8. Database Monitor (Optional - shows live database updates)
        TimerAction(
            period=30.0,
            actions=[
                ExecuteProcess(
                    cmd=[
                        'bash', '-c',
                        'echo "🔍 Starting database monitor..." && ' +
                        'while true; do ' +
                        'echo "📊 Database Status - $(date)"; ' +
                        'powershell.exe -c "cd C:\\Users\\semih\\Assessment\\1_ROS2\\ass_ros2_ws; docker exec cijfer_generator_db psql -U cijfer_user -d cijfer_generator -c \\"SELECT student_name, course, final_result FROM student_results WHERE final_result > 0 ORDER BY timestamp DESC LIMIT 5;\\""; ' +
                        'echo ""; sleep 10; done'
                    ],
                    name='database_monitor',
                    output='screen'
                )
            ]
        ),
        
        # 9. Auto-shutdown after timeout (Optional)
        TimerAction(
            period=float(LaunchConfiguration('timeout').perform(None) if LaunchConfiguration('timeout').perform(None) else 120.0),
            actions=[
                ExecuteProcess(
                    cmd=['echo', '⏰ Launch timeout reached - system has been running for specified duration'],
                    name='timeout_notification',
                    output='screen'
                )
            ]
        )
    ])
