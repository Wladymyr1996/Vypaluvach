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

#ifndef MC_H
#define MC_H

#include <QObject>
#include <QTimer>
#include <QDir>
#include "ui.h"
#include "cnc.h"
#include "alldata.h"

//Перелік типів функцій для меню
enum TMenuFunction {FNone, FSelectUSB, FSelectFile, FSelectMainMenu, FLoadImage,
                    FSelectSettings, FEditMaxStepsX, FEditMaxStepsY, FEditMinMPSX,
                    FEditMaxMPSX, FEditNSkipStepY, FEditSkipImgLine, FEditWaitTimeHeat,
                    FSelectStepMode, FSelectBaudRate, BR9600, BR19200, BR57600, BR115200,
                    SMFullStep, SMHalfStep, SMQuarterStep, SMMicroStep, FMoving, FReturn,
                    FBurn, FMoveToZero, FShutDown, FEditScreenTime};

//Перелік типів функцій для ввдення числових значеннь
enum TEditType {EMaxStepsY, EMaxStepsX, EMinMPSX, EMaxMPSX, ENskipStepY, ESkipImgLine,
                EWaitTimeHeat, EReturnLine, EScreenTime};

//Структура даних для введення числового значення
struct TEdit {
    QString value;
    QString name;
    TEditType type;
};

//Структура даних для пункта меню
struct TMenuItem {
    QString name;
    TMenuFunction func;
};

//Структура меню
struct TMenu
{
    QList<TMenuItem> Item;
    QString Name;
    int CurrentItem;
};

//Головний клас, який заправляє всім
class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = nullptr);

private:
    enum TStatus {SMenu, SEdit, SPrinting, SMoving};
    QList<QList<ColorLine*>*> *lines = NULL;
    TStatus Status = SMenu;
    lcdUI *LCD = NULL;
    keyboardUI *Keyboard = NULL;
    TMenu *CurrentMenu = NULL;
    TEdit CurrentEdit;
    QString path;
    beepUI *Buzzer;
    shutdownUI *ShutDown;
    QPoint pos;
    int currentLine;

    int MaxCountStepsX, MaxCountStepsY, MaxSpeedPerX, MinSpeedPerX, SkippedYSteps,
        SkippedLines, CColors, Marker, BaudRate, BaudRateIndex, PrePrintingPause;

    void nextItem();
    void printMenu();
    void printEdit();
    void printMoving();
    void printPrinting();
    void prevItem();
    void setMenu(TMenu *menu);
    void setEdit();
    void selectMainMenu();
    void selectUSB();
    void selectFile();
    void selectSettigns();
    void selectSetBaudRate();
    void selectSetStepMode();
    void toMoving();
    void addNumberToEdit(int digit);
    void saveEditValue();
    void loadImage();
    void setBaudRate();
    void setStepMode();
    void startBurn();
    void returnToZero();

private slots:
    void keyPressed(int k);
    void keyRealease(int);
    void showMessage(QString msg);
    void getPos(int X, int Y);
    void connected();
    void newYLine(int Y);
    void endPrint(bool stopped);

signals:
    void runKeyboard();
    void Warning();
    void printLCD(QString, int, int, int);
    void clearLCD();
    void onBrightLCD();
    void onFinalBeeps();
    void offFinalBeeps();
    void doShutDown();
};

#endif // MC_H
