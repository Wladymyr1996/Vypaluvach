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

#ifndef ALLDATA_H
#define ALLDATA_H

#define VERSION "2.1-1"
#define APPNAME "Vypaluvach"

#include <QObject>
#include <QSettings>
#include <QRect>

class TAllData : public QObject
{
    Q_OBJECT
public:
    explicit TAllData(QObject *parent = nullptr);
    ~TAllData();

    void saveAll();

    QString getPortName();
    int getMaxCountStepsX();
    int getMaxCountStepsY();
    int getMaxSpeedPerX();
    int getMinSpeedPerX();
    int getSkippedYSteps();
    int getSkippedLines();
    int getCColors();
    int getMarker();
    int getBaudRate();
    int getBaudRateIndex();
    QRect getWindowGeometry();
    bool getGetPosEnabled();
    unsigned char getMS();
    int getPrePrintingPause();

    void setPortName(QString Name);
    void setMaxCountStepsX(int count);
    void setMaxCountStepsY(int count);
    void setMaxSpeedPerX(int speed);
    void setMinSpeedPerX(int speed);
    void setSkippedYSteps(int skip);
    void setSkippedLines(int skip);
    void setMarker(int type);
    void setBaudRate(int Rate);
    void setBaudRateIndex(int Index);
    void setWindowGeometry(QRect geometry);
    void setGetPosEnabled(bool Enable);
    void setMS(unsigned char MS);
    void setPrePrintingPause(int pause);

    QSettings *AppSettings;
    int getScreenTime();
    void setScreenTime(int value);

private:
    void setCColors();
    bool GetPos;
    QString PortName;
    int MaxCountStepsX, MaxCountStepsY, MaxSpeedPerX, MinSpeedPerX, SkippedYSteps,
        SkippedLines, CColors, Marker, BaudRate, BaudRateIndex, PrePrintingPause,
        screenTime;
    QRect WindowGeometry;
    char MS;

signals:

};

extern TAllData *AllData;

#endif // ALLDATA_H
