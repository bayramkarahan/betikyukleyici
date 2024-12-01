#!/bin/bash

apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update

############################################################
wget -O /tmp/app.deb https://github.com/bayramkarahan/betikyukleyici/raw/refs/heads/master/deb/smartboard_1.1_amd64.deb
dpkg --force-all -i /tmp/app.deb
sleep 1
rm /tmp/app.deb

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/smartboard
exit 0

