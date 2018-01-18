#ifndef FTPDOWNLOADDIALOG_H
#define FTPDOWNLOADDIALOG_H

#include <QDialog>

namespace Ui {
class FtpDownloadDialog;
}

class FtpDownloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FtpDownloadDialog(QWidget *parent = 0);
    ~FtpDownloadDialog();

    void setFileName(const QStringList &value);

    void setStartFrom(const QString &value);

    void setDestination(const QString &value);

    void setRemainTime(const QString &value);

    void setPassedTime(const QString &value);

    void setDownloadSpeed(const QString &value);

    void setCurrentSize(const QString &value);

    void setPercent(int value);

public slots:
    update();
    setupContent(QStringList contentList);
private slots:
    void on_pushButton_cancel_clicked();

private:
    Ui::FtpDownloadDialog *ui;
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

};

#endif // FTPDOWNLOADDIALOG_H
