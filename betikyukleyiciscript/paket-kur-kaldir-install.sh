#!/bin/bash
zenity --info --text="merhaba." --width=400
exit


apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get install zenity -y
sleep 1

paketname=$(zenity --entry --title "Paket Kurma" --text "Kurulacak Paket Adını Giriniz")

if [ "$paketname" != "" ]; then
	dpkg -s "$paketname"
	if [ $? -ne 0 ]; then
		zenity --error --text="Böyle Bir Paket Yok.\n ${status}" --title="Error" --width=300 --width=200
		exit 1
	else
		apt install "$paketname"
		zenity --info --text="$paketname Paketi Kuruldu." --width=400
	fi
fi

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/"$paketname"
exit 0
