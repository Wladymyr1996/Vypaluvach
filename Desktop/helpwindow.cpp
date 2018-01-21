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

#include "helpwindow.h"
#include "alldata.h"

HelpWindow::HelpWindow(QRect parent_geometry, QWidget *parent) : QWidget(parent)
{
    setWindowTitle(QString(tr("Help") + " - " + APPNAME));
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowIcon(QIcon(":/img/help.png"));
    setGeometry(parent_geometry.x()+(parent_geometry.width()-WIDTH)/2,
                parent_geometry.y()+(parent_geometry.height()-HEIGHT)/2, WIDTH, HEIGHT);
    setFixedSize(WIDTH, HEIGHT);

    QTextEdit *txtedt = new QTextEdit(this);
    txtedt->setPlainText(tr("1. Program Settings -------------------\n"
                         "1.1. The maximum number of steps can be entered in order to notify the user when the image is larger than allowed.\n"
                         "1.2. The maximum and minimum speeds are entered to determine the speed limits. The smaller the number, the faster the sting moves, because the speed is measured in milliseconds between the steps.\n"
                         "1.3. Proportion is determined by the experimental method. Put \"1\" in the main window menu and run the test proportion and wait for the completion of all actions. Must print a square with sides of 1000x1000 steps. After need to take a ruler and measure the length of the two adjacent sides. Now we need to find a number that must be multiplied by Y so that all sides are equal.\n"
                         "1.4. The number of skipped rows depends on the thickness of the sting, you need to determine it experimentally until you get the desired result.\n"
                         "\n"
                         "2. Configure the connection ---------------------\n"
                         "2.1. To configure the connection, in the menu, open \"Settings -> Connection settings\". Select the desired port (by default ttyUSB0), if necessary, scan the ports again (the CNC must be connected to the computer). And click \"Apply\".\n"
                         "\n"
                         "3. Burning -------------------------------\n"
                         "3.1. Open the image (File -> Open image), then wait until the program scans the image. Then use the arrows to select the initial position for burning. We set this position as zero (Control -> Set the current position as zero). And in order to start the burning process (Control -> Start Burning).\n"
                         "3.2. Burning goes automatically. Each time, the sting goes to the ruler with a cleaver. Purification goes in two stages: 300 steps to the left of zero (since you need to calculate that the zero of the coordinate plane should be farther from the edge). As the burnout progresses, the red line marks the row that is currently being burned.\n"
                         "3.3. In case of an unforeseen situation, when the burning was left, it can be continued. If the red line does not indicate the place from which you would like to continue burning, you can set it by clicking the mouse in the desired place of renewal, and set the arrows, if necessary, sting at zero on X, and on Y in the row where the burning was interrupted . After that, click \"Management -> Resume burning\"\n"
                         "\n"
                         "4. Image Types -------------------------\n"
                         "The program \"Vypaluvach\" can read more image types like *.bmp, *jpg, *png without information about the alpha channel. (Alpha chanel be ignored)"));
    txtedt->setGeometry(0, 0, WIDTH, HEIGHT);
}

HelpWindow::~HelpWindow()
{
    emit closeWindow();
}

void HelpWindow::closeEvent(QCloseEvent *)
{
    delete this;
}

