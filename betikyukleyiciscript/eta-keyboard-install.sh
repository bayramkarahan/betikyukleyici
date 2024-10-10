#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/eta-keyboard.deb https://github.com/bayramkarahan/betikyukleyici/raw/master/deb/eta-keyboard_1.0.6_amd64.deb
dpkg --force-all -i /tmp/eta-keyboard.deb
sleep 1
rm /tmp/eta-keyboard.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/eta-keyboard
exit 0
