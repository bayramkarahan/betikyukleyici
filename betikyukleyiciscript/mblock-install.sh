#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/scratch.deb https://github.com/bayramkarahan/mBlock-desktop-linux/releases/download/v5.6.0/mblock-builder_5.6.0_amd64.deb
apt install /tmp/mblock.deb -y
sleep 1
rm /tmp/mblock.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/mblock
exit 0
