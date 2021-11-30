#include "dialog.h"
#include "ui_dialog.h"
#include "serialport.h"
#include <QList>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QList<QSerialPortInfo> comList(QSerialPortInfo().availablePorts());
    for(int i = 0;i<comList.count();i++)
        ui->comboBox->addItem(comList.at(i).portName());


}

Dialog::~Dialog()
{
    delete ui;
}

