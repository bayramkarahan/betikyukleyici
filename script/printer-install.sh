#!/bin/bash
apt-get update
apt-get install printer-driver-all-enforce printer-driver-all -y
apt-get update
apt-get install printer-driver-* -y
apt install cups -y
/etc/init.d/cups restart
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/printer
exit 0
