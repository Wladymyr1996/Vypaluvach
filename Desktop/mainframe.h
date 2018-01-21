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

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "mainwidget.h"
#include "settingswindow.h"
#include "helpwindow.h"
#include "aboutwindow.h"
#include "cncsettingswindow.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>

class StatusPos : public QLabel {
    Q_OBJECT

public:
    StatusPos(QString caption);

public slots:
    void newPos(int x, int y);
};

class StatusConnect : public QLabel {
    Q_OBJECT

public:
    StatusConnect(QString caption);

protected:
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void doConnect();
    void doDisconnect();

public slots:
    void connected();
    void disconnected();
};

namespace Ui {
class MainFrame;
}

class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void on_actionOpenImage_triggered();
    void on_actionClose_app_triggered();
    void on_actionApp_settings_triggered();
    void on_actionAbout_author_triggered();
    void on_action_Help_triggered();
    void on_action_Serial_settings_triggered();
    void on_action_Proportion_test_triggered();
    void on_actionSetCenter_triggered();
    void on_actionBegin_burn_triggered();
    void on_actionContinue_burn_triggered();
    void on_actionEnglish_triggered();
    void on_actionUkrainian_triggered();
    void on_actionRussian_triggered();

    void onAppSettingsClose();
    void onCNCSettingsClose();
    void onHelpClose();
    void onAboutClose();
    void onUpdateStatusBar();
    void onEndPrint();
    void onBurnTimer();

    void on_actionReturn_to_zero_triggered();

private:
    Ui::MainFrame *ui;
    //QPicture *pic;
    MainWidget *widget;
    int beginLine;
    AboutWindow *AboutWin;
    SettingsForm *AppSettingsWin;
    CNCsettingswindow *CNCSettingsWin;
    HelpWindow *HelpWin;

    StatusConnect *Status;
    StatusPos *CNCPosition;
    QLabel *BurnTime, *RemainingTime, *Progress, *ProgressProcent;
    qint64 beginTime;
    QTimer BurnTimer;
};

#endif // MAINFRAME_H
