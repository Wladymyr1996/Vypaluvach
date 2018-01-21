#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QSerialPort>

class MySerialPort : public QSerialPort
{
public:
    MySerialPort();
    bool MyIsOpen();
    void MyClose();
    void MySetPortName(QString name);
    void MySetBaudRate(int rate);
    void MyOpen();
    void MyWrite(QByteArray data);
};

#endif // MYSERIALPORT_H
