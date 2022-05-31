#!/bin/bash
wget -O /tmp/zoom.deb https://zoom.us/client/latest/zoom_amd64.deb
dpkg --force-all -i /tmp/zoom.deb
sleep 1
rm /tmp/zoom.deb
mkdir /var/lib/tinyinstaller
touch /var/lib/tinyinstaller/zoom
exit 0
