#!/bin/bash
wget -O /tmp/javamimetype.deb https://github.com/bayramkarahan/javaplugin/raw/master/javamimetype.deb
dpkg --force-all -i /tmp/javamimetype.deb
sleep 1
rm /tmp/javamimetype.deb
exit 0