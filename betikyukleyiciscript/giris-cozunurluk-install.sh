#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get install zenity -y
sleep 1

olcek=$(zenity --entry --title "Ekran Ölçekleme" --text "Giriş Ekranınına Ölçek Giriniz\nFaz1=1.5\nFaz2=1.5\nFaz3=2")

if [ "$olcek" != "" ]; then

	sed -i '/scale/d' /usr/share/pardus/pardus-lightdm-greeter/data/config.ini
	sed -i "s/\[pardus\]/\[pardus\]\nscale=${olcek}/g" /usr/share/pardus/pardus-lightdm-greeter/data/config.ini		
	zenity --info --text="Ölçekleme Ayarlandı." --width=400

fi

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/giriscozunurluk
exit 0
