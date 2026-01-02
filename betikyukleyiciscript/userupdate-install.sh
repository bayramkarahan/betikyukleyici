#!/bin/bash
set -e
# ---- Paket sistemi toparlama ----
dpkg --configure -a || true
apt --fix-broken install -y || true

# ---- İşlemler ------

sudo tee /etc/apt/sources.list <<'EOF'

## Debian
deb https://deb.debian.org/debian bookworm main contrib non-free non-free-firmware

## ETAP
deb http://depo.etap.org.tr/etap yirmiuc main contrib non-free non-free-firmware

## Pardus
deb http://depo.etap.org.tr/pardus yirmiuc main contrib non-free non-free-firmware

## Pardus Deb
deb http://depo.etap.org.tr/pardus yirmiuc-deb main contrib non-free non-free-firmware

## Pardus Security Deb
deb http://depo.etap.org.tr/guvenlik yirmiuc-deb main contrib non-free non-free-firmware
EOF
apt update || true
#ek pakerler
apt install eta-info --reinstall -y || true
apt install eta-register --reinstall -y || true
apt install eta-gtk-theme --reinstall  -y || true
apt install eta-icon-theme --reinstall -y || true
apt install eta-qr-reader --reinstall -y || true
apt install eta-right-click --reinstall -y || true
apt install eta-keyboard --reinstall -y || true
apt install rsync --reinstall -y || true

# ek paket bitti
wget -O /tmp/addmycomputer.deb https://github.com/bayramkarahan/addmycomputer/raw/refs/heads/master/addmycomputer.deb
cd /tmp
apt install ./addmycomputer.deb --reinstall -y || true
rm -f /tmp/addmycomputer.deb

wget -O /tmp/eta-menu.deb https://github.com/bayramkarahan/eta-menu/raw/refs/heads/master/eta-menu_1.2.1_all.deb
cd /tmp
apt install ./eta-menu.deb --reinstall -y || true
rm -f /tmp/eta-menu.deb

wget -O /tmp/setwallpaperlock.deb https://github.com/bayramkarahan/setwallpaper/raw/refs/heads/master/setwallpaperlock.deb
cd /tmp
apt install ./setwallpaperlock.deb --reinstall -y || true
rm -f /tmp/setwallpaperlock.deb

wget -O /tmp/e-ag-client.deb https://github.com/bayramkarahan/e-ag-client/raw/refs/heads/master/e-ag-client_2.8.5_amd64.deb
cd /tmp
apt install ./e-ag-client.deb --reinstall -y || true
rm -f /tmp/e-ag-client.deb

wget -O /tmp/zamanligorev.deb https://github.com/bayramkarahan/zamanligorev/raw/refs/heads/master/zamanligorev_1.8.0_amd64.deb
cd /tmp
apt install ./zamanligorev.deb --reinstall -y || true
rm -f /tmp/zamanligorev.deb


wget -O /tmp/greeter.deb https://github.com/bayramkarahan/pardus-lightdm-greeter/releases/download/current/pardus-lightdm-greeter_40.0.0_all.deb
cd /tmp
apt install ./greeter.deb --reinstall -y || true
rm -f /tmp/greeter.deb

wget -O /tmp/pardusupdate.deb https://depo.etap.org.tr/pardus/pool/main/p/pardus-update/pardus-update_0.5.1_all.deb
cd /tmp
apt install ./pardusupdate.deb --reinstall -y || true
rm -f /tmp/pardusupdate.deb



wget -O /tmp/corner_applet.js https://github.com/bayramkarahan/betikyukleyici/raw/refs/heads/master/deb/corner_applet.js
cd /tmp
cp /tmp/corner_applet.js /usr/share/cinnamon/applets/cornerbar@cinnamon.org/applet.js
rm -f /tmp/corner_applet.js

# 1️⃣ skel.zip indir
wget -O /tmp/skel.zip https://github.com/bayramkarahan/betikyukleyici/raw/refs/heads/master/deb/skel.zip
sleep 1

# 2️⃣ aç
cd /tmp || exit 1
unzip -o skel.zip
rm -f /tmp/skel.zip

# 3️⃣ /etc/skel güncelle
#cp -prfv /tmp/skel/. /etc/skel/
rsync -a /tmp/skel/ /etc/skel/
chown -R root:root /etc/skel

# 4️⃣ /home altındaki tüm kullanıcılar
for home in /home/*; do
    [ -d "$home" ] || continue
    user=$(basename "$home")

    echo "➡️ $user"

    rsync -a /tmp/skel/ "$home"/
    chown -R "$user:$user" "$home"
done

# 5️⃣ temizlik
rm -rf /tmp/skel


mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/userupdate
exit 0
