#!/bin/bash
wget -O /tmp/winemimetype.deb https://github.com/bayramkarahan/wineplugin/raw/master/winemimetype.deb
dpkg --force-all -i /tmp/winemimetype.deb
sleep 1
rm /tmp/winemimetype.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/winemimetype

#### install wine

apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.

apt --purge remove wine* -y
apt autoremove -y
dpkg --add-architecture i386
apt update
wget -nc https://dl.winehq.org/wine-builds/winehq.key &&  apt-key add winehq.key
echo "deb https://dl.winehq.org/wine-builds/debian/ buster main" | tee /etc/apt/sources.list.d/winehq.list

apt update
apt -y install gnupg2 software-properties-common
apt update

apt install --install-recommends winehq-stable -y
apt --purge remove wine32:i386 libwine libwine:i386 fonts-wine -y
apt update
dpkg-reconfigure wine-stable-amd64 wine-stable wine-stable-i386 -y

apt-get install libgtk3-nocsd0:i386 -y
apt autoremove -y
apt autoclean -y

rm -rf /etc/apt/sources.list.d/winehq.list
touch /var/lib/betikyukleyici/wine7.0
exit 0
