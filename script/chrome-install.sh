#!/bin/bash
wget -O /tmp/chrome.deb https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
dpkg --force-all -i /tmp/chrome.deb
sleep 1
rm /tmp/chrome.deb
mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/Google-Chrome
exit 0
