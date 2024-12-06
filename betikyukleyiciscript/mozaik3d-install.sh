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
cd /tmp
wget -d --header="User-Agent: Mozilla/5.0 (Windows NT 6.0) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.97 Safari/537.11" https://download.mozaweb.com/m3dviewer/m3dViewer_2.0.633_x64.tar.gz

tar -xf m3dViewer_2.0.633_x64.tar.gz
sleep 1
rm -rf /tmp/m3dViewer_2.0.633_x64.tar.gz

cp -prfv /tmp/opt /
cp -prfv /tmp/usr /

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/mozaik3d
exit 0
