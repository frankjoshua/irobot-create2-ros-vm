# iRobot create 2 simulation
Uses Vagrant and Ansible to create a virtual box with ROS and iRobot create 2 simulation

Launches to Virtual Machines
workstation - Has ROS preinstalled with iRobot create 2 drivers
server - Runs Sensu for monitoring the robot
server:3000 - Uchiwa (user/pass admin/admin) Monitoring software
server:8088 - Graphite (Graphs battery)

#Quick start
Just run
```bash
vagrant up
```

# Uses Anisble for provisioning. 
In the /ansible dir
Make sure to update the ROS master URI in /ansible/production
Then run
```bash
vagrant provision
```