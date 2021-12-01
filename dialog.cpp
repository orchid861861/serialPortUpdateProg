#include "dialog.h"
#include "ui_dialog.h"
#include "serialport.h"
#include <QList>
#include "mynativeeventfilter.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    comList=QSerialPortInfo().availablePorts();
    foreach(const QSerialPortInfo info,comList)
        ui->comboBox->addItem(info.portName());
    port = new SerialPort();

    if(!comList.empty())
    {
        port->InitSerialPort(ui->comboBox->currentText());
        updateComPortConfig();
    }
    else
        clearComPortConfig();
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,&Dialog::setCurrentSerialPortName);


}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::updateComPortConfig()
{
    ui->lineEdit_baundrate->setText(QString("%1").arg(port->baudRate()));
    ui->lineEdit_databit->setText(QString("%1").arg(port->dataBits()));
    ui->lineEdit_stopbit->setText(QString("%1").arg(port->stopBits()));
    ui->lineEdit_parity->setText(QString("%1").arg(port->parity()));
}
void Dialog::clearComPortConfig()
{
    ui->lineEdit_baundrate->setText(QString());
    ui->lineEdit_databit->setText(QString());
    ui->lineEdit_stopbit->setText(QString());
    ui->lineEdit_parity->setText(QString());
}
void Dialog::addSerialPorts(QString comPort)
{
    if(ui->comboBox->findText(comPort) == -1)
        ui->comboBox->addItem(comPort);
}
void Dialog::removeSerialPorts(QString comPort)
{
    int index = ui->comboBox->findText(comPort);
    if(index !=-1)
         ui->comboBox->removeItem(index);
}
 void Dialog::setCurrentSerialPortName(QString port_name)
 {
     if(ui->comboBox->count())
     {
         port->InitSerialPort(port_name);
         updateComPortConfig();
     }
     else
         clearComPortConfig();

 }
