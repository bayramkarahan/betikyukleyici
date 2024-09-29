#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
rm -rf /opt/windows/*
sleep 1
cd /tmp
rm -rf /opt/windows/*
chown root:root /opt/windows
ver=$(wine --version|cut -d '-' -f2)
echo $ver
wget "https://dl.winehq.org/wine/wine-mono/${ver}.0/wine-mono-${ver}.0-x86.msi"
WINEPREFIX=/opt/windows wine64 msiexec /i "wine-mono-${ver}.0-x86.msi"
sleep 1

display=":$(ls /tmp/.X11-unix/* | sed 's#/tmp/.X11-unix/X##' | head -n 1)"      #Detect the name of the display in use
user=$(who | grep '('$display')' | awk '{print $1}')    #Detect the user using such display
chown ${user}:${user} /opt/windows
touch /var/lib/betikyukleyici/ilkhazirlikwine
exit 0
