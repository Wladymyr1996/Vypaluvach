#/bin/bash

# Встановлювальний скрипт для "Випалювач" версії 2.0-2
# Instalation script for Vypaluvach version 2.0-2
# Установочный скрипт для Vypaluvach весрии 2.0-2

lrelease Vypaluvach*.ts
qmake Vypaluvach.pro

if [ $? != 0 ]
then
    if [ $GDM_LANG = "uk" ] 
    then
        echo "qmake повідомив про помилку."
    else 
        if [ $GDM_LANG = "ru" ] 
        then
            echo "qmake сообщил об ошибке."
        else
            echo "qmake notify about error."
        fi
    fi
    exit
fi

make 

if [ $? != 0 ]
then
    if [ $GDM_LANG = "uk" ] 
    then
        echo "make повідомив про помилку."
    else 
        if [ $GDM_LANG = "ru" ] 
        then
            echo "make сообщил об ошибке."
        else
            echo "make notify about error."
        fi
    fi
    exit
fi

make clean

mkdir -p /opt/Volodya/Vypaluvach
cp uninstall.sh /opt/Volodya/Vypaluvach/uninstall.sh
cp Vypaluvach /usr/bin/vypaluvach
cp img/icon.png /usr/share/icons/hicolor/48x48/apps/vypaluvach.png
cp vypaluvach.desktop /usr/share/applications
gtk-update-icon-cache -f /usr/share/icons/hicolor
    
