#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
apt install opera-stable -y
sleep 1

rm /tmp/app.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/opera
exit 0
