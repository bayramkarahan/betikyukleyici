#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt install libre* -y
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/LibreOfis
exit 0
