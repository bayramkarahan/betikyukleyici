#!/bin/bash
apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update
############################################################
cd /tmp 
wget http://cdn01.foxitsoftware.com/pub/foxit/reader/desktop/linux/2.x/2.4/en_us/FoxitReader.enu.setup.2.4.4.0910.x86.run.tar.gz
tar xzvf FoxitReader*.tar.gz
chmod a+x FoxitReader*.run
./FoxitReader*.run

sleep 1

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/foxitreader
exit 0
