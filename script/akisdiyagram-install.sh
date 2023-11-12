#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/paket.deb https://github.com/bayramkarahan/akisdiyagram/raw/master/akisdiyagram_1.3_amd64.deb
dpkg --force-all -i /tmp/paket.deb
sleep 1
rm /tmp/paket.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/akisdiyagram
exit 0
