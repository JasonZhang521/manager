#include "ftpuploaddialog.h"
#include "ui_ftpuploaddialog.h"

FtpUploadDialog::FtpUploadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpUploadDialog)
{
    ui->setupUi(this);
}

FtpUploadDialog::~FtpUploadDialog()
{
    delete ui;
}

void FtpUploadDialog::setFileName(const QStringList &value)
{
    fileName = value;
}

void FtpUploadDialog::setStartFrom(const QString &value)
{
    startFrom = value;
}

void FtpUploadDialog::setDestination(const QString &value)
{
    destination = value;
}

void FtpUploadDialog::setRemainTime(const QString &value)
{
    remainTime = value;
}

void FtpUploadDialog::setPassedTime(const QString &value)
{
    passedTime = value;
}

void FtpUploadDialog::setDownloadSpeed(const QString &value)
{
    downloadSpeed = value;
}

void FtpUploadDialog::setCurrentSize(const QString &value)
{
    currentSize = value;
}

void FtpUploadDialog::setPercent(int value)
{
    percent = value;
}

void FtpUploadDialog::update()
{
    QString temp_filename="";
    foreach(QString each ,  fileName)
    {
         temp_filename = temp_filename + each + ", ";
    }
    ui->label_filename->setText(temp_filename);
    ui->label_destination->setText(destination);
    ui->label_downloaded->setText(currentSize);
    ui->label_passedTime->setText(passedTime);
    ui->label_remainTime->setText(remainTime);
    ui->label_speed->setText(downloadSpeed);
    ui->progressBar_percent->setValue(percent);

}




void FtpUploadDialog::on_pushButton_cancel_clicked()
{
    emit canceledSignal();

}
