#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
############################################################
wget -O /tmp/paket.deb https://github.com/bayramkarahan/e-tahta/raw/master/e-tahta_1.8.8_amd64-debian.deb
dpkg --force-all -i /tmp/paket.deb
sleep 1
rm /tmp/paket.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/e-tahta
exit 0
