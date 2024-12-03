#!/bin/bash

apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update

apt-get install zenity -y
sleep 1

############################################################
wget -O /tmp/app.deb https://github.com/bayramkarahan/rightclick-evdev-emulation/releases/download/current/rightclick_1.0_amd64.deb
dpkg --force-all -i /tmp/app.deb
sleep 1
rm /tmp/app.deb

#glib-compile-schemas /usr/share/glib-2.0/schemas/
#dconf update


zenity --info --text="Ayarların geçerli olması için sistemi yeniden başlatınız veya oturumu kapatıp tekrar giriniz." --width=500

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/rightclick
exit 0

