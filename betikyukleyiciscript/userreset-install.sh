#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
sleep 1
# Detect the name of the display in use
display=":$(ls /tmp/.X11-unix/* | sed 's#/tmp/.X11-unix/X##' | head -n 1)"
# Detect the user using such display	
user=$(who | grep '('$display')' | awk '{print $1}')	
cp -prfv /etc/skel/* /home/$user/
chown "${user}:${user}" -R /home/$user/

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/userreset
exit 0
