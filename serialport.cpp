#include "serialport.h"

SerialPort::SerialPort():QSerialPort()
{
    
}

void SerialPort::InitSerialPort(QString port_name)
{
    setPortName(port_name);
    setBaudRate(QSerialPort::Baud115200);
    setStopBits(QSerialPort::OneStop);
    setParity(QSerialPort::NoParity);
}

