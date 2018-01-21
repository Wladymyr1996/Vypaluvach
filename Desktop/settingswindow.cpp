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

#include "settingswindow.h"
#include "cnc.h"
#include <QPainter>
#include "alldata.h"

SettingsForm::SettingsForm(QRect ParrentGeometry, QWidget *parent) : QWidget(parent)
{
    int x, y, w= 700, h = 400;
    x = ParrentGeometry.x()+(ParrentGeometry.width()-w)/2;
    y = ParrentGeometry.y()+(ParrentGeometry.height()-h)/2;
    setGeometry(x, y, w, h);

    setFixedSize(w, h);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowTitle(QString(tr("App settings")+" - "+APPNAME));
    setWindowIcon(QIcon(":/img/setting.png"));

    MaxCountStepsXEdit = new QLineEdit(QString::number(AllData->getMaxCountStepsX()));
    MaxCountStepsXEdit->setValidator(new QIntValidator);
    MaxCountStepsYEdit = new QLineEdit(QString::number(AllData->getMaxCountStepsY()));
    MaxCountStepsYEdit->setValidator(new QIntValidator);
    MinSpeedXEdit = new QLineEdit(QString::number(AllData->getMinSpeedPerX()));
    MinSpeedXEdit->setValidator(new QIntValidator);
    MaxSpeedXEdit = new QLineEdit(QString::number(AllData->getMaxSpeedPerX()));
    MaxSpeedXEdit->setValidator(new QIntValidator);
    SkippedYSteps = new QLineEdit(QString::number(AllData->getSkippedYSteps()));
    SkippedYSteps->setValidator(new QIntValidator);
    SkippedLinesEdit = new QLineEdit(QString::number(AllData->getSkippedLines()));
    SkippedLinesEdit->setValidator(new QIntValidator);
    PrePrintingPauseEdit = new QLineEdit(QString::number(AllData->getPrePrintingPause()));
    PrePrintingPauseEdit->setValidator(new QIntValidator);
    GetPosEnabled = new QCheckBox(tr("Get HeadPos from CNC"));
    GetPosEnabled->setChecked(AllData->getGetPosEnabled());
    Marker = new QComboBox();
    Marker->addItem(QIcon(":/img/marker.png"), tr("Like for map"), 0);
    Marker->addItem(QIcon(":/img/SimpleMarker.png"), tr("Simple marker"), 1);
    Marker->setCurrentIndex(AllData->getMarker());
    Marker->setEnabled(AllData->getGetPosEnabled());
    cbMS = new QComboBox();
    cbMS->addItem(tr("Full step"), (char)0);
    cbMS->addItem(tr("Half step"), (char)1);
    cbMS->addItem(tr("Quarter step"), (char)2);
    cbMS->addItem(tr("Microstep"), (char)3);
    cbMS->setCurrentIndex((int)AllData->getMS());

    CancelButton = new QPushButton(tr("Cancel"));
    ApplyButton = new QPushButton(tr("Apply"));

    QGridLayout *lay = new QGridLayout(this);
    lay->addWidget(new QLabel(tr("Max Count steps per X:")), 0, 0); lay->addWidget(MaxCountStepsXEdit, 0, 1);
    lay->addWidget(new QLabel(tr("Max Count steps per Y:")), 1, 0); lay->addWidget(MaxCountStepsYEdit, 1, 1);
    lay->addWidget(new QLabel(tr("Min speed per X:")), 2, 0); lay->addWidget(MinSpeedXEdit, 2, 1);
    lay->addWidget(new QLabel(tr("Max speed per X:")), 3, 0); lay->addWidget(MaxSpeedXEdit, 3, 1);
    lay->addWidget(new QLabel(tr("Skipped Y steps on skipped lines:")), 4, 0); lay->addWidget(SkippedYSteps, 4, 1);
    lay->addWidget(new QLabel(tr("Skipped lines:")), 5, 0); lay->addWidget(SkippedLinesEdit, 5, 1);
    lay->addWidget(new QLabel(tr("Time to wait heating:")), 6, 0); lay->addWidget(PrePrintingPauseEdit, 6, 1);
    lay->addWidget(new QLabel(tr("Get HeadPos from CNC")), 7, 0); lay->addWidget(GetPosEnabled, 7, 1);
    lay->addWidget(new QLabel(tr("Marker:")), 8, 0); lay->addWidget(Marker, 8, 1);
    lay->addWidget(new QLabel(tr("Step mode:")), 9, 0); lay->addWidget(cbMS, 9, 1);

    QHBoxLayout *BtnLay = new QHBoxLayout;
    BtnLay->addWidget(CancelButton);
    BtnLay->addStretch();
    BtnLay->addWidget(ApplyButton);

    lay->addLayout(BtnLay, 11, 0, 1, 2);
    setLayout(lay);

    connect(CancelButton, SIGNAL(clicked(bool)),
            this, SLOT(onCancelButton()));
    connect(ApplyButton, SIGNAL(clicked(bool)),
            this, SLOT(onApplyButton()));
    connect(GetPosEnabled, SIGNAL(toggled(bool)),
            Marker, SLOT(setEnabled(bool)));
}

SettingsForm::~ SettingsForm()
{
    emit closeWindow();
}

void SettingsForm::closeEvent(QCloseEvent *)
{
    delete this;
}

void SettingsForm::onCancelButton()
{
    delete this;
}

void SettingsForm::onApplyButton()
{
    AllData->setMaxCountStepsX(MaxCountStepsXEdit->text().toInt());
    AllData->setMaxCountStepsY(MaxCountStepsYEdit->text().toInt());
    AllData->setMinSpeedPerX(MinSpeedXEdit->text().toInt());
    AllData->setMaxSpeedPerX(MaxSpeedXEdit->text().toInt());
    AllData->setSkippedYSteps(SkippedYSteps->text().toInt());
    AllData->setSkippedLines(SkippedLinesEdit->text().toInt());
    AllData->setGetPosEnabled(GetPosEnabled->isChecked());
    AllData->setMarker(Marker->currentIndex());
    AllData->setMS(cbMS->currentData().toChar().toLatin1());
    AllData->setPrePrintingPause(PrePrintingPauseEdit->text().toInt());
    AllData->saveAll();

    cnc->setGetPos();
    cnc->setMS();

    close();
}

