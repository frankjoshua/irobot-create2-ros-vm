#!/bin/bash

source /opt/ros/indigo/setup.bash
timeout 2 rostopic echo -n 1 $1 || exit 2