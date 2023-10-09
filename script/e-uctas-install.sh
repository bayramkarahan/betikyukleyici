#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/e-uctas.deb https://github.com/bayramkarahan/e-uctas/raw/master/e-uctas_1.0.0_amd64.deb
dpkg --force-all -i /tmp/e-uctas.deb
sleep 1
rm /tmp/e-uctas.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/e-uctas
exit 0
