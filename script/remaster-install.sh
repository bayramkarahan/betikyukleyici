#!/bin/bash
wget -O /tmp/winemimetype.deb https://github.com/bayramkarahan/tinyinstaller/raw/master/deb/pardus-remaster_0.1.0_all.deb
dpkg --force-all -i /tmp/remaster.deb
sleep 1
rm /tmp/remaster.deb
mkdir /var/lib/tinyinstaller
touch /var/lib/tinyinstaller/remaster
exit 0
