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

#include "cnc.h"
#include "alldata.h"
#include <QRgb>
#include <QColor>
#include <QThread>
#include <QtCore/qmath.h>

ColorLine::ColorLine(QPoint p1, QPoint p2, char cl) {
    line=QLine(p1, p2);
    setColor(cl);
}

void ColorLine::setColor(char c)
{
    color = c;
}

char ColorLine::getColor()
{
    return color;
}

QRgb ColorLine::getRGBColor()
{
    return QColor(qRound(color*(255.0f/static_cast<qreal>(AllData->getCColors()))),
                  qRound(color*(255.0f/static_cast<qreal>(AllData->getCColors()))),
                  qRound(color*(255.0f/static_cast<qreal>(AllData->getCColors())))).rgb();
}

CNC::CNC(QObject *parent) : QObject(parent)
{
    port = new QSerialPort(this);

    status = NotBusy;

    yps = NULL;
    TransferData = NULL;

    HeadTimer = new QTimer(this);
    HeadTimer->setSingleShot(true);
    PrintingWait = new QTimer(this);
    PrintingWait->setSingleShot(true);
    isHeadOn = false;

    connect(port, SIGNAL(readyRead()),
            SLOT(canReadData()));
    connect(HeadTimer, SIGNAL(timeout()),
            SLOT(setHeadOff()));
    connect(PrintingWait, SIGNAL(timeout()),
            SLOT(doPrinting()));
}

CNC::~CNC()
{
    if (TransferData != NULL) delete TransferData;
    if (yps != NULL) delete yps;
}

bool CNC::init()
{
    if (port->isOpen()) {
        port->close();
    }

    port->setPortName(AllData->getPortName());
    port->setBaudRate(AllData->getBaudRate());

    bool c=port->open(QSerialPort::ReadWrite);

    if (c) {
        QThread::sleep(2);
        sendSkippedYSteps();
        setGetPos();
        setMS();
        emit isConnect();
    }
    return c;
}

void CNC::close()
{
    setGetPos(false);
    setHeadOff();
    port->close();
    emit isDisconnect();
}

void CNC::move(char direct)
{
    if (!isBusy()) {
        QByteArray *arr = new QByteArray;
        if (direct!=cncendmove){
            if (!getHeadState()) {
                setHeadOn();
                QThread::msleep(100);
            } else HeadTimer->stop();

            arr->push_back(cmove);
            arr->push_back(direct);
        } else {
            arr->push_back(c_stop);
            HeadTimer->start(5000);
        }
        sendCommand(arr);
    }
}

void CNC::setGetPos(bool getposState)
{
    if (isConnected()) {
        QByteArray *arr = new QByteArray;
        arr->push_back(csetSendPos);
        arr->push_back(getposState);
        sendCommand(arr);
    }
}

void CNC::stop()
{
    if (status==Printing) {
        TransferData->clear();
        while (yps->count() > 10) {
            yps->pop_back();
        }
        status = Stoped;
        port->waitForBytesWritten(1000);
        if (PrintingWait->isActive()) {
            PrintingWait->stop();
            yps->clear();
        }
        sendCommand(new QByteArray(1, cprintPause), true);
    }
}

void CNC::setCurrentPosAsZero()
{
    QByteArray *arr = new QByteArray;
    arr->push_back(csetzero);
    sendCommand(arr, true);
}

void CNC::returnToZero()
{
    if (!getHeadState()) {
        setHeadOn();
        QThread::sleep(1);
    }
    QByteArray *arr = new QByteArray;
    arr->push_back(static_cast<char>(creturn_to_zero));
    sendCommand(arr, true);
}

void CNC::setLine(int yp)
{
    yp/=AllData->getSkippedLines();
    QByteArray *arr = new QByteArray;
    arr->push_back(csetLine);
    arr->push_back((yp >> 8) & 0xFF);
    arr->push_back(yp & 0xFF);
    sendCommand(arr, true);
}

void CNC::testProportion()
{

    QByteArray *arr = new QByteArray;
    arr->push_back(ctestproportion);
    sendCommand(arr);
}

void CNC::setBaudRate(int BaudRate)
{
    port->setBaudRate(BaudRate);
}

void CNC::setGetPos()
{
    if (isConnected()) {
        QByteArray *arr = new QByteArray;
        arr->push_back(csetSendPos);
        arr->push_back((char)AllData->getGetPosEnabled());
        sendCommand(arr);
    }
}

void CNC::setMS()
{
    MS = AllData->getMS();
    if (isConnected()) {
        QByteArray *arr = new QByteArray;
        arr->push_back(csetMS);
        arr->push_back(MS);
        sendCommand(arr, true);
    }
}

void CNC::shutDown()
{
    if (isConnected()) {
        QByteArray *arr = new QByteArray;
        arr->push_back(cshutdownOPI);
        arr->push_back((char)AllData->getGetPosEnabled());
        sendCommand(arr);
        port->waitForBytesWritten(30000);
    }
}

int CNC::getBeginLine()
{
    return beginLine;
}

void CNC::sendSkippedYSteps()
{
    QByteArray *arr = new QByteArray;

    arr->push_back(csetskippedysteps);
    arr->push_back(AllData->getSkippedYSteps()>>8);
    arr->push_back(AllData->getSkippedYSteps());

    sendCommand(arr);
}

bool CNC::isConnected()
{
    return port->isOpen();
}

bool CNC::isBusy()
{
    if (status==NotBusy) return false;
    return true;
}

void CNC::TryConnect()
{
    init();
}

CNC::enumStatus CNC::whatDo()
{
    return status;
}

void CNC::startPrint(QList<QList<ColorLine *> *> *lines, int beginLine)
{
    this->lines = lines;
    this->beginLine = beginLine;

    HeadTimer->stop();

    if (TransferData != NULL) delete TransferData;
    if (yps != NULL) delete yps;
    TransferData = new QQueue<QByteArray>;
    yps = new QQueue<int>;

    sendSkippedYSteps();
    setGetPos();
    setMS();

    if (!isBusy()) {
        setHeadOn();
        QThread::msleep(500);
        if (beginLine == 0) {
            setCurrentPosAsZero();
	    sendCommand(QByteArray(1, (char)cprePrint));
	}
        else
            sendCommand(QByteArray(1, (char)csetPrePrintingZero));
        status = Printing;
        PrintingWait->start(AllData->getPrePrintingPause()*1000);
    }
}

void CNC::sendNextLine()
{
    if (!TransferData->empty()) sendCommand(TransferData->dequeue());
}

void CNC::setHeadOn()
{
    QByteArray *arr = new QByteArray;
    arr->push_back(static_cast<char>(cheadOn));
    sendCommand(arr, true);
    port->waitForBytesWritten(1000);
    isHeadOn = true;
}

void CNC::setBuzzerOn()
{
    QByteArray *arr = new QByteArray;
    arr->push_back(static_cast<char>(cBuzzerOn));
    sendCommand(arr, true);
    port->waitForBytesWritten(1000);
}

void CNC::setBuzzerOff()
{
    QByteArray *arr = new QByteArray;
    arr->push_back(static_cast<char>(cBuzzerOff));
    sendCommand(arr, true);
    port->waitForBytesWritten(1000);
}

void CNC::setHeadOff()
{
    QByteArray *arr = new QByteArray;
    arr->push_back(static_cast<char>(cheadOff));
    sendCommand(arr, true);
    port->waitForBytesWritten(1000);
    isHeadOn = false;
}

void CNC::doPrinting()
{
    returnToZero();
    setLine(beginLine);
    PrintingWait->stop();
    int cy;
    for (cy = beginLine/AllData->getSkippedLines(); cy < lines->count()/AllData->getSkippedLines(); cy++) {
        int y = cy * AllData->getSkippedLines();
        for (int x = 0; x < lines->at(y)->count(); x++) {
            QByteArray tmp;
            tmp.push_back(cnewline);

            int mPause = AllData->getMinSpeedPerX() + (AllData->getCColors() - lines->at(y)->at(x)->getColor());
            tmp.push_back((mPause>>8)&0xFF);
            tmp.push_back(mPause & 0xFF);

            int toX = lines->at(y)->at(x)->line.p2().x();
            tmp.push_back((toX>>8) & 0xFF);
            tmp.push_back(toX & 0xFF);
            TransferData->enqueue(tmp);
            yps->enqueue(cy);
        }
        TransferData->enqueue(QByteArray(1, cendline));
        yps->enqueue(cy);
    }
    TransferData->enqueue(QByteArray(1, cprintEnd));
    yps->enqueue(cy);

    for (int i=0; i<10; i++) sendNextLine();
}

bool CNC::getHeadState()
{
    return isHeadOn;
}

void CNC::sendCommand(QByteArray *arr, bool deleteThis)
{
    if (port->isOpen()) {
        port->write(*arr);
//        qDebug() << port->portName() << port->baudRate() << arr->toHex();
        if (port->error()!=QSerialPort::NoError) {
            port->close();
            emit isDisconnect();
        }
    }
    if (deleteThis) delete arr;
}

void CNC::sendCommand(QByteArray arr)
{
    sendCommand(new QByteArray(arr), true);
}

void CNC::canReadData()
{
    QByteArray data = port->readAll();
    for (int i=0; i<data.count(); i++) {
        if ((data.at(i) == msgEnd) && (yps!=NULL)) {
            sendNextLine();
            if ((!yps->empty())) {
                static int oldYps = -1;
                int curyps = yps->dequeue();
                if (oldYps != curyps) {
                    oldYps = curyps;
                    emit newY(yps->dequeue());
                }
            }
            else {
                if (status==Printing) {
                    status = NotBusy;
                    emit endPrint(false);
                    setGetPos(false);
                    setHeadOff();
                    setGetPos();
                    emit message("Printing succes!");
                    HeadTimer->start(5000);
                }
                if (status==Stoped) {
                    status = NotBusy;
                    emit endPrint(true);
                    setGetPos(false);
                    setHeadOff();
                    setGetPos();
                    emit message("Printing stoped!");
                }
           }
        } else
        if (data.at(i) == msgPos) {
            if (i+4<data.count()) {
                unsigned char xh, xl, yh, yl;
                xl = data.at(i+1);
                xh = data.at(i+2);
                yl = data.at(i+3);
                yh = data.at(i+4);
                qint16 posx = xl | (xh<<8);
                qint16 posy = yl | (yh<<8);
               // if (xh & 0x80) posx*=-1;

                emit newPosition(posx, posy);
            }
            i += 4;
        }
        if (data.at(i) == msgOk) HeadTimer->start(5000);
    }
}

CNC *cnc;
