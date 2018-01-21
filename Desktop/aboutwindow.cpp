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


#include "aboutwindow.h"
#include "alldata.h"

AboutWindow::AboutWindow(QRect parent_geometry, QWidget *parent) : QWidget(parent)
{
    setWindowTitle(QString(tr("About") + " " + APPNAME));
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowIcon(QIcon(":/img/help.png"));
    setGeometry(parent_geometry.x()+(parent_geometry.width()-WIDTH)/2,
                parent_geometry.y()+(parent_geometry.height()-HEIGHT)/2, WIDTH, HEIGHT);
    setFixedSize(WIDTH, HEIGHT);

    QLabel *img = new QLabel("<img src=':/img/logo.png'/>", this);
    img->setGeometry(0, 0, 300, 48);
    QTextEdit *txtedt = new QTextEdit(this);
    txtedt->setPlainText(tr("Programm ") + APPNAME + tr(" can distributed free, and should be available to everyone.\n"
                         "\n"
                         "Author - Stadnyk Volodymyr.\n"
                         "e-mail - Wladymyr1996@gmail.com\n"
                         "Version - ") + VERSION + "\n" +
                         tr("License - GNU General Public License v3.0\n"
                         "\n"
                         "Thanks: Rick101\n"));
    txtedt->setGeometry(0, 48, 300, 152);

}

AboutWindow::~AboutWindow()
{
    emit closeWindow();
}

void AboutWindow::closeEvent(QCloseEvent *)
{
    delete this;
}
