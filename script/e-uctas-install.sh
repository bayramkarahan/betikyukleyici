#!/bin/bash
wget -O /tmp/e-uctas.deb https://github.com/bayramkarahan/e-uctas/raw/master/e-uctas_1.0.0_amd64.deb
dpkg --force-all -i /tmp/e-uctas.deb
sleep 1
rm /tmp/e-uctas.deb
mkdir /var/lib/tinyinstaller
touch /var/lib/tinyinstaller/e-uctas
exit 0
