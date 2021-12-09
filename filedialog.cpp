#include "filedialog.h"
#include "ui_filedialog.h"

FileDialog::FileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog)
{
    ui->setupUi(this);
}

FileDialog::~FileDialog()
{
    delete ui;
}

void FileDialog::on_send_btn_clicked()
{
    emit accept();
}

void FileDialog::on_pushButton_2_clicked()
{
    emit reject();
}


void FileDialog::on_select_btn_clicked()
{
    QDir dir("C:");
}
