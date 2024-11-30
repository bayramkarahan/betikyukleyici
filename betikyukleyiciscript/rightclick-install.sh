#!/bin/bash

apt install --fix-missing -y
apt --fix-broken install -y
apt-get install -f -y # eksik bağımlılıkları tamamlaması için.
apt autoremove -y
apt update


function run-in-user-session() {
    _display_id=":$(find /tmp/.X11-unix/* | sed 's#/tmp/.X11-unix/X##' | head -n 1)"
    _username=$(who | grep "\(${_display_id}\)" | awk '{print $1}')
    _user_id=$(id -u "$_username")
    _environment=("DISPLAY=$_display_id" "DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/$_user_id/bus")
    echo $_display_id
   echo $_username
   echo $_user_id
   echo $_environment
    
    sudo -Hu "$_username" env "${_environment[@]}" "$@"
}

############################################################
apt-get install zenity -y
sleep 1

zaman=$(zenity --entry --title "Sağtuş Değeri" --text "Sağtuş Bekleme Süresini Giriniz"  --entry-text "1.0")

run-in-user-session gsettings set org.gnome.desktop.a11y.mouse secondary-click-enabled true
run-in-user-session gsettings set org.gnome.desktop.a11y.mouse secondary-click-time "${zaman}"

#gsettings set org.gnome.desktop.a11y.mouse secondary-click-enabled true
#gsettings set org.gnome.desktop.a11y.mouse secondary-click-time "${zaman}"

mkdir /var/lib/betikyukleyici
touch /var/lib/betikyukleyici/rightclick
exit 0

