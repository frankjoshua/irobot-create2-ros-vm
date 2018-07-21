#!/bin/bash

export ROS_MASTER_URI=$1
source /opt/ros/$2/setup.bash
rostopic list || exit 2