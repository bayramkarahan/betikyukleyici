#!/bin/bash

wget -O /tmp/firefox.tar.bz2 "https://download.mozilla.org/?product=firefox-latest-ssl&os=linux64&lang=tr"

tar -xvf /tmp/firefox.tar.bz2 -C /etc/skel/
rm -rf /etc/skel/.firefox
mv /etc/skel/firefox /etc/skel/.firefox

for item in $(ls /home)
do
rm -rf /home/$item/.firefox
cp -R  /etc/skel/.firefox /home/$item/.firefox
chown -R $item:$item  /home/$item/.firefox
chmod -R 755 /home/$item/.firefox
done


apt install libdbus-glib-1-2 -y
sleep 1

certificateFile="/tmp/fatih.pem"
certificateName="fatihby" 
#/usr/local/share/ca-certificates
wget http://sertifika.meb.gov.tr/MEB_SERTIFIKASI.cer -O /tmp/MEB_SERTIFIKASI.cer
openssl x509 -inform DER -in /tmp/MEB_SERTIFIKASI.cer -out /tmp/MEB_SERTIFIKASI.crt
openssl x509 -in /tmp/MEB_SERTIFIKASI.crt -out /tmp/fatih.pem -outform PEM

######################profil kopyalanır#######################
for item in $(ls /etc/skel/.mozilla/firefox)
do
if [[ -f /etc/skel/.mozilla/firefox/$item/cert9.db ]] ; then 
	for userhome in $(ls /home)
	do
		#echo $userhome
		cp -R /etc/skel/.mozilla/firefox/$item /home/$userhome/.mozilla/firefox/myprofil
		chown -R $userhome:$userhome  /home/$userhome/.mozilla/firefox/myprofil
		#chgrp -R $userhome
		chmod -R 755 /home/$userhome/.mozilla/firefox/myprofil
	done
fi
done
######################sertifika yükleniyor#######################


for item in $(ls /home)
do
	for certDB in $(find  /home/$item/.mozilla* -name "cert9.db")
	do
	  certDir=$(dirname ${certDB});
	  #log "mozilla certificate" "install '${certificateName}' in ${certDir}"
	  certutil -A -n "${certificateName}" -t "TCu,Cuw,Tuw" -i ${certificateFile} -d sql:${certDir}
	done

done

#######################desktop file#####################################
rm -rf /usr/share/applications/tarayici.desktop

cat > /usr/share/applications/tarayici.desktop << EOF
[Desktop Entry]
Version=1.0
Name=Browser Application
Name[tr]=Web Tarayıcısı1
Type=Application
Comment=Web Browser Application
Comment[tr]=Web Tarayıcısı Uygulaması
Terminal=false
Exec=sh -c "env MOZ_USE_XINPUT2=1 \$HOME/.firefox/firefox -profile "\$HOME/.mozilla/firefox/myprofil" %u"
Icon=tarayici
Categories=Network;WebBrowser;
Keywords=internet;web;browser;chrome;firefox;
GenericName=Tarayici
EOF


mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/firefox
exit 0
