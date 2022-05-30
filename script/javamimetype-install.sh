#!/bin/bash
wget -O /tmp/javamimetype.deb https://github.com/bayramkarahan/javaplugin/raw/master/javamimetype.deb
dpkg --force-all -i /tmp/javamimetype.deb
sleep 1
rm /tmp/javamimetype.deb
mkdir /var/lib/tinyinstaller
touch /var/lib/tinyinstaller/javamimetype
exit 0
