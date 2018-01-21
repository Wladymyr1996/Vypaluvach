#/bin/bash

# Скрипт для видалення "Випалювач"
# Script for unisnstall "Vypaluvach"
# Скрипт для удаления "Vypaluvach"

rm -rf /opt/Volodya/Vypaluvach
rm /usr/bin/vypaluvach
rm /usr/share/icons/hicolor/48x48/apps/vypaluvach.png
rm /usr/share/applications/vypaluvach.desktop 
gtk-update-icon-cache -f /usr/share/icons/hicolor
    
