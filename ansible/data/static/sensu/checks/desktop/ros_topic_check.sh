#!/bin/bash

#Setup ROS enviroment for the check to run
export ROS_MASTER_URI=http://black-pearl.local:11311
source /opt/ros/indigo/setup.bash
#Change log directory to a writable one
export ROS_LOG_DIR=/var/log/sensu
#Set a small timeout and echo the ROS topic
#grep -Eo [0-9][0-9].*
RESULT=`timeout 2 rostopic echo -n 1 $1` 
if [ $? -ne 0 ];
then
echo $RESULT
exit 2
fi
echo $1 `echo $RESULT | grep -Eo 0.[0-9]*` -1
exit 0
