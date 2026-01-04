#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
# Gerekli paketler
apt-get install -y \
  openssl \
  ca-certificates \
  libnss3-tools

# sertifika install
wget http://sertifika.meb.gov.tr/MEB_SERTIFIKASI.cer -O /tmp/MEB_SERTIFIKASI.cer
cp /tmp/MEB_SERTIFIKASI.cer /usr/local/share/ca-certificates/MEB_SERTIFIKASI.cer

# Sertifikayı DER → PEM çevir
openssl x509 -inform DER \
  -in /usr/local/share/ca-certificates/MEB_SERTIFIKASI.cer \
  -out /usr/local/share/ca-certificates/MEB_SERTIFIKASI.crt

### tüm sistem görmesi için
cp /usr/local/share/ca-certificates/MEB_SERTIFIKASI.crt /usr/share/ca-certificates/
update-ca-certificates


wget -O /tmp/chrome.deb https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
dpkg --force-all -i /tmp/chrome.deb
sleep 1

for u in /home/*; do
  user=$(basename "$u")
  NSSDB="$u/.pki/nssdb"

  sudo -u "$user" mkdir -p "$NSSDB"

  pwfile=$(mktemp)
  echo "" > "$pwfile"

  sudo -u "$user" certutil \
    -d sql:"$NSSDB" \
    -N \
    -f "$pwfile" 2>/dev/null || true

  sudo -u "$user" certutil \
    -d sql:"$NSSDB" \
    -A -t "C,," \
    -n "baymeb" \
    -i /usr/local/share/ca-certificates/MEB_SERTIFIKASI.crt

  rm -f "$pwfile"
done


rm /tmp/chrome.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/Google-Chrome
exit 0
