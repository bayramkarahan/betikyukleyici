#!/bin/bash

apt-get install zenity -y
sleep 1

apt remove rightclick -y

#glib-compile-schemas /usr/share/glib-2.0/schemas/
#dconf update

zenity --info --text="Ayarların geçerli olması için sistemi yeniden başlatınız veya oturumu kapatıp tekrar giriniz." --width=500

rm -rf /var/lib/betikyukleyici/rightclick
exit 0
