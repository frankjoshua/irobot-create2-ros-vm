# iRobot create 2 simulation
Uses Vagrant and Ansible to create a virtual box with ROS and iRobot create 2 simulation

Just run
```bash
vagrant up
```
Uses Anisble for provisioning. In the /ansible dir
Make sure to update the ROS master URI in /ansible/production
Then run
```bash
vagrant provision
```