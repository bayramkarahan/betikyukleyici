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
wget -O /tmp/setwallpaper.deb https://github.com/bayramkarahan/setwallpaper/raw/master/setwallpaper.deb
dpkg --force-all -i /tmp/setwallpaper.deb
sleep 1
rm /tmp/setwallpaper.deb


mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/setwallpaper
exit 0
