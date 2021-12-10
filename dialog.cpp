#include "dialog.h"
#include "ui_dialog.h"
#include <QByteArray>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->update_btn->setDisabled(false);
    ui->download_btn->setDisabled(false);
    ui->upload_btn->setDisabled(false);
    ui->exit_btn->setDisabled(false);

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
void Dialog::addSerialPorts(QString& comPort)
{
    if(ui->comboBox->findText(comPort) == -1)
        ui->comboBox->addItem(comPort);
}
void Dialog::removeSerialPorts(QString& comPort)
{
    if( 0 == port->portName().compare(comPort))
    {
        port->close();
        ui->comboBox->setDisabled(false);
    }
    int index = ui->comboBox->findText(comPort);
    if(index !=-1)
         ui->comboBox->removeItem(index);

}

 void Dialog::setCurrentSerialPortName(const QString& port_name)
 {
     port->InitSerialPort(port_name); //串口设置更新

     if(ui->comboBox->count())//ui 显示更新
     {
         updateComPortConfig();
     }
     else
     {
       clearComPortConfig();
     }

}

void Dialog::on_open_port_btn_clicked() //open port
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

void Dialog::on_close_port_btn_clicked() //closed port
{
    port->close();
    ui->comboBox->setDisabled(false);
}


void Dialog::on_update_btn_clicked()
{
   port->setBaudRate(QSerialPort::Baud19200);

   QByteArray updCommand;
   updCommand.resize(9);
   updCommand[0]=0x02;
   updCommand[1]=0x53;
   updCommand[2]=0x46;
   updCommand[3]=0x55;
   updCommand[4]=0x20;
   updCommand[5]=0x01;
   updCommand[6]=0x00;
   updCommand[7]=0x01;
   updCommand[8]=0xF8;

    char ack = 0x06;
    QByteArray rev_c;

    if(9 == port->write(updCommand))
    {
        if(port->waitForReadyRead())
        {
            rev_c = port->read(1);
            if(rev_c.compare(&ack) == 0)
            {
                ui->update_btn->setDisabled(true);
                ui->download_btn->setDisabled(false);
                ui->upload_btn->setDisabled(false);
                ui->exit_btn->setDisabled(false);
                port->setBaudRate(QSerialPort::Baud115200);
            }
        }
        else
        {
            QMessageBox(QMessageBox::Warning,QString("INFO"),QString("Recieve no data !")).exec();
        }
    }
    else
    {
         QMessageBox(QMessageBox::Warning,QString("INFO"),QString("send update command failed!")).exec();
    }
}

void Dialog::on_exit_btn_clicked()
{
    port->setBaudRate(QSerialPort::Baud115200);
    QByteArray extCommand;
    extCommand.resize(4);
    extCommand[0]=0x45;
    extCommand[1]=0x58;
    extCommand[2]=0x49;
    extCommand[3]=0x54;

    char ack = 0x06;
    QByteArray rev_c;

    if(4 == port->write(extCommand))
    {
        if(port->waitForReadyRead())
        {
            rev_c = port->read(1);
            if(rev_c.compare(&ack) == 0)
            {
                ui->update_btn->setDisabled(false);
                ui->download_btn->setDisabled(true);
                ui->upload_btn->setDisabled(true);
                ui->exit_btn->setDisabled(true);
            }
        }
        else
        {
            QMessageBox(QMessageBox::Warning,QString("INFO"),QString("Recieve no data !")).exec();
        }
    }
    else
    {
         QMessageBox(QMessageBox::Warning,QString("INFO"),QString("send exit command failed!")).exec();
    }

}

void Dialog::on_download_btn_clicked()
{
    FileDialog fileSel(this);
    if( QDialog::Accepted == fileSel.exec())
    {
        QByteArray dwnCommand;
        dwnCommand.resize(4);
        dwnCommand[0]=0x44;
        dwnCommand[1]=0x57;
        dwnCommand[2]=0x4C;
        dwnCommand[3]=0x44;

        char ack = 0x06;
        //char rdy = 0x43;

        QByteArray rev_c;

        if(4 == port->write(dwnCommand))
        {
            if(port->waitForReadyRead())
            {
                rev_c = port->read(1);
                if(rev_c.compare(&ack) == 0)
                {

                    ui->update_btn->setDisabled(true);
                    ui->download_btn->setDisabled(true);
                    ui->upload_btn->setDisabled(true);
                    ui->exit_btn->setDisabled(true);

                }
            }
            else
            {
                QMessageBox(QMessageBox::Warning,QString("INFO"),QString("Recieve no data !")).exec();
            }
        }
        else
        {
             QMessageBox(QMessageBox::Warning,QString("INFO"),QString("send exit command failed!")).exec();
        }
    }
}

void Dialog::on_upload_btn_clicked()
{
    QByteArray extCommand;
    extCommand.resize(4);
    extCommand[0]=0x55;
    extCommand[1]=0x50;
    extCommand[2]=0x44;
    extCommand[3]=0x54;

    char ack = 0x06;
    QByteArray rev_c;

    if(4 == port->write(extCommand))
    {
        if(port->waitForReadyRead())
        {
            rev_c = port->read(1);
            if(rev_c.compare(&ack) == 0)
            {
                ui->update_btn->setDisabled(false);
                ui->download_btn->setDisabled(true);
                ui->upload_btn->setDisabled(true);
                ui->exit_btn->setDisabled(true);
            }
        }
        else
        {
            QMessageBox(QMessageBox::Warning,QString("INFO"),QString("Recieve no data !")).exec();
        }
    }
    else
    {
         QMessageBox(QMessageBox::Warning,QString("INFO"),QString("send exit command failed!")).exec();
    }
}
