#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################

sleep 1

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/update
exit 0
