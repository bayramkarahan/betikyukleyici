#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/app.deb https://github.com/bayramkarahan/betikyukleyici/raw/master/deb/espr/1-epson-inkjet-printer-201601w_1.0.0-1lsb3.2_amd64.deb
dpkg --force-all -i /tmp/app.deb

wget -O /tmp/app.deb https://github.com/bayramkarahan/betikyukleyici/raw/master/deb/espr/2-epson-inkjet-printer-201601w_1.0.1-1_amd64.deb
dpkg --force-all -i /tmp/app.deb

wget -O /tmp/app.deb https://github.com/bayramkarahan/betikyukleyici/raw/master/deb/espr/epson_inkjet_printer_escpr_1_8_5_1_amd64_apt_install_libcupsimage2.deb
dpkg --force-all -i /tmp/app.deb

wget -O /tmp/app.deb https://github.com/bayramkarahan/betikyukleyici/raw/master/deb/espr/epson_printer_utility_1_1_3_1_amd64_apt_install_libqt5widgets5.deb
dpkg --force-all -i /tmp/app.deb

wget -O /tmp/app.deb https://github.com/bayramkarahan/betikyukleyici/raw/master/deb/espr/lsb-compat_9.20161125_amd64.deb
dpkg --force-all -i /tmp/app.deb

apt install printer-driver-escpr 


sleep 1
rm /tmp/app.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/epson
exit 0
