#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/e-ag.deb https://github.com/bayramkarahan/e-ag/raw/master/e-ag_2.1.0_amd64.deb
dpkg --force-all -i /tmp/e-ag.deb
sleep 1
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/e-ag
exit 0
