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

#include "cncsettingswindow.h"
#include "cnc.h"
#include "alldata.h"
#include <QSerialPortInfo>

CNCsettingswindow::CNCsettingswindow(QRect ParrentGeometry, QWidget *parent) : QWidget(parent)
{
    int x, y, w= 500, h = 150;
    x = ParrentGeometry.x()+(ParrentGeometry.width()-w)/2;
    y = ParrentGeometry.y()+(ParrentGeometry.height()-h)/2;
    setGeometry(x, y, w, h);

    setFixedSize(w, h);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowTitle(QString(tr("CNC settings") + " - " + APPNAME));
    setWindowIcon(QIcon(":/img/setting.png"));

    cbBaudRate = new QComboBox;
    cbBaudRate->addItem("9600 bps", 9600);
    cbBaudRate->addItem("19200 bps", 19200);
    cbBaudRate->addItem("57600 bps", 57600);
    cbBaudRate->addItem("115200 bps", 115200);

    cbPort = new QComboBox;
    doScan();

    pbScan = new QPushButton(tr("Scan ports"));
    pbApply = new QPushButton(tr("Apply"));

    cbBaudRate->setCurrentIndex(AllData->getBaudRateIndex());

    QGridLayout *lay = new QGridLayout(this);
    lay->addWidget(new QLabel(tr("Baudrate:")), 0, 0); lay->addWidget(cbBaudRate, 0, 1);
    lay->addWidget(new QLabel(tr("Port:")), 1, 0); lay->addWidget(cbPort, 1, 1);

    QHBoxLayout *BtnLay = new QHBoxLayout;
    BtnLay->addWidget(pbScan);
    BtnLay->addStretch();
    BtnLay->addWidget(pbApply);

    lay->addLayout(BtnLay, 2, 0, 1, 2);
    setLayout(lay);

    connect(pbScan, SIGNAL(clicked(bool)),
            SLOT(doScan()));
    connect(pbApply, SIGNAL(clicked(bool)),
            SLOT(doApply()));
}

CNCsettingswindow::~CNCsettingswindow()
{
    emit closeWindow();
}

void CNCsettingswindow::closeEvent(QCloseEvent *)
{
    delete this;
}

void CNCsettingswindow::scan()
{
    QSerialPortInfo tmp;
    QList<QSerialPortInfo> conteiner = QSerialPortInfo::availablePorts();
    cbPort->clear();
    foreach (tmp, conteiner) {
        cbPort->addItem(tmp.description() + " (" + tmp.portName() + ")", tmp.portName());
    }
    if (conteiner.count()==0) cbPort->setEnabled(false);
    else cbPort->setEnabled(true);
    cbPort->setCurrentIndex(0);
}

void CNCsettingswindow::doScan()
{
    scan();
}

void CNCsettingswindow::doApply()
{
    AllData->setBaudRateIndex(cbBaudRate->currentIndex());
    AllData->setBaudRate(cbBaudRate->currentData().toInt());
    AllData->setPortName(cbPort->currentData().toString());
    AllData->saveAll();
    close();
}
