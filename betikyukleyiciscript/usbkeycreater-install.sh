#!/bin/bash
set -e
export DEBIAN_FRONTEND=noninteractive
# ---- Paket sistemi toparlama ----
dpkg --configure -a || true
apt install -f -y || true
apt install --fix-missing -y || true
apt --fix-broken install -y || true
packagename="usbkeycreaterusers"
############################################################
wget O /tmp/${packagename}.deb https://github.com/bayramkarahan/usbkeycreaterusers/raw/refs/heads/master/usbkeycreaterusers_1.7.0_amd64.deb
cd /tmp
apt install ./${packagename}.deb --reinstall -y || true
rm -f /tmp/${packagename}.deb || true

apt install -f -y || true
apt --fix-broken install -y || true
apt autoremove -y || true

sleep 1
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/${packagename}
exit 0

