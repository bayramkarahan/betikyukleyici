#!/bin/bash

#### etap greeter install
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt --fix-broken install -y

wget https://github.com/bayramkarahan/qr-greeter/releases/download/current/etap-greeter_0.1.0_all.deb 
mv etap-greeter_0.1.0_all.deb tmp/
dpkg -i /tmp/etap-greeter_0.1.0_all.deb # dosya adını uygun şekilde yazınız.
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.

sleep 1
rm /tmp/etap-greeter_0.1.0_all.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/etap-greeter
exit 0
