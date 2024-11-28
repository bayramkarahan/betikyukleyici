#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get install zenity -y
sleep 1

username=$(zenity --entry --title "Kullanıcı Adı" --text "Otomatik Giriş Yapılacak Kullanıcı Adını Giriniz")
echo "Girilen isim: $username"
if [ "$username" != "" ]; then
	id $username
	if [ $? -ne 0 ]; then
		zenity --error --text="Böyle Bir Kullanıcı Yok.\n ${status}" --title="Error" --width=300 --width=200
		exit 1
	else
		sed -i -e 's/autologin-user =/#autologin-user =/g' ./lightdm.conf
		sed -i -e 's/autologin-user=/#autologin-user =/g' ./lightdm.conf

		sed -i 's/\[Seat:\*\]/\[Seat:\*\]\nautologin-user=${username}/g' ./lightdm.conf
		zenity --info --text="$username Kullanıcısı ile Otomatik Giriş Ayarlandı." --width=400
	fi
fi

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/otomatikgiris
exit 0
