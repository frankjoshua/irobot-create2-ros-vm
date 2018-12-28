# iRobot create 2 simulation
Uses Vagrant and Ansible to create a virtual box with ROS and iRobot create 2 simulation

Launches to Virtual Machines<br>
workstation - Has ROS preinstalled with iRobot create 2 drivers<br>
server - Runs Sensu for monitoring the robot<br>
server:3000 - Uchiwa (user/pass admin/admin) Monitoring software<br>
server:8088 - Graphite (Graphs battery)<br>

# Quick start
Just run
```bash
vagrant up
```

# Uses Anisble for provisioning. 
In the /ansible dir<br>
Make sure to update the ROS master URI in /ansible/production<br>
Then run
```bash
vagrant provision
```
