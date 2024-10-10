#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/scratch.deb https://github.com/redshaderobotics/scratch3.0-linux/releases/download/3.3.0/scratch-desktop_3.3.0_amd64.deb
apt install /tmp/scratch.deb -y
sleep 1
rm /tmp/scratch.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/scratch
exit 0
