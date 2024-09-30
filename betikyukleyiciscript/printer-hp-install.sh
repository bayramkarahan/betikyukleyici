#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
display=":$(ls /tmp/.X11-unix/* | sed 's#/tmp/.X11-unix/X##' | head -n 1)"      #Detect the name of the display in use
user=$(who | grep '('$display')' | awk '{print $1}')    #Detect the user using such display

############################################################
apt install printer-driver-all printer-driver-all-enforce printer-driver-foo2zjs printer-driver-foo2zjs-common printer-driver-hpcups printer-driver-hpijs 


sleep 1
cd /tmp
git clone https://github.com/bayramkarahan/printer.git
cd printer/
make
make install
sleep 1
rm print*

adduser $user lpadmin

service cups restart

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/hp
exit 0
