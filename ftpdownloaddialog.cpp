#include "ftpdownloaddialog.h"
#include "ui_ftpdownloaddialog.h"

FtpDownloadDialog::FtpDownloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FtpDownloadDialog)
{
    ui->setupUi(this);
}

FtpDownloadDialog::~FtpDownloadDialog()
{
    delete ui;
}

FtpDownloadDialog::setupContent(QStringList contentList)
{

}

void FtpDownloadDialog::setPercent(int value)
{
    percent = value;
}

void FtpDownloadDialog::setCurrentSize(const QString &value)
{
    currentSize = value;
}

void FtpDownloadDialog::setDownloadSpeed(const QString &value)
{
    downloadSpeed = value;
}

void FtpDownloadDialog::setPassedTime(const QString &value)
{
    passedTime = value;
}

void FtpDownloadDialog::setRemainTime(const QString &value)
{
    remainTime = value;
}

void FtpDownloadDialog::setDestination(const QString &value)
{
    destination = value;
}

void FtpDownloadDialog::setStartFrom(const QString &value)
{
    startFrom = value;
}

void FtpDownloadDialog::setFileName(const QStringList &value)
{
    fileName = value;
}

FtpDownloadDialog::update()
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


void FtpDownloadDialog::on_pushButton_cancel_clicked()
{
    emit canceledSignal();
}
