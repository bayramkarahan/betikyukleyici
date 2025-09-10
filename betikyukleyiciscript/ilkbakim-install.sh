#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
rm -rf /etc/apt/sources.list.d/*
rm -rf /etc/apt/sources.list
echo "deb https://deb.debian.org/debian stable main contrib non-free non-free-firmware" | sudo tee -a /etc/apt/sources.list
echo "deb https://depo.pardus.org.tr/pardus yirmiuc main contrib non-free" | sudo tee -a /etc/apt/sources.list


rm -r /var/lib/dpkg/lock*
dpkg --configure -a
apt-get install -f -y
apt-get update
#apt-get upgrade -y
#apt-get full-upgrade -y
apt-get autoremove -y
 apt-get autoclean -y

sleep 1

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/ilkbakim
exit 0
