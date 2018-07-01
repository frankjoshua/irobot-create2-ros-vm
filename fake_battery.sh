#!/bin/bash

if [ -z ${BATTERY+x} ];
then
  echo "Setting battery"
  export BATTERY=100.0
fi

while true; do
#Drain the battery
DRAIN=0.0$(expr $RANDOM)
echo $BATTERY
BATTERY=$(bc <<< "$BATTERY - $DRAIN")
echo $DRAIN
echo $BATTERY
#Publish the result
rostopic pub /battery/charge_ratio std_msgs/Float32 "data: $BATTERY" -1
done
