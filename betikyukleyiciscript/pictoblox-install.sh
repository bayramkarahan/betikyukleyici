#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/pictoblox.deb https://download.pictoblox.ai/V7.1.0/PictoBlox_V7.1.0_linux_amd64.deb
apt install /tmp/pictoblox.deb -y
sleep 1
rm /tmp/pictoblox.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/pictoblox
exit 0
