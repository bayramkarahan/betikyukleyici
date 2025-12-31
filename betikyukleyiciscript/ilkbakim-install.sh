#!/bin/bash
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

# ---- betikyukleyici işlemi ------
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/ilkbakim

