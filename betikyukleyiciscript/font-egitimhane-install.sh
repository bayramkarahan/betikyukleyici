#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/app.deb https://github.com/bayramkarahan/fonts/raw/refs/heads/master/diktemelabc.deb
dpkg --force-all -i /tmp/app.deb
sleep 1
rm /tmp/app.deb
sleep 1

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/diktemelabc
exit 0
