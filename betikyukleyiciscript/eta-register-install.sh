#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/paket.deb http://19.depo.pardus.org.tr/etap/pool/main/e/eta-register/eta-register_0.9_amd64.deb
dpkg --force-all -i /tmp/paket.deb
sleep 1
rm /tmp/paket.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/eta-register
exit 0
