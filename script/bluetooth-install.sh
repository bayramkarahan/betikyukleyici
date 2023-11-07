#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################


apt-get install blueman bluetooth bluez bluez-tools rfkill pulseaudio-module-bluetooth -y
#rfkill list
rfkill unblock bluetooth
systemctl start bluetooth
pactl load-module module-bluetooth-discover

sleep 1

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/bluetooth
exit 0
