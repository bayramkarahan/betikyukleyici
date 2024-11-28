#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get install zenity -y
sleep 1

username=$(zenity --entry --title "Kullanıcı Adı" --text "Eklenecek Kullanıcıyı Adını Giriniz")
echo "Girilen isim: $username"
p1=$(zenity --entry --title "User Info" --text "Yeni Parolayı Giriniz")
p2=$(zenity --entry --title "User Info" --text "Yeni Parolayı Tekrar Giriniz")

if [ "$username" != "" ]; then
	id $username
	if [ $? -ne 0 ]; then
	#kullanıcı yok ekleniyor
		if [ "${p1}" == "${p2}" ]
		then
			useradd -m ${username} -s /bin/bash -p $(openssl passwd ${p1}) -U -d /home/${username}
			zenity --info --text="Kullanıcı Başarıyla  Eklendi." --width=300
		else
			zenity --error --text="Yeni Girilen Parolalar Faklı" --title="Error" --width=300 --width=200
			exit 1
		fi

	else
		zenity --info --text="$username Kullanıcısı Sistemde Var." --width=300
		exit 1
	fi
fi


exit 0
