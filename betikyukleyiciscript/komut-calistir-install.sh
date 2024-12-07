#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
apt-get install zenity -y
sleep 1

komut=$(zenity --entry --title "Komut Çalıştırıcı" --text "Çalıştırılacak Komutu Giriniz"  --width=300)
echo "Girilen isim: $komut"
if [ "$komut" != "" ]; then
	sonuc=$(sh -c "env DISPLAY=$DISPLAY XAUTHORITY=$XAUTHORITY  $komut")
	
		zenity --info --text="Komut Çalıştırıldı. \n ${sonuc}" --width=400
fi

mkdir /var/lib/betikyukleyici
exit 0
