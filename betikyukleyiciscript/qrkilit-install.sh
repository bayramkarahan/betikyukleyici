#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
cd /tmp
wget https://github.com/bayramkarahan/pardus-lightdm-greeter-qrkilit/releases/download/current/pardus-lightdm-greeter-qrkilit_1.2_all.deb

dpkg -i /tmp/etap-greeter_0.1.0_all.deb # dosya adını uygun şekilde yazınız.
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.

sleep 1

wget https://github.com/bayramkarahan/pardus-lightdm-greeter-listener/releases/download/current/pardus-lightdm-greeter-listener_1.0_all.deb

dpkg -i /tmp/pardus-lightdm-greeter-listener_1.0_all.deb # dosya adını uygun şekilde yazınız.
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
sleep 1
rm /tmp/pardus-lightdm-greeter-qrkilit_1.2_all.deb
rm /tmp/pardus-lightdm-greeter-listener_1.0_all.deb

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/qrkilit
exit 0

