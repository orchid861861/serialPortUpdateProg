#include "dialog.h"
#include "ui_dialog.h"


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

    setFocusPolicy(Qt::StrongFocus);

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
     if(ui->comboBox->count())//ui 显示更新
     {
         port->InitSerialPort(port_name); //串口设置更新
         updateComPortConfig();
     }
     else
     {
         clearComPortConfig();

     }

 }

void Dialog::on_pushButton_clicked() //open port
{
    if(port->portName().isEmpty())
        QMessageBox(QMessageBox::Warning,QString("COMINFO"),QString("open comport not exist!")).exec();
    else if(!port->open(QIODevice::ReadWrite))
        QMessageBox(QMessageBox::Warning,QString("COMINFO"),QString("already opened,open comport failed!")).exec();
    else
    {
        port->clear();
        ui->comboBox->setDisabled(true);
    }
}

void Dialog::on_pushButton_2_clicked() //closed port
{
    port->close();
    ui->comboBox->setDisabled(false);

}

void Dialog::on_pushButton_3_clicked()//download
{
    port->write("hello world!");
}

void Dialog::on_pushButton_4_clicked()//upoload
{

}
