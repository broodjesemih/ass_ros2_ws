#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, TimerAction
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition


def generate_launch_description():
    # Declare launch arguments
    use_sim_time_arg = DeclareLaunchArgument(
        'use_sim_time',
        default_value='false',
        description='Use simulation time if true'
    )
    
    log_level_arg = DeclareLaunchArgument(
        'log_level',
        default_value='info',
        description='Log level (debug, info, warn, error, fatal)'
    )

    # Get launch configurations
    use_sim_time = LaunchConfiguration('use_sim_time')
    log_level = LaunchConfiguration('log_level')

    # Define nodes
    tentamen_result_generator_node = Node(
        package='g1_ass1_pkg',
        executable='tentamen_result_generator',
        name='tentamen_result_generator',
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
        }],
        arguments=['--ros-args', '--log-level', log_level],
        respawn=True,
        respawn_delay=2.0
    )

    cijfer_calculator_node = Node(
        package='g1_ass1_pkg',
        executable='cijfer_calculator',
        name='cijfer_calculator',
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
        }],
        arguments=['--ros-args', '--log-level', log_level],
        respawn=True,
        respawn_delay=2.0
    )

    # Start final_cijfer_determinator after a short delay to ensure services are ready
    final_cijfer_determinator_node = TimerAction(
        period=3.0,
        actions=[
            Node(
                package='g1_ass1_pkg',
                executable='final_cijfer_determinator',
                name='final_cijfer_determinator',
                output='screen',
                parameters=[{
                    'use_sim_time': use_sim_time,
                }],
                arguments=['--ros-args', '--log-level', log_level],
                respawn=True,
                respawn_delay=2.0
            )
        ]
    )

    herkansing_scheduler_node = TimerAction(
        period=5.0,
        actions=[
            Node(
                package='g1_ass1_pkg',
                executable='herkansing_scheduler',
                name='herkansing_scheduler',
                output='screen',
                parameters=[{
                    'use_sim_time': use_sim_time,
                }],
                arguments=['--ros-args', '--log-level', log_level],
                respawn=True,
                respawn_delay=2.0
            )
        ]
    )

    herkansing_cijfer_determinator_node = TimerAction(
        period=4.0,
        actions=[
            Node(
                package='g1_ass1_pkg',
                executable='herkansing_cijfer_determinator',
                name='herkansing_cijfer_determinator',
                output='screen',
                parameters=[{
                    'use_sim_time': use_sim_time,
                }],
                arguments=['--ros-args', '--log-level', log_level],
                respawn=True,
                respawn_delay=2.0
            )
        ]
    )

    return LaunchDescription([
        # Launch arguments
        use_sim_time_arg,
        log_level_arg,
        
        # Core service nodes first
        cijfer_calculator_node,
        herkansing_cijfer_determinator_node,
        
        # Then client nodes with delays
        final_cijfer_determinator_node,
        herkansing_scheduler_node,
        
        # Generator node last
        TimerAction(
            period=2.0,
            actions=[tentamen_result_generator_node]
        ),
    ])
