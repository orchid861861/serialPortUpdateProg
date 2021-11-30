#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "serialport.h"
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void addSerialPorts(QString comPort);
    void removeSerialPorts(QString comPort);
    void setCurrentSerialPortName(QString port_name);
private:
    Ui::Dialog *ui;
    SerialPort *port;
    QList<QSerialPortInfo> comList;
};
#endif // DIALOG_H
