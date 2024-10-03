#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
display=":$(ls /tmp/.X11-unix/* | sed 's#/tmp/.X11-unix/X##' | head -n 1)"      #Detect the name of the display in use
user=$(who | grep '('$display')' | awk '{print $1}')    #Detect the user using such display

############################################################
rm -rf /opt/windows
mkdir /opt/windows
chown $user:$user /opt/windows
chmod 777 /opt/windows

for item in $(ls /home)
do
rm -rf /home/$item/.wine
ln -s /opt/windows /home/$item/.wine
done

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/wine-reset
notify-send -i wine "Wine ayaralarının yapılandırılması için bilgisayarı yeniden başlatınız.." -u critical
exit 0
