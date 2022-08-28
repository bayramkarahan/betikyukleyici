#!/bin/bash
wget -O /tmp/winemimetype.deb https://github.com/bayramkarahan/betikyukleyici/raw/master/deb/pardus-remaster_0.1.0_all.deb
dpkg --force-all -i /tmp/remaster.deb
sleep 1
rm /tmp/remaster.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/remasterImaj
exit 0
