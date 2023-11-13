#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt autoremove -y
apt update
############################################################
wget -O /tmp/e-zil.deb https://github.com/bayramkarahan/e-zil/raw/master/e-zil_2.8.0_amd64.deb
dpkg --force-all -i /tmp/e-zil.deb
sleep 1
rm /tmp/e-zil.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/e-zil
exit 0
