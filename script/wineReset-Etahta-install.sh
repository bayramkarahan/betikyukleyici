#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
wget -O /tmp/winemimetype.deb https://github.com/bayramkarahan/wineplugin/raw/master/winemimetype.deb
dpkg --force-all -i /tmp/winemimetype.deb
sleep 1
wget -O /tmp/wineshare.deb https://github.com/bayramkarahan/wineshare/raw/master/wineshare.deb
dpkg --force-all -i /tmp/wineshare.deb
rm -rf /opt/windows
for item in $(ls /home)
do
	rm -rf /home/$item/.wine
done
sleep 1
rm /tmp/wineshare.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/wine-reset
notify-send -i wine "Wine ayaralarının yapılandırılması için bilgisayarı yeniden başlatınız.." -u critical
exit 0
