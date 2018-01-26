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

#ifndef UI_H
#define UI_H
#define E 0x02
#define RS 0x00
#define BRIGHT 0x03

#include <QObject>
#include <QTimer>
#include <alldata.h>
#include <QProcess>

//Клас відповідальний за коректне вимикання ЧПК
class shutdownUI : public QObject
{
    Q_OBJECT
public:
    explicit shutdownUI(QObject *parent = nullptr);

public slots:
    void doShutDown();
};

//Клас відповідальний за звукові сповіщення
class beepUI : public QObject
{
    Q_OBJECT
public:
    explicit beepUI(QObject *parent = nullptr);
    ~beepUI();

private:
    QTimer *finalBeepsTimer = NULL;

public slots:
    void beep();
    void Succes();
    void Warning();
    void Final();
    void Stop();
};

//Клас відповідальний за вивід інформації на екран
class lcdUI : public QObject
{
    Q_OBJECT
public:
    explicit lcdUI(QObject *parent = nullptr);

private:
    QTimer *brightTimer = NULL;
    unsigned char bright;
    void lcdWriteByte(uint8_t data);
    void lcdWriteCommand(unsigned char command);
    void lcdWriteChar(unsigned char symbol);
    void lcdWriteBright();

public slots:
    void print(QString string, int x = -1, int y = -1, int width = 16);
    void BrightOn();
    void BrightOff();
    void clear();


signals:
    void brightTimerStart(int);
    void brightTimerStop();
};

//Клас відповідалний за клавіатру
class keyboardUI : public QObject
{
    Q_OBJECT

public:
    explicit keyboardUI(QObject *parent = nullptr);
    enum Key {KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_A, KEY_B, KEY_C, KEY_D, KEY_STAR, KEY_HASH};

private:
    void click(Key k, int GPIO);
    QTimer keyReadTimer;

public slots:
    void run();

signals:
    void doWorkSig();
    void keyPressed(int);
    void keyRelease(int);
    void beep();
};

#endif // UI_H
