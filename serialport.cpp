#include "serialport.h"

SerialPort::SerialPort():QSerialPort()
{
    
}

void SerialPort::InitSerialPort(QString port_name)
{
    setPortName(port_name);
    setBaudRate(QSerialPort::Baud115200);
    setDataBits(QSerialPort::QSerialPort::Data8);
    setStopBits(QSerialPort::OneStop);
    setParity(QSerialPort::NoParity);


}

