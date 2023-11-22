#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/wps.deb https://wdl1.pcfg.cache.wpscdn.com/wpsdl/wpsoffice/download/linux/11708/wps-office_11.1.0.11708.XA_amd64.deb
dpkg --force-all -i /tmp/wps.deb
wget -O /tmp/wps-tr.deb https://github.com/bayramkarahan/wps-office-tr-dil/blob/master/wps-tr.deb
dpkg --force-all -i /tmp/wps-tr.deb
sleep 1
rm /tmp/wps.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/wpsOfis
exit 0
