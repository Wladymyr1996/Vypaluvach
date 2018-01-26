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

#include "mc.h"
#include <QDebug>
#include <QThread>
#include <QImage>
#include <QColor>

#define SERIALPORT "/dev/ttyS2"

MainClass::MainClass(QObject *parent) : QObject(parent)
{
    //Ініціалізація глоабльних класів Даних і ЧПК
    AllData = new TAllData;
    cnc = new CNC;
    AllData->setGetPosEnabled(false);

    Status = SMenu;

    //Ініціалізація класів інтерфейсу користувача в інших потоках
    QThread *th = new QThread;
    LCD = new lcdUI;
    LCD->moveToThread(th);
    th->start();

    th = new QThread;
    Keyboard = new keyboardUI();
    Keyboard->moveToThread(th);

    Buzzer = new beepUI;
    Buzzer->moveToThread(th);
    th->start();

    ShutDown = new shutdownUI;

    //З'єдання  усіх сигналів зі слотами

    connect(Keyboard, SIGNAL(keyPressed(int)),
            SLOT(keyPressed(int)));
    connect(Keyboard, SIGNAL(keyRelease(int)),
            SLOT(keyRealease(int)));
    connect(Keyboard, SIGNAL(beep()),
            Buzzer, SLOT(beep()));
    connect(this, SIGNAL(clearLCD()),
            LCD, SLOT(clear()));
    connect(this, SIGNAL(printLCD(QString,int,int,int)),
            LCD, SLOT(print(QString,int,int,int)));
    connect(this, SIGNAL(onBrightLCD()),
            LCD, SLOT(BrightOn()));
    connect(this, SIGNAL(Warning()),
            Buzzer, SLOT(Warning()));
    connect(this, SIGNAL(onFinalBeeps()),
            Buzzer, SLOT(Final()));
    connect(this, SIGNAL(offFinalBeeps()),
            Buzzer, SLOT(Stop()));
    connect(cnc, SIGNAL(isConnect()),
            SLOT(connected()));
    connect(cnc, SIGNAL(newPosition(int,int)),
            SLOT(getPos(int,int)));
    connect(cnc, SIGNAL(newY(int)),
            SLOT(newYLine(int)));
    connect(cnc, SIGNAL(endPrint(bool)),
            SLOT(endPrint(bool)));
    connect(cnc, SIGNAL(message(QString)),
            SLOT(showMessage(QString)));
    connect(this, SIGNAL(doShutDown()),
            ShutDown, SLOT(doShutDown()));

    QThread::sleep(2);
    selectMainMenu();

    AllData->setPortName(SERIALPORT);
    AllData->setGetPosEnabled(false);
    cnc->TryConnect();
}

//наступний пункт меню
void MainClass::nextItem()
{
    CurrentMenu->CurrentItem++;
    if (CurrentMenu->CurrentItem == CurrentMenu->Item.count()) CurrentMenu->CurrentItem = 0;
    printMenu();
}

//Малювання меню
void MainClass::printMenu()
{
    QString s = QString::number(CurrentMenu->CurrentItem+1)+"/"+QString::number(CurrentMenu->Item.count());
    QString line = CurrentMenu->Name;
    while (line.length()<16-s.length()) line += " ";
    emit printLCD(line + s, 0, 0, 16);

    line = CurrentMenu->Item.at(CurrentMenu->CurrentItem).name;
    while (line.length()<14) line+=" ";
    emit printLCD((char)0x7F + line, 0, 1, 15);
    emit printLCD(QString("")+(char)0x7E, 15, 1, 1);
}

//Малювання поля введеня числа
void MainClass::printEdit()
{
    while (CurrentEdit.name.length()<16) CurrentEdit.name += " ";
    emit printLCD(CurrentEdit.name, 0, 0, 16);
    QString str = "Value: " + CurrentEdit.value + "_";

    while (str.length() < 16) str += " ";
    emit printLCD(str, 0, 1, 16);
}

//Малюванняя екрану ручного руху жалом
void MainClass::printMoving()
{
    emit printLCD("Manual moving   ", 0, 0, 16);
    QString space = "";
    QString Xstr = QString::number(pos.x());
    for (int i = 0; i<6-Xstr.length(); i++) space +=" ";
    emit printLCD("X:"+Xstr+space, 0, 1, 8);
    emit printLCD("Y:"+QString::number(pos.y())+"     ", 8, 1, 16);
}

//Малювання екрану випалювання
void MainClass::printPrinting()
{
    QString line = "Burn";
    QString str = QString::number(currentLine)+"/"+QString::number(lines->count());
    while (line.length() < 16 - str.length()) line += " ";
    emit printLCD(line + str, 0, 0, 16);

    int procentd2 = (50 * (currentLine - cnc->getBeginLine())) / (lines->count() - cnc->getBeginLine());
    line= "[";
    int full = procentd2/5;
    for (int i = 0; i<full; i++) line += (char)0x04;
    if (procentd2 - (full*5) > 0) line += (char)(procentd2-(full*5)-1);
    while (line.length()<11) line+=(char)0x06;
    line+="]";

    str = QString::number((100 * (currentLine - cnc->getBeginLine())) / (lines->count() - cnc->getBeginLine()))+"%";
    while (line.length()<16-str.length()) line += " ";
    emit printLCD(line + str, 0, 1, 16);
}

//Попередній пункт меню
void MainClass::prevItem()
{
    CurrentMenu->CurrentItem--;
    if (CurrentMenu->CurrentItem == -1) CurrentMenu->CurrentItem = CurrentMenu->Item.count()-1;
    printMenu();
}

//Обрати меню
void MainClass::setMenu(TMenu *menu)
{
    Status = SMenu;
    if (CurrentMenu != NULL) delete CurrentMenu;
    CurrentMenu = menu;
    printMenu();

    //При відкритті будь-якого меню, засвічуємо екран
    emit onBrightLCD();
}

//Обрання "редагування числового параметру"
void MainClass::setEdit()
{
    CurrentEdit.name = CurrentMenu->Item.at(CurrentMenu->CurrentItem).name;
    switch (CurrentMenu->Item.at(CurrentMenu->CurrentItem).func) {
    case FEditMaxStepsX:
        CurrentEdit.type = EMaxStepsX;
        CurrentEdit.value = QString::number(AllData->getMaxCountStepsX());
        break;
    case FEditMaxStepsY:
        CurrentEdit.type = EMaxStepsY;
        CurrentEdit.value = QString::number(AllData->getMaxCountStepsY());
        break;
    case FEditMaxMPSX:
        CurrentEdit.type = EMaxMPSX;
        CurrentEdit.value = QString::number(AllData->getMaxSpeedPerX());
        break;
    case FEditMinMPSX:
        CurrentEdit.type = EMinMPSX;
        CurrentEdit.value = QString::number(AllData->getMinSpeedPerX());
        break;
    case FEditNSkipStepY:
        CurrentEdit.type = ENskipStepY;
        CurrentEdit.value = QString::number(AllData->getSkippedYSteps());
        break;
    case FEditSkipImgLine:
        CurrentEdit.type = ESkipImgLine;
        CurrentEdit.value = QString::number(AllData->getSkippedLines());
        break;
    case FEditWaitTimeHeat:
        CurrentEdit.type = EWaitTimeHeat;
        CurrentEdit.value = QString::number(AllData->getPrePrintingPause());
        break;
    case FEditScreenTime:
        CurrentEdit.type = EScreenTime;
        CurrentEdit.value = QString::number(AllData->getScreenTime());
        break;
    case FReturn:
        if (lines == NULL) {
            showMessage("Image not opened");
            return;
        }
        CurrentEdit.type = EReturnLine;
        CurrentEdit.name = "Return line";
        CurrentEdit.value = QString::number(AllData->getLastLine());
        break;
    default:
    break;
    }
    Status = SEdit;
    printEdit();
    emit onBrightLCD();
}

//Ініціалізація для показу головного меню
void MainClass::selectMainMenu()
{
    TMenu *MainMenu = new TMenu;
    MainMenu->CurrentItem = 0;
    MainMenu->Name = "Main menu";
    MainMenu->Item.append({"Select image", FSelectUSB});
    MainMenu->Item.append({"Burn", FBurn});
    MainMenu->Item.append({"Restore", FReturn});
    MainMenu->Item.append({"Manual moving", FMoving});
    MainMenu->Item.append({"Settings", FSelectSettings});
    MainMenu->Item.append({"Shutdown", FShutDown});

    setMenu(MainMenu);
}

//Ініціалізація для показу меню вибору USB пристрою
void MainClass::selectUSB()
{
    QDir dir("/media");
    TMenu *USBmenu = new TMenu;
    USBmenu->Name = "Select USB";
    USBmenu->CurrentItem = 0;
    foreach (QString s, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name)) {
        USBmenu->Item.append({s, FSelectFile});
    }
    USBmenu->Item.append({"Return back", FSelectMainMenu});

    setMenu(USBmenu);
}

//Ініціалізація для показу меню вибору файла
void MainClass::selectFile()
{
    path = "/media/"+CurrentMenu->Item.at(CurrentMenu->CurrentItem).name+"/";
    QDir dir(path);
    TMenu *FileMenu = new TMenu;
    FileMenu->Name = "Select image";
    FileMenu->CurrentItem = 0;
    QStringList filters;
    filters << "*.jpg" << "*.JPG" << "*.png" << "*.jpeg" << "*.PNG";
    foreach (QString s, dir.entryList(filters, QDir::Files, QDir::Name)) {
        FileMenu->Item.append({s, FLoadImage});
    }
    FileMenu->Item.append({"Return back", FSelectUSB});
    FileMenu->Item.append({"To main menu", FSelectMainMenu});

    setMenu(FileMenu);
}

//Ініціалізація для показу меню налаштувань
void MainClass::selectSettigns()
{
    TMenu *SettingsMenu = new TMenu;
    SettingsMenu->Name = "Settings";
    SettingsMenu->CurrentItem = 0;

    SettingsMenu->Item.append({"Max steps/X", FEditMaxStepsX});
    SettingsMenu->Item.append({"Max steps/Y", FEditMaxStepsY});
    SettingsMenu->Item.append({"Min ms/step X", FEditMinMPSX});
    SettingsMenu->Item.append({"Max ms/step X", FEditMaxMPSX});
    SettingsMenu->Item.append({"N skip step Y", FEditNSkipStepY});
    SettingsMenu->Item.append({"Skip img line", FEditSkipImgLine});
    SettingsMenu->Item.append({"Wait time heat", FEditWaitTimeHeat});
    SettingsMenu->Item.append({"Step mode", FSelectStepMode});
    SettingsMenu->Item.append({"BaudRate", FSelectBaudRate});
    SettingsMenu->Item.append({"Screen timeout", FEditScreenTime});
    SettingsMenu->Item.append({"Return back", FSelectMainMenu});

    setMenu(SettingsMenu);
}

//Ініціалізація для показу меню вибору швидкості передачі даних
void MainClass::selectSetBaudRate()
{
    TMenu *BaudRateMenu = new TMenu;
    BaudRateMenu->Name = "BaudRate";
    BaudRateMenu->CurrentItem = AllData->getBaudRateIndex();

    BaudRateMenu->Item.append({"9600 bps", BR9600});
    BaudRateMenu->Item.append({"19200 bps", BR19200});
    BaudRateMenu->Item.append({"57600 bps", BR57600});
    BaudRateMenu->Item.append({"115200 bps", BR115200});
    BaudRateMenu->Item.append({"Return back", FSelectSettings});
    BaudRateMenu->Item.append({"To main menu", FSelectMainMenu});

    setMenu(BaudRateMenu);
}

//Ініціалізація для показу меню вибору режиму крокового двигуна
void MainClass::selectSetStepMode()
{
    TMenu *StepModeMenu = new TMenu;
    StepModeMenu->Name = "Step mode";
    StepModeMenu->CurrentItem = AllData->getMS();

    StepModeMenu->Item.append({"Full step", SMFullStep});
    StepModeMenu->Item.append({"Half step", SMHalfStep});
    StepModeMenu->Item.append({"Quarter step", SMQuarterStep});
    StepModeMenu->Item.append({"Microstep", SMMicroStep});
    StepModeMenu->Item.append({"Return back", FSelectSettings});
    StepModeMenu->Item.append({"To main menu", FSelectMainMenu});

    setMenu(StepModeMenu);
}

//Обрали ручний режим управління голівкою
void MainClass::toMoving()
{
    Status = SMoving;
    cnc->setGetPos(true);
    printMoving();
}

//Додавання нової цифри до числа, що вводиться з клавіатури
void MainClass::addNumberToEdit(int digit)
{
    if (CurrentEdit.value.length()<8)
        CurrentEdit.value += QString::number(digit);
    printEdit();
}

//Збереження редагованого числа
void MainClass::saveEditValue()
{
    switch (CurrentEdit.type) {
    case EMaxStepsX:
        AllData->setMaxCountStepsX(CurrentEdit.value.toInt());
        selectSettigns();
        break;
    case EMaxStepsY:
        AllData->setMaxCountStepsY(CurrentEdit.value.toInt());
        selectSettigns();
        break;
    case EMaxMPSX:
        AllData->setMaxSpeedPerX(CurrentEdit.value.toInt());
        selectSettigns();
        break;
    case EMinMPSX:
        AllData->setMinSpeedPerX(CurrentEdit.value.toInt());
        selectSettigns();
        break;
    case ENskipStepY:
        AllData->setSkippedYSteps(CurrentEdit.value.toInt());
        selectSettigns();
        break;
    case ESkipImgLine:
        AllData->setSkippedLines(CurrentEdit.value.toInt());
        selectSettigns();
        break;
    case EWaitTimeHeat:
        AllData->setPrePrintingPause(CurrentEdit.value.toInt());
        selectSettigns();
        break;
    case EReturnLine:
        cnc->startPrint(lines, CurrentEdit.value.toInt());
        currentLine = CurrentEdit.value.toInt();
        Status = SPrinting;
        printPrinting();
        break;
    case EScreenTime:
        AllData->setScreenTime(CurrentEdit.value.toInt());
        selectSettigns();
        break;
    }
    AllData->saveAll();
}

//Виведення повідомлення на екран
void MainClass::showMessage(QString msg)
{
    emit clearLCD();
    emit printLCD("Notification", 2, 0, 12);
    emit printLCD(msg, 0, 1, 16);
    emit Warning();
    QThread::sleep(3);

    switch (Status) {
        case SMenu: printMenu(); break;
        case SEdit: printEdit(); break;
        case SMoving: printMoving(); break;
        case SPrinting: break;
    }
    emit onBrightLCD();
}

//Отримання даних про аотону позицію голівки на координатній площині
void MainClass::getPos(int X, int Y)
{
    pos.setX(X);
    pos.setY(Y);
    printMoving();
}

void MainClass::connected()
{
    showMessage("Connected!");
}

void MainClass::newYLine(int Y)
{
    currentLine = Y * AllData->getSkippedLines();
    printPrinting();
}

void MainClass::endPrint(bool stopped)
{
    emit onFinalBeeps();
    if (stopped) {
        AllData->setLastLine(currentLine);
        AllData->saveAll();
    }
    selectMainMenu();
}

//Обробка зображення попіксельно і утворення прямих горизонтальних ліній одного кольору
void MainClass::loadImage()
{
    path += CurrentMenu->Item.at(CurrentMenu->CurrentItem).name;

    if ((AllData->getMaxSpeedPerX()<=0) ||
            (AllData->getMinSpeedPerX()<=0) ||
            (AllData->getMaxSpeedPerX()<=AllData->getMinSpeedPerX()) ||
            (AllData->getSkippedLines()<=0) ||
            (AllData->getSkippedYSteps()<=0)) {

        showMessage("Not found config");
    }
    else {
        if (lines==NULL) {
            delete lines;
            lines = NULL;
        }
        lines = new QList<QList<ColorLine*>*>;
        QImage img(path);
        char current, next;
        QPoint beginPoint, endPoint;

        QSize ImgSize;
        ImgSize=img.size();

        if ((AllData->getMaxCountStepsX()<ImgSize.width()) || (AllData->getMaxCountStepsY()<(ImgSize.height()*AllData->getSkippedYSteps())/AllData->getSkippedLines()))
            showMessage("Image too large!");
        int r, g, b;
        for (int y=0; y<img.height(); y++) {
            beginPoint=QPoint(0, y);
            lines->push_back(new QList<ColorLine*>());
            QColor(img.pixel(0, y)).getRgb(&r, &g, &b);\
            current = qRound(static_cast<qreal>(r+g+b)/(768.00f/static_cast<qreal>(AllData->getCColors())));
            for (int x=0; x<img.width(); x++) {
                QColor(img.pixel(x, y)).getRgb(&r, &g, &b);
                next = qRound(static_cast<qreal>(r+g+b)/(768.00f/static_cast<qreal>(AllData->getCColors())));
                if (current!=next) {
                    endPoint=QPoint(x, y);
                    if (beginPoint.x()<endPoint.x())
                        lines->at(y)->push_back(new ColorLine(beginPoint, endPoint, current));
                    current=next;
                    beginPoint=QPoint(x, y);
                }
            }
            endPoint=QPoint(img.width()-1, y);
            lines->at(y)->push_back(new ColorLine(beginPoint, endPoint, current));
        }

        currentLine=0;
    }
    showMessage("Image is load.");

    selectMainMenu();
}

//Встановлення швидкості передачі даних
void MainClass::setBaudRate()
{
    int BaudRate = 0;
    switch (CurrentMenu->Item.at(CurrentMenu->CurrentItem).func) {
        case BR9600: BaudRate = 9600; break;
        case BR19200: BaudRate = 19200; break;
        case BR57600: BaudRate = 57600; break;
        case BR115200: BaudRate = 115200; break;
        default:
        break;
    }
    AllData->setBaudRate(BaudRate);
    AllData->setBaudRateIndex(CurrentMenu->CurrentItem);
    AllData->saveAll();
    selectSettigns();
}

//Встановлення режиму роботи двигуна
void MainClass::setStepMode()
{
    unsigned char StepMode = 0;
    switch (CurrentMenu->Item.at(CurrentMenu->CurrentItem).func) {
        case SMFullStep: StepMode = 0; break;
        case SMHalfStep: StepMode = 1; break;
        case SMQuarterStep: StepMode = 2; break;
        case SMMicroStep: StepMode = 3; break;
        default:
        break;
    }
    AllData->setMS(StepMode);
    AllData->saveAll();
    cnc->setMS();
    selectSettigns();
}

//Початок випалювання
void MainClass::startBurn()
{
    if (lines == NULL) {
        showMessage("Image not opened");
        return;
    }
    cnc->startPrint(lines);
    currentLine = 0;
    Status = SPrinting;
    printPrinting();
    emit onBrightLCD();
}

//Повертання до нульової позиції
void MainClass::returnToZero()
{
    cnc->returnToZero();
}

//Обробка сигналів клавіатури
void MainClass::keyPressed(int k)
{
    emit onBrightLCD();
    if (Status == SMenu) {
        emit offFinalBeeps();

        if (k == keyboardUI::KEY_4) prevItem();
        if (k == keyboardUI::KEY_6) nextItem();

        if (k == keyboardUI::KEY_5) {
            switch (CurrentMenu->Item.at(CurrentMenu->CurrentItem).func) {
                case FSelectMainMenu: selectMainMenu(); break;
                case FSelectUSB: selectUSB(); break;
                case FSelectFile: selectFile(); break;
                case FLoadImage: loadImage(); break;
                case FSelectSettings: selectSettigns(); break;
                case FSelectStepMode: selectSetStepMode(); break;
                case FSelectBaudRate: selectSetBaudRate(); break;
                case FMoving: toMoving(); break;
                case FBurn: startBurn(); break;
                case FShutDown: emit doShutDown(); break;
                case FReturn:
                case FEditMaxMPSX:
                case FEditMaxStepsX:
                case FEditMaxStepsY:
                case FEditMinMPSX:
                case FEditNSkipStepY:
                case FEditSkipImgLine:
                case FEditWaitTimeHeat:
                case FEditScreenTime:
                    setEdit();
                    break;
                case BR9600:
                case BR19200:
                case BR57600:
                case BR115200:
                    setBaudRate();
                    break;
                case SMFullStep:
                case SMHalfStep:
                case SMQuarterStep:
                case SMMicroStep:
                    setStepMode();
                    break;
                case FNone: break;
                default:
                break;
            }
        }
        return;
    }
    if (Status == SEdit) {
        if (k == keyboardUI::KEY_0) addNumberToEdit(0);
        if (k == keyboardUI::KEY_1) addNumberToEdit(1);
        if (k == keyboardUI::KEY_2) addNumberToEdit(2);
        if (k == keyboardUI::KEY_3) addNumberToEdit(3);
        if (k == keyboardUI::KEY_4) addNumberToEdit(4);
        if (k == keyboardUI::KEY_5) addNumberToEdit(5);
        if (k == keyboardUI::KEY_6) addNumberToEdit(6);
        if (k == keyboardUI::KEY_7) addNumberToEdit(7);
        if (k == keyboardUI::KEY_8) addNumberToEdit(8);
        if (k == keyboardUI::KEY_9) addNumberToEdit(9);

        if (k == keyboardUI::KEY_D) {
            CurrentEdit.value.resize(CurrentEdit.value.length()-1);
            printEdit();
        }
        if (k == keyboardUI::KEY_A) saveEditValue();
        if (k == keyboardUI::KEY_C) selectMainMenu();
        if (k == keyboardUI::KEY_B)
            switch (CurrentEdit.type) {
            case EReturnLine:
                selectMainMenu();
                break;
            default:
                selectSettigns();
                break;
            }
        return;
    }
    if (Status == SMoving) {
        if (k == keyboardUI::KEY_4) cnc->move(cncright);
        if (k == keyboardUI::KEY_2) cnc->move(cncdown);
        if (k == keyboardUI::KEY_6) cnc->move(cncleft);
        if (k == keyboardUI::KEY_8) cnc->move(cncup);

        if (k == keyboardUI::KEY_0) cnc->setCurrentPosAsZero();
        if (k == keyboardUI::KEY_B) {
            cnc->setGetPos();
            selectMainMenu();
        }

        return;
    }
    if (Status == SPrinting) {
        if (k == keyboardUI::KEY_C) cnc->stop();
    }
}

void MainClass::keyRealease(int)
{
    if (Status == SMoving) cnc->move(cncendmove);
}
