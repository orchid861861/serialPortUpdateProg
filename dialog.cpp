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
        port->InitSerialPort(ui->comboBox->currentText());
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,&Dialog::setCurrentSerialPortName);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::addSerialPorts(QString comPort)
{
    if(ui->comboBox->findText(comPort) == -1)
        ui->comboBox->addItem(comPort);

    if(!comList.empty())
        port->InitSerialPort(ui->comboBox->currentText());

}
void Dialog::removeSerialPorts(QString comPort)
{
    int index = ui->comboBox->findText(comPort);
    if(index !=-1)
         ui->comboBox->removeItem(index);

    if(!comList.empty())
        port->InitSerialPort(ui->comboBox->currentText());

}
 void Dialog::setCurrentSerialPortName(QString port_name)
 {
     if(!comList.empty())
         port->InitSerialPort(port_name);
 }
