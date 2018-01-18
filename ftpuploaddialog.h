#ifndef FTPUPLOADDIALOG_H
#define FTPUPLOADDIALOG_H

#include <QDialog>

namespace Ui {
class FtpUploadDialog;
}

class FtpUploadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FtpUploadDialog(QWidget *parent = 0);
    ~FtpUploadDialog();

    void setFileName(const QStringList &value);

    void setStartFrom(const QString &value);

    void setDestination(const QString &value);

    void setRemainTime(const QString &value);

    void setPassedTime(const QString &value);

    void setDownloadSpeed(const QString &value);

    void setCurrentSize(const QString &value);

    void setPercent(int value);
public slots:
   void update();

private:
    Ui::FtpUploadDialog *ui;

    QStringList fileName={}; //filename = 1 / filename list
    QString startFrom=""; //
    QString destination="";
    QString remainTime=""; // remainTime = (fileFullsize - currentfilesize) / downloadSpeed
    QString passedTime=""; //passedtime = timer record
    QString downloadSpeed=""; // downloadspeed = ( prosize - ppresize ) / passed time
    QString currentSize=""; //
    int percent = 0; // percent = current / full;

signals:
    void canceledSignal();
private slots:
    void on_pushButton_cancel_clicked();
};

#endif // FTPUPLOADDIALOG_H
