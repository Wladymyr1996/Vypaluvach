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
#include <QTimer>

#ifndef CNC_H
#define CNC_H

//направлення
#define cncendmove 0x00
#define cncleft 0x01
#define cncright 0x02
#define cncup 0x03
#define cncdown 0x04

//Макроси команд
#define creturntoXzero 0x0B //Повернутися до нуля по Х
#define cnewline 0x01  //Нова лінія
#define creturn_to_zero 0x00 //Повернення в нуль
#define c_stop 0xFF //Зупинка
#define cmove 0x02 //Рухати в ручному режимі
#define csetzero 0x03 //Встановлення поточного положення як нуль координатної сітки
#define cendline 0x05 //перехід до наступного рядка
#define csetspacey 0x06 //Команда для встановлення проміжку між рпядками
#define csetskippedysteps 0x07 //Кількість крокв пропуску на на одну передану лінію
#define ctestproportion 0x08 //Тест пропорцфї
#define csetLine 0x0A //Встановлення лінії
#define csetSendPos 0x0D //Встановити, чи повертати дані про положення
#define cheadOn 0x0E //Увімкнути голівку/двигуни
#define cheadOff 0x0F //Увімкнути голівку/двигуни
#define cBuzzerOn 0x10 //Увімкнути сповіщення
#define cBuzzerOff 0x11  //Вимкнути сповіщення
#define csetMS 0x12
#define cshutdownOPI 0x13
#define cprePrint 0x14
#define csetPrePrintingZero 0x15
#define cprintPause 0x16
#define cprintEnd 0x17

//Відповіді від ЧПК
#define msgEnd 'f'
#define msgError 'e'
#define msgOk 'o'
#define msgPos 0x09

#include <QRgb>
#include <QLine>
#include <QQueue>
#include <QObject>
#include <QtSerialPort>
#include <QSerialPortInfo>

class ColorLine {

public:
    ColorLine(QPoint p1, QPoint p2, char cl);
    void setColor(char c);
    char getColor();
    QRgb getRGBColor();

    char color;
    QLine line;
};

class CNC : public QObject
{
    Q_OBJECT
public:
    enum enumStatus{NotBusy, Printing, Moving, Stoped};

    explicit CNC(QObject *parent = nullptr);
    ~CNC();
    bool init();
    void close();

    void startPrint(QList<QList<ColorLine*>*> *lines, int beginLine = 0);
    void stop();

    bool isConnected();
    bool isBusy();

    void TryConnect();
    void setCurrentPosAsZero();
    void returnToZero();
    void testProportion();
    void move(char direct);
    void setGetPos(bool getposState);
    void setGetPos();
    void setMS();
    void shutDown();
    int getBeginLine();

    enumStatus whatDo();
    QList<QSerialPortInfo> getPortList();

private:
    void setLine(int yp);
    void setBaudRate(int BaudRate);
    void setPrePrintingZero();
    void sendSkippedYSteps();
    void sendCommand(QByteArray *arr, bool deleteThis = false);
    void sendCommand(QByteArray arr);
    void sendNextLine();
    void setHeadOn();
    void setBuzzerOn();
    void setBuzzerOff();
    bool getHeadState();

    QWidget *myParent;
    QSerialPort *port;
    QTimer *HeadTimer, *PrintingWait;
    int yp, xp;
    char MS;
    enumStatus status;
    bool isHeadOn;
    QList<QList<ColorLine *> *> *lines;
    int beginLine;

    QQueue<QByteArray> *TransferData;
    QQueue<int> *yps;

private slots:
    void canReadData();
    void setHeadOff();
    void doPrinting();

signals:
    void newPosition(int, int);
    void isConnect();
    void isDisconnect();
    void error(QString);
    void newY(int);
    void endPrint(bool);
    void message(QString);
};

extern CNC *cnc;

#endif // CNC_H
