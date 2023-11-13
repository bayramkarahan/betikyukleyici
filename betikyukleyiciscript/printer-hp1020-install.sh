#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt --fix-broken install -y
apt-get install -f -y 
apt autoremove -y
apt install system-config-printer -y
#cups install
apt install cups -y
/etc/init.d/cups restart
#tarayıcıda localhost:631
#tüm marka sürücüler yükleniyor
apt-get install printer-driver-* -y
sleep 1
apt install hplip -y
sleep 1
getweb 1020 # Get HP LaserJet 1020 firmware file
sleep 1
cd /tmp
git clone https://github.com/bayramkarahan/printer.git
cd printer/
make
make install
sleep 1
rm print*

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/hp1020
exit 0
