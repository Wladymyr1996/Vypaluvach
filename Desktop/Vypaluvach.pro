#-------------------------------------------------
#
# Project created by QtCreator 2017-09-04T09:23:56
#
# VERSION 2.1-0
#
#-------------------------------------------------

#----------------------------------------------------------------------------
#    "Vypaluvach" - is control program for CNC wood burner "CNC Vypaluvach"
#    Copyright (C) 2017 Volodymyr Stadnyk
#    e-mail: Wladymyr1996@gmail.com
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>
#----------------------------------------------------------------------------


QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_FILE = icon.rc

CONFIG += c++11
TARGET = Vypaluvach
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += main.cpp\
        mainframe.cpp \
    mainwidget.cpp \
    settingswindow.cpp \
    aboutwindow.cpp \
    helpwindow.cpp \
    cnc.cpp \
    cncsettingswindow.cpp \
    alldata.cpp

HEADERS  += mainframe.h \
    mainwidget.h \
    settingswindow.h \
    aboutwindow.h \
    helpwindow.h \
    cnc.h \
    cncsettingswindow.h \
    alldata.h

FORMS    += mainframe.ui

TRANSLATIONS += Vypaluvach_uk.ts \
                Vypaluvach_ru.ts \
                Vypaluvach_en.ts

RESOURCES += \
    resources.qrc

DISTFILES += \
    Vypaluvach_ru.ts \
    Vypaluvach_uk.ts \
    Vypaluvach_en.ts
