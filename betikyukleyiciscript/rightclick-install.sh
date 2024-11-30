#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get install zenity -y
sleep 1

zaman=$(zenity --entry --title "Sağtuş Değeri" --text "Sağtuş Bekeleme Süresini Giriniz"  --entry-text "1.0")


gsettings set org.gnome.desktop.a11y.mouse secondary-click-enabled true
gsettings set org.gnome.desktop.a11y.mouse secondary-click-time "${zaman}"

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/rightclick
exit 0

