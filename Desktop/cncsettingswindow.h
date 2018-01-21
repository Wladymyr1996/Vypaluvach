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

#ifndef CNCSETTINGSWINDOW_H
#define CNCSETTINGSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QSettings>

class CNCsettingswindow : public QWidget
{
    Q_OBJECT
public:
    explicit CNCsettingswindow(QRect ParrentGeometry, QWidget *parent = nullptr);
    ~CNCsettingswindow();

protected:
    void closeEvent(QCloseEvent *);

private:
    void scan();
    QComboBox *cbBaudRate, *cbPort;
    QPushButton *pbScan, *pbApply;

private slots:
    void doScan();
    void doApply();

signals:
    void closeWindow();
};

#endif // CNCSETTINGSWINDOW_H
