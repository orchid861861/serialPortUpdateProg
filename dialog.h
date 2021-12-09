#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "serialport.h"
#include "mynativeeventfilter.h"
#include <QMessageBox>
#include <QList>
#include "filedialog.h"

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
    void addSerialPorts(QString& comPort);
    void removeSerialPorts(QString& comPort);
    void setCurrentSerialPortName(const QString& port_name);

private slots:
    void on_open_port_btn_clicked();

    void on_close_port_btn_clicked();

    void on_update_btn_clicked();

    void on_exit_btn_clicked();

    void on_download_btn_clicked();

    void on_upload_btn_clicked();

private:
    Ui::Dialog *ui;
    SerialPort *port;
    QList<QSerialPortInfo> comList;
};
#endif // DIALOG_H
