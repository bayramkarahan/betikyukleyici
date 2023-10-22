#!/bin/bash
#merhaba bu flash ekleme betiği
#flash dosyaları oynatır.

apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt autoremove -y
apt update
############################################################
wget -O /tmp/flashplayer.deb https://github.com/bayramkarahan/flashplayerplugin/raw/master/flashplayer.deb
dpkg --force-all -i /tmp/flashplayer.deb
sleep 1
rm /tmp/flashplayer.deb


mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/flashplayer
exit 0
