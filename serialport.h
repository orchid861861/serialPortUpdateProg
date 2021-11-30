#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>


class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    SerialPort();
    void InitSerialPort(const QSerialPortInfo &serialPortInfo);

};

#endif // SERIALPORT_H
