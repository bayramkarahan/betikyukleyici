#!/bin/bash
wget -O /tmp/wps.deb https://depo.pardus.org.tr/etap/pool/non-free/w/wps-office/wps-office_10.1.0.6757pardus2_amd64.deb
dpkg --force-all -i /tmp/wps.deb
sleep 1
rm /tmp/wps.deb
mkdir /var/lib/tinyinstaller
touch /var/lib/tinyinstaller/wps
exit 0
