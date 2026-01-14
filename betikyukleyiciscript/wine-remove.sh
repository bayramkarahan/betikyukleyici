#!/bin/bash
sudo rm /var/lib/dpkg/lock-frontend
sudo rm /var/lib/dpkg/lock
sudo rm /var/cache/apt/archives/lock
sudo dpkg --configure -a
sudo apt -f install


apt remove winemimetype -y
rm -rf /var/lib/betikyukleyici/winemimetype
rm -rf /var/lib/betikyukleyici/wine
apt remove wine* -y
apt --purge remove wine* -y
apt autoremove -y
dpkg --add-architecture i386
exit 0
