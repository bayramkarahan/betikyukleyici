#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
cd /tmp 
wget -O https://github.com/bayramkarahan/foxit/raw/refs/heads/master/foxit.run
chmod a+x foxit.run
./foxit.run

sleep 1

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/foxitreader
exit 0
