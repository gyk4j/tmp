#!/bin/sh

# Reference: https://docs.docker.com/engine/install/ubuntu/
# Add Docker's official GPG key:
apt-get update
apt-get install -y ca-certificates curl
install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  tee /etc/apt/sources.list.d/docker.list > /dev/null
apt-get update

# Install networking tools
apt-get install -y net-tools smbclient

# Install Docker
apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
  
systemctl start docker
docker version

# Post-installation steps

# Manage Docker as a non-root user
groupadd docker
usermod -aG docker vagrant
newgrp docker

# Configure Docker to start on boot with systemd
systemctl enable docker.service
systemctl enable containerd.service

# Disable systemd-resolved on boot and use dnsmasq container instead
# systemctl stop systemd-resolved
# systemctl disable systemd-resolved

# Install required tools to update /etc/resolv.conf
# resolvconf  : resolvconf
# dnsutils    : nslookup and dig
apt-get install -y resolvconf dnsutils
systemctl enable resolvconf.service
systemctl start resolvconf.service
systemctl status resolvconf.service

# Set preferred DNS server (Cloudflare at the moment)
echo "nameserver 1.1.1.1" >> /etc/resolvconf/resolv.conf.d/head
resolvconf --enable-updates
resolvconf -u

# Verify if /etc/resolv.conf contains our new DNS server
grep "nameserver 1.1.1.1" /etc/resolv.conf

nslookup -q=mx gmail.com
dig gmail.com MX

