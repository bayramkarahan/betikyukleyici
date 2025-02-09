#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
#*******************************************************************************************
# paket yönetim paketi add-apt-repository bu paketten gelir
apt install software-properties-common -y
# şifreleme ve dijital imzalama aracıdır.
apt install gnupg2 -y
# Bu komut, sisteminize 32-bit (i386) mimarisini ekler
dpkg --add-architecture i386

#genel wine keyi ekleniyor
wget -O /tmp/winehq.key https://dl.winehq.org/wine-builds/winehq.key
apt-key add /tmp/winehq.key

#key ekleniyor
mkdir -pm755 /etc/apt/keyrings
rm -rf /etc/apt/keyrings/winehq*
wget -O - https://dl.winehq.org/wine-builds/winehq.key | sudo gpg --dearmor -o /etc/apt/keyrings/winehq-archive.key -
#repostory ekleniyor
echo 'deb https://dl.winehq.org/wine-builds/debian/ bookworm main'> /etc/apt/sources.list.d/winehq.list
apt update
apt install winehq-stable=9.0.0.0~bookworm-1 wine-stable=9.0.0.0~bookworm-1 wine-stable-amd64=9.0.0.0~bookworm-1 wine-stable-i386=9.0.0.0~bookworm-1 -y

#Windows uygulamalarının (DLL dosyaları vb.) otomatik olarak indirip kurabilir
apt install --no-install-recommends winetricks -y
# .NET uygulamalarını Linux üzerinde wine ile çalıştırmak için gerekli
apt install mono-complete -y
apt install libgtk3-nocsd0:i386 -y

rm -rf /tmp/winemimetype.deb
wget -nc -O /tmp/winemimetype.deb https://github.com/bayramkarahan/wineplugin/raw/master/winemimetype.deb
sudo dpkg -i --force-all /tmp/winemimetype.deb

rm -rf /tmp/wineshare.deb
wget -nc -O /tmp/wineshare.deb https://github.com/bayramkarahan/wineshare/raw/master/wineshare.deb
sudo dpkg -i --force-all /tmp/wineshare.deb


apt autoremove -y
apt autoclean -y
rm -rf /etc/apt/sources.list.d/winehq*
rm -rf /etc/apt/keyrings/wine*
apt update


touch /var/lib/betikyukleyici/wine
exit 0
