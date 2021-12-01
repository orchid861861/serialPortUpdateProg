#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "serialport.h"
#include "mynativeeventfilter.h"
#include <QMessageBox>
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
    void updateComPortConfig();
    void clearComPortConfig();
public slots:
    void addSerialPorts(QString comPort);
    void removeSerialPorts(QString comPort);
    void setCurrentSerialPortName(QString port_name);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Dialog *ui;
    SerialPort *port;
    QList<QSerialPortInfo> comList;
};
#endif // DIALOG_H
