#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/e-kilit.deb https://github.com/bayramkarahan/e-kilit/raw/master/e-kilit_4.8.1_amd64.deb
dpkg --force-all -i /tmp/e-kilit.deb
sleep 1
rm /tmp/e-kilit.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/e-kilit
exit 0
