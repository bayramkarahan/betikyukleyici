#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/betik.deb https://github.com/bayramkarahan/betikyukleyici/raw/refs/heads/master/betikyukleyici_1.8.7_amd64.deb
apt install /tmp/betik.deb
sleep 1
rm /tmp/betik.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/betik
exit 0
