#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt autoremove -y
apt update
############################################################
wget -O /tmp/yuzuncuyil.deb http://depo.pardus.org.tr/pardus/pool/main/p/pardus-yuzyil/pardus-yuzyil_1.0.0_all.deb
dpkg --force-all -i /tmp/yuzuncuyil.deb
sleep 1
rm -rf /tmp/yuzuncuyil.deb
apt remove setwallpaper -y

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/yuzuncuyil
exit 0
