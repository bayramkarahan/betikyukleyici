#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt autoremove -y
apt update
############################################################
wget -O /tmp/googleearth.deb https://dl.google.com/dl/earth/client/current/google-earth-pro-stable_current_amd64.deb
dpkg --force-all -i /tmp/googleearth.deb
sleep 1
rm /tmp/googleearth.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/Googleearth
exit 0
