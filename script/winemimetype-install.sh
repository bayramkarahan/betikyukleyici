#!/bin/bash
wget -O /tmp/winemimetype.deb https://github.com/bayramkarahan/wineplugin/raw/master/winemimetype.deb
dpkg --force-all -i /tmp/winemimetype.deb
sleep 1
rm /tmp/winemimetype.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/winemimetype
exit 0
