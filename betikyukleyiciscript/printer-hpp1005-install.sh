#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get remove hplip cups-filters cups hplip-data system-config-printer-udev -y
rm -rf /usr/share/hplip
apt-get install build-essential tix groff dc cups cups-filters system-config-printer hplip system-config-printer-common -y
sleep 1
/etc/init.d/cups restart
cd /tmp

git clone https://github.com/bayramkarahan/printer.git
cd printer/
make

make install
make install-hotplug
getweb p1005 # Get HP LaserJet P1005 firmware file

system-config-printer
tail /var/log/syslog

sleep 1
rm print*
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/hpp1005
exit 0
