#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
apt install libnss3-tools -y
wget -O /tmp/chrome.deb https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
dpkg --force-all -i /tmp/chrome.deb
sleep 1

certutil -d sql:$HOME/.pki/nssdb -A -t "C,," -n "baymeb"  -i /usr/local/share/ca-certificates/MEB_SERTIFIKASI.crt 
rm /tmp/chrome.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/Google-Chrome
exit 0
