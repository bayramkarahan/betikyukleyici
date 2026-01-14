#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update

############################################################
rm -rf /usr/share/etap/bin/wine*
mv /opt/wine-stable /opt/oldwine-stable

#sudo apt remove winehq-stable 
#sudo apt remove wine-stable
#sudo apt remove wine-stable-amd64 
#sudo apt remove wine-stable-i386
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
apt install winehq-stable=9.0.0.0~bookworm-1 wine-stable=9.0.0.0~bookworm-1 wine-stable-amd64=9.0.0.0~bookworm-1 wine-stable-i386=9.0.0.0~bookworm-1 -y --allow-downgrades
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
#apt update
#touch /var/lib/betikyukleyici/wine
#exit 0
mkdir /opt/windows
# Detect the name of the display in use
display=":$(ls /tmp/.X11-unix/* | sed 's#/tmp/.X11-unix/X##' | head -n 1)"
# Detect the user using such display
user=$(who | grep '('$display')' | awk '{print $1}')
# Detect the id of the user
uid=$(id -u $user)
chmod 755 /opt/windows
chown $user:$user /opt/windows

exit 0
