#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get install zenity -y
sleep 1

username=$(zenity --entry --title "Kullanıcı Adı" --text "Silinecek Kullanıcı Adını Giriniz")
echo "Girilen isim: $username"
if [ "$username" != "" ]; then
	id $username
	if [ $? -ne 0 ]; then
		zenity --error --text="Böyle Bir Kullanıcı Yok.\n ${status}" --title="Error" --width=300 --width=200
		exit 1
	else
		userdel ${username}
		rm -r /home/${username}
		zenity --info --text="$username Kullanıcısı Silindi." --width=300
		exit 1
	fi
fi



exit 0
