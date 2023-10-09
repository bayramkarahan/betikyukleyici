#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/wps.deb https://depo.pardus.org.tr/etap/pool/non-free/w/wps-office/wps-office_10.1.0.6757pardus2_amd64.deb
dpkg --force-all -i /tmp/wps.deb
wget -O /tmp/wps-tr.deb https://github.com/bayramkarahan/wps-office-tr-dil/blob/master/wps-tr.deb
dpkg --force-all -i /tmp/wps-tr.deb
sleep 1
rm /tmp/wps.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/wpsOfis
exit 0
