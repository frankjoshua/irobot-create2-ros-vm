#!/bin/bash

#Setup ROS enviroment for the check to run
export ROS_MASTER_URI=$2
source /opt/ros/$1/setup.bash
#Change log directory to a writable one
export ROS_LOG_DIR=/var/log/sensu
#Set a small timeout and echo the ROS topic
#grep -Eo [0-9][0-9].*
RESULT=`timeout 2 rostopic echo -n 1 $3` 
if [ $? -ne 0 ];
then
echo $RESULT
exit 2
fi
echo $3 `echo $RESULT | grep -Eo '[0-9]{1,}.[0-9]*'` -1
exit 0
