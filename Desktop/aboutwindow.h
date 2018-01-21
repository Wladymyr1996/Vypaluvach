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

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QTextEdit>

class AboutWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AboutWindow(QRect parent_geometry, QWidget *parent = 0);
    ~AboutWindow();

protected:
    void closeEvent(QCloseEvent *);

private:
    static const int WIDTH=300;
    static const int HEIGHT=200;

signals:
    void closeWindow();
};

#endif // ABOUTWINDOW_H
