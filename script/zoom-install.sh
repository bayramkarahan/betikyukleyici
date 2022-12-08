#!/bin/bash
wget -O /tmp/zoom.deb https://zoom.us/client/5.12.9.367/zoom_amd64.deb
dpkg --force-all -i /tmp/zoom.deb
sleep 1
rm /tmp/zoom.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/zoom
exit 0
