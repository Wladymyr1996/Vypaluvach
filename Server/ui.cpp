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

#include "ui.h"
#include "gpio/gpio_lib.c"
#include "i2c/i2c_lib.c"
#include <QThread>
#include <QDebug>
#include <cnc.h>

#define ELLIPSIS (char)0x05

//Стоврення додаткового набору символів для "…" і шкали прогресу
unsigned char mySymbol[7][8] = {{0x1F, 0x00, 0x10, 0x10, 0x10, 0x00, 0x1F, 0x00},
                                {0x1F, 0x00, 0x18, 0x18, 0x18, 0x00, 0x1F, 0x00},
                                {0x1F, 0x00, 0x1C, 0x1C, 0x1C, 0x00, 0x1F, 0x00},
                                {0x1F, 0x00, 0x1E, 0x1E, 0x1E, 0x00, 0x1F, 0x00},
                                {0x1F, 0x00, 0x1F, 0x1F, 0x1F, 0x00, 0x1F, 0x00},
                                {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x00},
                                {0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00}};

int fd;
bool inited = false;

lcdUI::lcdUI(QObject *parent) : QObject(parent) {
    fd = i2c_open((char *)"/dev/i2c-0", 0x27);

    //Ініціалізація дисплею
    {
        BrightOff();
        QThread::sleep(1);
        lcdWriteByte(0x20 | (bright << BRIGHT));
        lcdWriteByte(0x20 | (bright << BRIGHT) | (1 << E));
        lcdWriteByte(0x20 | (bright << BRIGHT));
        QThread::sleep(1);
        lcdWriteCommand(0x28);
        QThread::usleep(5000);
        lcdWriteCommand(0x08);
        QThread::usleep(5000);
        lcdWriteCommand(0x01);
        QThread::usleep(5000);
        lcdWriteCommand(0x06);
        QThread::usleep(10000);
        lcdWriteCommand(0x0C);
        QThread::usleep(100000);
    }

    //Завантаження в пам'ять CGRAM набору символів
    for (int i=0; i<7; i++) {
        lcdWriteCommand(0x40 | (i*8));
        for (int j=0; j<8; j++) {
            lcdWriteChar(mySymbol[i][j]);
        }
    }

    BrightOn();

    print(APPNAME, 3, 0);
    print("Version", 0, 1);
    print(VERSION, 16-QString(VERSION).length(), 1);
}

void lcdUI::lcdWriteByte(uint8_t data) {
    i2c_send(fd, &data, 1);
    usleep(10);
}

void lcdUI::lcdWriteCommand(unsigned char command)
{
    lcdWriteByte((command & 0xF0) | (bright << BRIGHT));
    lcdWriteByte((command & 0xF0) | (bright << BRIGHT) | (1 << E));
    lcdWriteByte((command & 0xF0) | (bright << BRIGHT));

    lcdWriteByte(((command & 0x0F) << 4) | (bright << BRIGHT));
    lcdWriteByte(((command & 0x0F) << 4) | (bright << BRIGHT) | (1 << E));
    lcdWriteByte(((command & 0x0F) << 4) | (bright << BRIGHT));
}

void lcdUI::lcdWriteChar(unsigned char symbol)
{
    lcdWriteByte((symbol & 0xF0) | (bright << BRIGHT) | (1 << RS));
    lcdWriteByte((symbol & 0xF0) | (bright << BRIGHT) | (1 << E) | (1 << RS));
    lcdWriteByte((symbol & 0xF0) | (bright << BRIGHT) | (1 << RS));

    lcdWriteByte(((symbol & 0x0F) << 4) | (bright << BRIGHT) | (1 << RS));
    lcdWriteByte(((symbol & 0x0F) << 4) | (bright << BRIGHT) | (1 << E) | (1 << RS));
    lcdWriteByte(((symbol & 0x0F) << 4) | (bright << BRIGHT) | (1 << RS));
}

void lcdUI::lcdWriteBright()
{
    lcdWriteByte(bright << BRIGHT);
}

void lcdUI::print(QString string, int x, int y, int width)
{
    if ((y>1) || (y<0)) y = 0;
    if ((x<0) || (x>15)) x = 0;
    if (width < 2) width = 2;

    //Якщо рядок більший за вказану ширину, зменшуємо і додаємо "…"
    if (string.length()>width) {
        string.resize(width-1);
        string += ELLIPSIS;
    }
    unsigned int addr = x + 0x40 * y; //Знаходження адреси DDRAM

    lcdWriteCommand(0x80 | addr);
    QThread::usleep(40);

    for (int i=0; i<string.length(); i++) {
        lcdWriteChar(string.toStdString().c_str()[i]);
    }
}

//вмикання підсвічування дисплею
void lcdUI::BrightOn()
{
    if (brightTimer == NULL) {
        brightTimer = new QTimer;
        brightTimer->moveToThread(this->thread());
        connect(brightTimer, SIGNAL(timeout()),
                SLOT(BrightOff()));
        connect(this, SIGNAL(brightTimerStart(int)),
                brightTimer, SLOT(start(int)));
        connect(this, SIGNAL(brightTimerStop()),
                brightTimer, SLOT(stop()));

    }

    if (AllData->getScreenTime() != 0)
        emit brightTimerStart(AllData->getScreenTime()*1000);
    else
        emit brightTimerStop();
    bright = 1;
    lcdWriteBright();
}

void lcdUI::BrightOff()
{
    bright = 0;
    lcdWriteBright();
}

//Очищення дисплею
void lcdUI::clear()
{
    lcdWriteCommand(0x01);
    QThread::msleep(2);
}

keyboardUI::keyboardUI(QObject *parent) : QObject(parent) {
    if (!inited) sunxi_gpio_init();

    //Налаштування портів
    {
        sunxi_gpio_set_cfgpin(SUNXI_GPG(6), SUNXI_GPIO_OUTPUT);
        sunxi_gpio_set_cfgpin(SUNXI_GPG(7), SUNXI_GPIO_OUTPUT);
        sunxi_gpio_set_cfgpin(SUNXI_GPA(7), SUNXI_GPIO_OUTPUT);
        sunxi_gpio_set_cfgpin(SUNXI_GPA(19), SUNXI_GPIO_OUTPUT);
        sunxi_gpio_output(SUNXI_GPG(6), 0);
        sunxi_gpio_output(SUNXI_GPG(7), 0);
        sunxi_gpio_output(SUNXI_GPA(7), 0);
        sunxi_gpio_output(SUNXI_GPA(19), 0);

        sunxi_gpio_set_cfgpin(SUNXI_GPA(14), SUNXI_GPIO_INPUT);
        sunxi_gpio_set_cfgpin(SUNXI_GPA(2), SUNXI_GPIO_INPUT);
        sunxi_gpio_set_cfgpin(SUNXI_GPA(10), SUNXI_GPIO_INPUT);
        sunxi_gpio_set_cfgpin(SUNXI_GPA(13), SUNXI_GPIO_INPUT);
    }

    connect(&keyReadTimer, SIGNAL(timeout()),
            SLOT(run()));
    keyReadTimer.start(50);
}

//Надискання на кнопку клавіатури
void keyboardUI::click(keyboardUI::Key k, int GPIO)
{
    emit keyPressed(k);
    emit beep();
    QThread::msleep(50);
    while (sunxi_gpio_input(SUNXI_GPA(GPIO)) == 1);
    emit keyRelease(k);
    QThread::msleep(50);
}

//Цикл обробки натискань клаіатури
void keyboardUI::run() {
        sunxi_gpio_output(SUNXI_GPA(19), 0);
        sunxi_gpio_output(SUNXI_GPG(6), 1);

        if (sunxi_gpio_input(SUNXI_GPA(10)) == 1) click(KEY_D, 10);
        if (sunxi_gpio_input(SUNXI_GPA(13)) == 1) click(KEY_C, 13);
        if (sunxi_gpio_input(SUNXI_GPA(2)) == 1) click(KEY_B, 2);
        if (sunxi_gpio_input(SUNXI_GPA(14)) == 1) click(KEY_A, 14);

        sunxi_gpio_output(SUNXI_GPG(6), 0);
        sunxi_gpio_output(SUNXI_GPG(7), 1);

        if (sunxi_gpio_input(SUNXI_GPA(10)) == 1) click(KEY_HASH, 10);
        if (sunxi_gpio_input(SUNXI_GPA(13)) == 1) click(KEY_9, 13);
        if (sunxi_gpio_input(SUNXI_GPA(2)) == 1) click(KEY_6, 2);
        if (sunxi_gpio_input(SUNXI_GPA(14)) == 1) click(KEY_3, 14);

        sunxi_gpio_output(SUNXI_GPG(7), 0);
        sunxi_gpio_output(SUNXI_GPA(7), 1);

        if (sunxi_gpio_input(SUNXI_GPA(10)) == 1) click(KEY_0, 10);
        if (sunxi_gpio_input(SUNXI_GPA(13)) == 1) click(KEY_8, 13);
        if (sunxi_gpio_input(SUNXI_GPA(2)) == 1) click(KEY_5, 2);
        if (sunxi_gpio_input(SUNXI_GPA(14)) == 1) click(KEY_2, 14);

        sunxi_gpio_output(SUNXI_GPA(7), 0);
        sunxi_gpio_output(SUNXI_GPA(19), 1);

        if (sunxi_gpio_input(SUNXI_GPA(10)) == 1) click(KEY_STAR, 10);
        if (sunxi_gpio_input(SUNXI_GPA(13)) == 1) click(KEY_7, 13);
        if (sunxi_gpio_input(SUNXI_GPA(2)) == 1) click(KEY_4, 2);
        if (sunxi_gpio_input(SUNXI_GPA(14)) == 1) click(KEY_1, 14);
}

beepUI::beepUI(QObject *parent) : QObject(parent)
{
    //Ініціалізація
    sunxi_gpio_set_cfgpin(SUNXI_GPA(15), SUNXI_GPIO_OUTPUT);
}

beepUI::~beepUI()
{
    if (finalBeepsTimer != NULL) delete finalBeepsTimer;
}

//Короткочасний звуковий сигнал
void beepUI::beep()
{
    sunxi_gpio_output(SUNXI_GPA(15), 1);
    QThread::msleep(100);
    sunxi_gpio_output(SUNXI_GPA(15), 0);
}

//Сигнал успіху
void beepUI::Succes()
{
    beep();
    QThread::msleep(100);
    beep();
}

//Сигнал привернення уваги
void beepUI::Warning()
{
    beep();
    QThread::msleep(100);
    sunxi_gpio_output(SUNXI_GPA(15), 1);
    QThread::msleep(200);
    sunxi_gpio_output(SUNXI_GPA(15), 0);
}

//Запуск циклу сигналів "Успіху" після закінчення випалювання
void beepUI::Final()
{
    if (finalBeepsTimer == NULL) {
        finalBeepsTimer = new QTimer;
        connect(finalBeepsTimer, SIGNAL(timeout()),
                SLOT(Succes()));
    }
    finalBeepsTimer->start(1000);
}

//Зупинка циклу сигналів "Успіху"
void beepUI::Stop()
{
    if (finalBeepsTimer != NULL)
        finalBeepsTimer->stop();
}

shutdownUI::shutdownUI(QObject *parent) : QObject(parent)
{
    //Ініціалізація
    sunxi_gpio_set_cfgpin(SUNXI_GPA(6), SUNXI_GPIO_OUTPUT);
    sunxi_gpio_output(SUNXI_GPA(6), 1);
}

void shutdownUI::doShutDown()
{
    //Вимикання
    QThread::msleep(100);
    cnc->shutDown();
    QThread::sleep(1);
    QProcess::startDetached("reboot");
}
