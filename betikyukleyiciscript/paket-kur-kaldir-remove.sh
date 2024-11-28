#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get install zenity -y
sleep 1

paketname=$(zenity --entry --title "Paket Kaldırma" --text "Kaldırılacak Paket Adını Giriniz")

if [ "$paketname" != "" ]; then
	dpkg -s "$paketname"
	if [ $? -ne 0 ]; then
		zenity --error --text="Paket Kurulu Değil.\n ${status}" --title="Error" --width=300 --width=200
		exit 1
	else
		apt remove "$paketname"
		zenity --info --text="$paketname Paketi Kaldırıldı." --width=300
	fi
fi

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/"$paketname"
exit 0
