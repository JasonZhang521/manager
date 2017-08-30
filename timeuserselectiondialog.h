#ifndef TIMEUSERSELECTIONDIALOG_H
#define TIMEUSERSELECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class TimeUserSelectionDialog;
}

class TimeUserSelectionDialog : public QDialog
{
    Q_OBJECT

public:
     TimeUserSelectionDialog(QWidget *parent, QList<QStringList> userList);
    ~TimeUserSelectionDialog();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::TimeUserSelectionDialog *ui;
    QList<QStringList> m_userList;

    setupSession();
signals:
    void finishGetUsersAndTime(QStringList sl,QString str1,QString str2);
};

#endif // TIMEUSERSELECTIONDIALOG_H
