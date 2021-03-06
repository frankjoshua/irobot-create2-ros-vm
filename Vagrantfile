# -*- mode: ruby -*-
# vi: set ft=ruby :

# All Vagrant configuration is done below. The "2" in Vagrant.configure
# configures the configuration version (we support older styles for
# backwards compatibility). Please don't change it unless you know what
# you're doing.
Vagrant.configure("2") do |config|
  # The most common configuration options are documented and commented below.
  # For a complete reference, please see the online documentation at
  # https://docs.vagrantup.com.

  # Disable automatic box update checking. If you disable this, then
  # boxes will only be checked for updates when the user runs
  # `vagrant box outdated`. This is not recommended.
  # config.vm.box_check_update = false

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # NOTE: This will enable public access to the opened port
  # config.vm.network "forwarded_port", guest: 80, host: 8080

  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine and only allow access
  # via 127.0.0.1 to disable public access
  # config.vm.network "forwarded_port", guest: 80, host: 8080, host_ip: "127.0.0.1"

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  # config.vm.network "private_network", ip: "192.168.33.10"

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network "public_network"

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  
  
  # config.vm.define "firewall" do |firewall|
  #   firewall.vm.network "public_network"
  #   firewall.vm.network "public_network"
  #   firewall.vm.box = "ubuntu/xenial64"
  #   firewall.vm.synced_folder ".", "/vagrant", disabled: true
  #   firewall.vm.provider "virtualbox" do |vb|
  #     # Display the VirtualBox GUI when booting the machine
  #     vb.gui = true
  #     # Customize the amount of memory on the VM:
  #     vb.memory = "1024"
  #   end
  # end

  config.vm.define "server" do |server|
    server.vm.hostname = "server"
    server.vm.network :private_network, ip: "192.168.33.57"
    #port for uchiwa
    server.vm.network "forwarded_port", guest: 3000, host: 3000
    #sensu
    server.vm.network "forwarded_port", guest: 4567, host: 4567
    #graphite
    server.vm.network "forwarded_port", guest: 8088, host: 8088
    server.vm.network "forwarded_port", guest: 2003, host: 2003
    server.vm.network "forwarded_port", guest: 2004, host: 2004
    server.vm.network "forwarded_port", guest: 2023, host: 2023
    server.vm.network "forwarded_port", guest: 2024, host: 2024
    server.vm.network "forwarded_port", guest: 8125, host: 8125, protocol: "udp"
    server.vm.network "forwarded_port", guest: 8126, host: 8126
    #Base box with ubuntu 16.04 
    server.vm.box = "ubuntu/xenial64"
    server.vm.provider "virtualbox" do |vb|
      # Customize the amount of memory on the VM:
      vb.memory = "1024"
      vb.cpus = 2
    end
  end

  config.vm.define "workstation" do |workstation|
    workstation.vm.synced_folder "./catkin_ws", "/catkin_ws"
    workstation.vm.hostname = "workstation"
    workstation.vm.network "public_network", bridge: "enp3s0"
    workstation.vm.network :private_network, ip: "192.168.33.58"
    workstation.vm.provider "virtualbox" do |vb|
      # Display the VirtualBox GUI when booting the machine
      vb.gui = true
      # Customize the amount of memory on the VM:
      vb.memory = "4096"
      vb.cpus = 6
    end
    # Every Vagrant development environment requires a box. You can search for
    # boxes at https://vagrantcloud.com/search.
    workstation.vm.box = "ubuntu/trusty64"
    # Enable provisioning with a shell script. Additional provisioners such as
    # Puppet, Chef, Ansible, Salt, and Docker are also available. Please see the
    # documentation for more information about their specific syntax and use.
    workstation.vm.provision "shell", inline: <<-SHELL
      sudo apt-get update
      sudo apt-get install -y ubuntu-desktop
      SHELL
  end

  #
  # Run Ansible from the Vagrant Host
  #
  ENV['ANSIBLE_ROLES_PATH'] = ".vagrant/roles:./roles"
  ENV['ANISBLE_STDOUT_CALLBACK'] = "debug"
  config.vm.provision "ansible" do |ansible|
    ansible.galaxy_roles_path = '.vagrant/roles'
    ansible.galaxy_command = 'ansible-galaxy install --role-file=%{role_file} --roles-path=%{roles_path}'
    ansible.galaxy_role_file = 'ansible/requirements.yml'
    ansible.playbook = "ansible/playbook.yml"
    ansible.inventory_path = "ansible/production"
  end
end
