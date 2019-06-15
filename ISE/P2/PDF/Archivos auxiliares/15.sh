#!/bin/bash/
sed -i 's/.*PasswordAuthentication no.*/PasswordAuthentication yes/' /etc/ssh/sshd_config
service ssh restart
sleep 180
sed -i 's/.*PasswordAuthentication yes.*/PasswordAuthentication no/' /etc/ssh/sshd_config
service ssh restart
