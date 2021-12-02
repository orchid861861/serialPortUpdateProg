#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>

class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    SerialPort();
    void InitSerialPort(QString port_name);


};

#endif // SERIALPORT_H
