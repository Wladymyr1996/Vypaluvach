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

#include "mainframe.h"
#include "ui_mainframe.h"
#include <QDateTime>
#include <QMessageBox>
#include "alldata.h"
#include <QThread>


//Створнення головного вікна
MainFrame::MainFrame(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainFrame)
{
    //Створення глобального класу загалнодоступних даних даних
    AllData = new TAllData(this);

    //Налаштування вікна
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/icon.png"));
    setWindowTitle(QString(APPNAME) + " v"+ VERSION);
    setGeometry(AllData->getWindowGeometry());
    setMinimumHeight(ui->menuBar->height()+ui->statusBar->height()+100);

    //Налаштування додаткових класів
    cnc = new CNC(this);

    widget = new MainWidget();
    setCentralWidget(widget);
    widget->setFocus();

    //Налаштування інформаційної панелі
    Status = new StatusConnect(tr("Disconnected"));
    Status->setFixedWidth(115);
    Status->setCursor(Qt::PointingHandCursor);
    Status->setToolTip(tr("Try connect!"));
    CNCPosition = new StatusPos("X: 0; Y: 0");
    CNCPosition->setFixedWidth(150);
    BurnTime = new QLabel(tr("Burn time: unkown"));
    BurnTime->setAlignment(Qt::AlignRight);
    RemainingTime = new QLabel(tr("Remaining time: uknown"));
    RemainingTime->setAlignment(Qt::AlignLeft);
    Progress = new QLabel(tr("worked 0/0"));
    Progress->setAlignment(Qt::AlignRight);
    ProgressProcent = new QLabel(tr("(0 %)"));
    ProgressProcent->setAlignment(Qt::AlignRight);
    ProgressProcent->setFixedWidth(50);

    statusBar()->addWidget(Status, 1);
    statusBar()->addWidget(CNCPosition, 2);
    statusBar()->addWidget(BurnTime, 3);
    statusBar()->addWidget(RemainingTime, 3);
    statusBar()->addWidget(Progress, 5);
    statusBar()->addWidget(ProgressProcent, 5);

    //ініціалізація вказівників
    AboutWin=NULL;
    AppSettingsWin=NULL;
    HelpWin=NULL;
    CNCSettingsWin=NULL;


    connect(widget, SIGNAL(NewLineSet()),
            SLOT(onUpdateStatusBar()));
    connect(cnc, SIGNAL(isConnect()),
            Status, SLOT(connected()));
    connect(cnc, SIGNAL(isDisconnect()),
            Status, SLOT(disconnected()));
    connect(cnc, SIGNAL(newPosition(int,int)),
            CNCPosition, SLOT(newPos(int,int)));
    connect(cnc, SIGNAL(endPrint(bool)),
            SLOT(onEndPrint()));
    connect(&BurnTimer, SIGNAL(timeout()),
            SLOT(onBurnTimer()));
}

MainFrame::~MainFrame()
{
    //Зберігаємо геометрію вікна
    AllData->setWindowGeometry(geometry());

    //Провсяк випадо видалємо всі дані і в кучі
    if (AboutWin!=NULL) delete AboutWin;
    if (AppSettingsWin!=NULL) delete AppSettingsWin;
    if (HelpWin!=NULL) delete HelpWin;
    if (CNCSettingsWin!=NULL) delete CNCSettingsWin;

    delete ui;
}

void MainFrame::closeEvent(QCloseEvent *)
{
    if (cnc->isConnected()) cnc->close();
    QApplication::quit();
}

void MainFrame::on_actionOpenImage_triggered()
{
    QString FileName = QFileDialog::getOpenFileName(widget,
                                                    tr("Open Image"),
                                                    QString(),
                                                    tr("Image (*.jpg *.jpeg *.png *.bmp);; All files (*.*)"));
    if (!FileName.isEmpty()) widget->setPicture(FileName);
}

void MainFrame::onUpdateStatusBar()
{
    static int old_line=-1;
    if (old_line!=widget->getCurrentLine()){
        Progress->setText(tr("worked ") +
                          QString::number(widget->getCurrentLine()) +
                          QString("/") +
                          QString::number(widget->getCountLines()));
        ProgressProcent->setText(QString("(") +
                                 QString::number(widget->getProgress()) +
                                 QString(" %)"));
        old_line = widget->getCurrentLine();
    }
}

void MainFrame::on_actionClose_app_triggered()
{
    this->close();
}

void MainFrame::on_actionApp_settings_triggered()
{
    //Відкриття вікна налаштувань якщо більше таких вікон не вікдрито
    if (AppSettingsWin==NULL) {
        AppSettingsWin = new SettingsForm(geometry());
        connect (AppSettingsWin, SIGNAL(closeWindow()),
                 this, SLOT(onAppSettingsClose()));
        AppSettingsWin->show();
    }
}

void MainFrame::on_action_Serial_settings_triggered()
{
    if (CNCSettingsWin==NULL) {
        CNCSettingsWin = new CNCsettingswindow(geometry());
        connect (CNCSettingsWin, SIGNAL(closeWindow()),
                 this, SLOT(onCNCSettingsClose()));
        CNCSettingsWin->show();
    }
}

void MainFrame::on_action_Help_triggered()
{
    if (HelpWin==NULL) {
        HelpWin = new HelpWindow(geometry());
        connect (HelpWin, SIGNAL(closeWindow()),
                 this, SLOT(onHelpClose()));
        HelpWin->show();
    }
}

void MainFrame::on_actionAbout_author_triggered()
{
    if (AboutWin==NULL) {
        AboutWin = new AboutWindow(geometry());
        connect (AboutWin, SIGNAL(closeWindow()),
                 this, SLOT(onAboutClose()));
        AboutWin->show();
    }
}

void MainFrame::onAppSettingsClose()
{
    AppSettingsWin = NULL;
}

void MainFrame::onCNCSettingsClose()
{
    CNCSettingsWin = NULL;
}

void MainFrame::onHelpClose()
{
    HelpWin = NULL;
}

void MainFrame::onAboutClose()
{
    AboutWin = NULL;
}

void MainFrame::on_action_Proportion_test_triggered()
{
    cnc->testProportion();
}

void MainFrame::on_actionSetCenter_triggered()
{
    cnc->setCurrentPosAsZero();
}

void MainFrame::on_actionBegin_burn_triggered()
{
    //Почати випалювання, якщо ЧПК не зайнятий і підключений до комп'ютера
    if ((!cnc->isBusy()) && (cnc->isConnected())){
        //Починаємо з нульової (першої) лінії
        beginLine = 0;
        cnc->startPrint(widget->getLines());
        //Запускаємо лічильник часу випалювання і очікування
        beginTime = QDateTime::currentMSecsSinceEpoch();
        BurnTimer.start(1000);
    }
}

void MainFrame::on_actionContinue_burn_triggered()
{
    if ((!cnc->isBusy()) && (cnc->isConnected())) {
        //Те саме, тільки початкова лініє - поточна
        beginLine = widget->getCurrentLine()-1;
        cnc->startPrint(widget->getLines(), beginLine);
        beginTime = QDateTime::currentMSecsSinceEpoch();
        BurnTimer.start(1000);
    }
}

void MainFrame::onEndPrint()
{
    //Після завершення випалювання зупиняємо таймер
    BurnTimer.stop();
    RemainingTime->setText(tr("Remaining time: uknown"));
}

void MainFrame::onBurnTimer()
{
    if (cnc->isBusy()) {
        //Поточний час
        quint64 BTime = QDateTime::currentMSecsSinceEpoch() - beginTime;
        BurnTime->setText(tr("Burn time: ") + QDateTime::fromMSecsSinceEpoch(BTime).toUTC().toString("HH:mm:ss"));

        //Розрахунок часу, що залишився до кінця
        if (widget->getCurrentLine()<beginLine) beginLine = widget->getCurrentLine();
        quint64 RTime = (BTime / (widget->getCurrentLine() - beginLine+1)) * (widget->getCountLines() - beginLine) - BTime;
        RemainingTime->setText(tr("Remaining time: ") + QDateTime::fromMSecsSinceEpoch(RTime).toUTC().toString("HH:mm:ss"));
    }
}

void MainFrame::on_actionEnglish_triggered()
{
    //Зміна мови
    AllData->AppSettings->setValue("/AppSettings/Language", "en");
    QMessageBox::information(widget, "Vypaluvach", "Please, restart the app to apply new settigs!");
}

void MainFrame::on_actionUkrainian_triggered()
{
    AllData->AppSettings->setValue("/AppSettings/Language", "uk");
    QMessageBox::information(widget, "Випалювач", "Будь ласка, перезапустіть цей додаток для застосування нових налаштувань!");
}

void MainFrame::on_actionRussian_triggered()
{
    AllData->AppSettings->setValue("/AppSettings/Language", "ru");
    QMessageBox::information(widget, "Vypaluvach", "Пожалуйста, перезагрузите это приложение, для приминения новых настроек!");
}

////////////////////////////////Status connect

StatusConnect::StatusConnect(QString caption) : QLabel(caption) {}

void StatusConnect::mouseReleaseEvent(QMouseEvent *)
{
    if (!cnc->isConnected()) {
        cnc->TryConnect();
    } else {
        cnc->close();
    }
}

void StatusConnect::connected()
{
    setText(tr("Connected"));
    setToolTip(tr("Disconnect!"));
}

void StatusConnect::disconnected()
{
    setText(tr("Disconnected"));
    setToolTip(tr("Try connect!"));
}

////////////////////////////////Status pos

StatusPos::StatusPos(QString caption) : QLabel()
{
    setText(caption);
}

void StatusPos::newPos(int x, int y)
{
    setText(QString("X: " + QString::number(x) +
                    "; Y: " + QString::number(y)));
}

void MainFrame::on_actionReturn_to_zero_triggered()
{
    cnc->returnToZero();
}
