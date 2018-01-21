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
    void endPrint(bool);

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
