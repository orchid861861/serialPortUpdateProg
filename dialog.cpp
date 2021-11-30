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

    QList<QSerialPortInfo> comList(QSerialPortInfo().availablePorts());
    foreach(const QSerialPortInfo info,comList)
        ui->comboBox->addItem(info.portName());

}

Dialog::~Dialog()
{
    delete ui;
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
