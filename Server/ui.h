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

public slots:
    void run();

signals:
    void doWorkSig();
    void keyPressed(int);
    void keyRelease(int);
    void beep();
};

#endif // UI_H
