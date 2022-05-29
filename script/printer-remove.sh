#!/bin/bash
apt-get remove printer-driver-all-enforce printer-driver-all -y
apt-get install printer-driver-* -y
apt install cups
/etc/init.d/cups restart
exit 0