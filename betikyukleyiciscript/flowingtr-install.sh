#!/bin/bash
export DEBIAN_FRONTEND=noninteractive
set -u
[ "$(id -u)" -eq 0 ] || exit 0

packagename="flowingtr"
deb_url="https://github.com/bayramkarahan/flowingtr/raw/refs/heads/master/flowingtr_3.2_amd64.deb"
deb_file="/tmp/${packagename}.deb"

# ---- Paket sistemi toparlama ----
dpkg --configure -a || true
apt --fix-broken install -y || true

# ---- Paket indirme ----
wget -O "$deb_file" "$deb_url" || true

# ---- Kurulum / yeniden kurulum ----
apt install "$deb_file" --reinstall -y || true

# ---- Temizlik ----
rm -f "$deb_file" || true
apt --fix-broken install -y || true
dpkg --configure -a || true

# ---- İşaret dosyası ----
mkdir -p /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/${packagename}

exit 0
