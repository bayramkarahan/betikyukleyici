#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
rm -rf /opt/windows/*
sleep 1
cd /tmp
ver=$(wine --version|cut -d '-' -f2)
echo $ver
wget "https://dl.winehq.org/wine/wine-mono/${ver}.0/wine-mono-${ver}.0-x86.msi"
wine msiexec /i "wine-mono-${ver}.0-x86.msi"
sleep 1

touch /var/lib/betikyukleyici/ilkhazirlikwine
exit 0
