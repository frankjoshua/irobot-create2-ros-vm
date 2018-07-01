#!/bin/bash

#Setup ROS enviroment for the check to run
source /opt/ros/indigo/setup.bash
#Change log directory to a writable one
export ROS_LOG_DIR=/var/log/sensu
#Set a small timeout and echo the ROS topic
timeout 2 rostopic echo -n 1 $1 || exit 2