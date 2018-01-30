/*
    "Vypaluvach" - is control program for CNC wood burner "CNC Vypaluvach"
    Copyright (C) 2017 Volodymyr Stadnyk
    e-mail: Wladymyr1996@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>
*/

#include "alldata.h"

TAllData::TAllData(QObject *parent) : QObject(parent)
{
    AppSettings = new QSettings("Volodya", "Vypaluvach");

    AppSettings->beginGroup("/Window");
        WindowGeometry = AppSettings->value("/Geometry", QVariant(QRect(50,
                                                                           50,
                                                                           500,
                                                                           400))).toRect();
    AppSettings->endGroup();

    AppSettings->beginGroup("/AppSettings");
        MaxCountStepsX = AppSettings->value("/MaxCountStepsX", 0).toInt();
        MaxCountStepsY = AppSettings->value("/MaxCountStepsY", 0).toInt();
        MinSpeedPerX = AppSettings->value("/MinSpeedX", 0).toInt();
        MaxSpeedPerX = AppSettings->value("/MaxSpeedX", 0).toInt();
        SkippedLines = AppSettings->value("/SkippedLines", 0).toInt();
        SkippedYSteps = AppSettings->value("/SkippedYSteps", 0).toInt();
        GetPos = AppSettings->value("/GetPosEnabled", true).toBool();
        Marker = AppSettings->value("/Marker", 0).toInt();
        MS = AppSettings->value("/MS", 0).toInt();
        PrePrintingPause = AppSettings->value("/PrePrintingPause", 30).toInt();
    AppSettings->endGroup();

    AppSettings->beginGroup("/CNCSettings");
        BaudRate = AppSettings->value("/BaudRate").toInt();
        BaudRateIndex = AppSettings->value("/BaudRateIndex").toInt();
        PortName = AppSettings->value("/PortName").toString();
    AppSettings->endGroup();

    setCColors();
}

TAllData::~TAllData()
{
    saveAll();
    delete AppSettings;
}

void TAllData::saveAll()
{
    AppSettings->beginGroup("/Window");
        AppSettings->setValue("/Geometry", WindowGeometry);
    AppSettings->endGroup();

    AppSettings->beginGroup("/AppSettings");
        AppSettings->setValue("/MaxCountStepsX", MaxCountStepsX);
        AppSettings->setValue("/MaxCountStepsY", MaxCountStepsY);
        AppSettings->setValue("/MinSpeedX", MinSpeedPerX);
        AppSettings->setValue("/MaxSpeedX", MaxSpeedPerX);
        AppSettings->setValue("/SkippedLines", SkippedLines);
        AppSettings->setValue("/SkippedYSteps", SkippedYSteps);
        AppSettings->setValue("/GetPosEnabled", GetPos);
        AppSettings->setValue("/Marker", Marker);
        AppSettings->setValue("/MS", MS);
        AppSettings->setValue("/PrePrintingPause", PrePrintingPause);
    AppSettings->endGroup();

    AppSettings->beginGroup("/CNCSettings");
        AppSettings->setValue("/BaudRate", BaudRate);
        AppSettings->setValue("/BaudRateIndex", BaudRateIndex);
        AppSettings->setValue("/PortName", PortName);
    AppSettings->endGroup();
}

QString TAllData::getPortName()
{
    return PortName;
}

int TAllData::getMaxCountStepsX()
{
    return MaxCountStepsX;
}

int TAllData::getMaxCountStepsY()
{
    return MaxCountStepsY;
}

int TAllData::getMaxSpeedPerX()
{
    return MaxSpeedPerX;
}

int TAllData::getMinSpeedPerX()
{
    return MinSpeedPerX;
}

int TAllData::getSkippedYSteps()
{
    return SkippedYSteps;
}

int TAllData::getSkippedLines()
{
    return SkippedLines;
}

int TAllData::getCColors()
{
    return CColors;
}

int TAllData::getMarker()
{
    return Marker;
}

int TAllData::getBaudRate()
{
    return BaudRate;
}

int TAllData::getBaudRateIndex()
{
    return BaudRateIndex;
}

QRect TAllData::getWindowGeometry()
{
    return WindowGeometry;
}

bool TAllData::getGetPosEnabled()
{
    return GetPos;
}

unsigned char TAllData::getMS()
{
    return MS;
}

int TAllData::getPrePrintingPause()
{
    return PrePrintingPause;
}

void TAllData::setPortName(QString Name)
{
    PortName = Name;
}

void TAllData::setMaxCountStepsX(int count)
{
    MaxCountStepsX = count;
}

void TAllData::setMaxCountStepsY(int count)
{
    MaxCountStepsY = count;
}

void TAllData::setMaxSpeedPerX(int speed)
{
    MaxSpeedPerX = speed;
    setCColors();
}

void TAllData::setMinSpeedPerX(int speed)
{
    MinSpeedPerX = speed;
    setCColors();
}

void TAllData::setSkippedYSteps(int skip)
{
    SkippedYSteps = skip;
}

void TAllData::setSkippedLines(int skip)
{
    SkippedLines = skip;
}

void TAllData::setMarker(int type)
{
    Marker = type;
}

void TAllData::setBaudRate(int Rate)
{
    BaudRate = Rate;
}

void TAllData::setBaudRateIndex(int Index)
{
    BaudRateIndex = Index;
}

void TAllData::setWindowGeometry(QRect geometry)
{
    WindowGeometry = geometry;
}

void TAllData::setGetPosEnabled(bool Enable)
{
    GetPos = Enable;
}

void TAllData::setMS(unsigned char MS)
{
    this->MS = MS;
}

void TAllData::setPrePrintingPause(int pause)
{
    PrePrintingPause = pause;
}

void TAllData::setCColors()
{
    CColors = MaxSpeedPerX - MinSpeedPerX;
}

TAllData *AllData;
