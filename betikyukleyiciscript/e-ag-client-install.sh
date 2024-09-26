#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/e-ag-client.deb https://github.com/bayramkarahan/e-ag-client/raw/refs/heads/master/e-ag-client_2.2.0_amd64-new.deb
dpkg --force-all -i /tmp/e-ag-client.deb
sleep 1

sleep 1
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/e-ag-client
exit 0
