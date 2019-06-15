#!/usr/bin/python
import subprocess
subprocess.call(["sudo sed -i 's/.*PasswordAuthentication no.*/PasswordAuthentication yes/' sshd_config"], shell=True)
subprocess.call(["sudo service ssh restart"], shell=True)
subprocess.call(["sleep 180"], shell=True)
subprocess.call(["sudo sed -i 's/.*PasswordAuthentication yes.*/PasswordAuthentication no/' sshd_config"], shell=True)
subprocess.call(["sudo service ssh restart"], shell=True)
