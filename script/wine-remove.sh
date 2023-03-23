#!/bin/bash
apt remove winemimetype -y
rm -rf /var/lib/betikyukleyici/winemimetype
rm -rf /var/lib/betikyukleyici/wine
apt remove wine* -y
apt --purge remove wine* -y
apt autoremove -y
dpkg --add-architecture i386
exit 0
