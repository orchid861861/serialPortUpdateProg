#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
#include <QDir>

namespace Ui {
class FileDialog;
}

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileDialog(QWidget *parent = nullptr);
    ~FileDialog();

private slots:
    void on_send_btn_clicked();

    void on_pushButton_2_clicked();

    void on_select_btn_clicked();

private:
    Ui::FileDialog *ui;
};

#endif // FILEDIALOG_H
