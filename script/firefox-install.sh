#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O chroot/tmp/firefox.tar.bz2 "https://download.mozilla.org/?product=firefox-latest-ssl&os=linux64&lang=tr"
tar -xvf chroot/tmp/firefox.tar.bz2 -C chroot/etc/skel/
mv /etc/skel/firefox chroot/etc/skel/.firefox
apt install libdbus-glib-1-2 -y

sleep 1
rm /tmp/firefox.tar.bz2

#####################################################
certificateFile="/tmp/fatih.pem"
certificateName="fatihby" 
#/usr/local/share/ca-certificates
wget http://sertifika.meb.gov.tr/MEB_SERTIFIKASI.cer -O /tmp/MEB_SERTIFIKASI.cer
openssl x509 -inform DER -in /tmp/MEB_SERTIFIKASI.cer -out /tmp/MEB_SERTIFIKASI.crt
openssl x509 -in /tmp/MEB_SERTIFIKASI.crt -out /tmp/fatih.pem -outform PEM

for certDB in $(find  ~/.mozilla* -name "cert9.db")
do
  certDir=$(dirname ${certDB});
  #log "mozilla certificate" "install '${certificateName}' in ${certDir}"
  certutil -A -n "${certificateName}" -t "TCu,Cuw,Tuw" -i ${certificateFile} -d sql:${certDir}
done

######################################################3
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/firefox
exit 0
