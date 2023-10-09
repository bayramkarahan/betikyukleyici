#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################

apt install system-config-printer -y
#cups install
apt install cups -y
/etc/init.d/cups restart
#tarayıcıda localhost:631
#tüm marka sürücüler yükleniyor
apt-get install printer-driver-* -y
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/printer
exit 0
