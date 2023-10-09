#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt install e-tahta
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/e-tahta
exit 0
