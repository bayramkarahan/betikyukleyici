#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt remove e-ag-client -y
apt remove e-ag-x11-client -y
apt remove nginx libnginx-mod-rtmp -y
apt install nginx libnginx-mod-rtmp -y
rm -rf /usr/share/e-ag
wget -O /tmp/e-ag.deb https://github.com/bayramkarahan/e-ag/raw/refs/heads/master/e-ag_2.3.0_amd64.deb
dpkg --force-all -i /tmp/e-ag.deb
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt --fix-broken install -y
apt autoremove -y
sleep 1
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/e-ag
exit 0
