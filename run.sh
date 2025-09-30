#!/bin/bash
# Run all g1_ass1_pkg nodes in a tmux session

SESSION="g1_ass1_pkg_test"

# Kill old session if exists
tmux kill-session -t $SESSION 2>/dev/null

# Pane 1: tentamen_result_generator
tmux new-session -d -s $SESSION \
    "bash -i -c 'source install/setup.bash && ros2 run g1_ass1_pkg tentamen_result_generator; exec bash'"

# Pane 2: cijfer_calculator
tmux split-window -h \
    "bash -i -c 'source install/setup.bash && ros2 run g1_ass1_pkg cijfer_calculator; exec bash'"

# Pane 3: final_cijfer_determinator
tmux split-window -v \
    "bash -i -c 'source install/setup.bash && ros2 run g1_ass1_pkg final_cijfer_determinator; exec bash'"

# Pane 4: herkansing_scheduler
tmux split-window -v \
    "bash -i -c 'source install/setup.bash && ros2 run g1_ass1_pkg herkansing_scheduler; exec bash'"

# Pane 5: herkansing_cijfer_determinator
tmux split-window -v \
    "bash -i -c 'source install/setup.bash && ros2 run g1_ass1_pkg herkansing_cijfer_determinator; exec bash'"

# Balance panes
tmux select-layout tiled

# Attach to session
tmux attach -t $SESSION
