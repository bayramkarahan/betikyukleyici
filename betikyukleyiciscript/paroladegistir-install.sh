#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get install zenity -y
sleep 1

username=$(zenity --entry --title "User Info" --text "Parolasını Değiştireceğiniz Kullanıcıyı Adını Giriniz")
echo "Girilen isim: $username"
p1=$(zenity --entry --title "User Info" --text "Yeni Parolayı Giriniz")
p2=$(zenity --entry --title "User Info" --text "Yeni Parolayı Tekrar Giriniz")

if [ "${p1}" == "${p2}" ]
then
 status=$(echo -e "${p1}\n${p2}\n" | passwd $username  2>&1 >/dev/null)

    if [ $? -ne 0 ]; then
        zenity --error --text="Hata:\n ${status}" --title="Error" --width=300 --width=200
        exit 1
        else
        zenity --info --text="Parola Başarıyla  Güncellendi." --width=300
    fi
else
zenity --error --text="Yeni Girilen Parolalar Faklı" --title="Error" --width=300 --width=200
fi

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/paroladegistir
exit 0
