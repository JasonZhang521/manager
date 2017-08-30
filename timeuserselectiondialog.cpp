#include "timeuserselectiondialog.h"
#include "ui_timeuserselectiondialog.h"
#include <QDebug>

TimeUserSelectionDialog::TimeUserSelectionDialog(QWidget *parent,QList<QStringList> userList) :
    QDialog(parent),
    ui(new Ui::TimeUserSelectionDialog)
{
    ui->setupUi(this);
    m_userList=userList;
    setupSession();
}



TimeUserSelectionDialog::~TimeUserSelectionDialog()
{
    delete ui;
}

TimeUserSelectionDialog::setupSession()
{
    foreach(QStringList each, m_userList)
    {
       ui->listWidget_user->addItem(each[0]);
    }

}

void TimeUserSelectionDialog::on_pushButton_ok_clicked()
{
    QStringList users;
    QString startTime;
    QString endTime;

    QList<QListWidgetItem *> seletedUsereItems = ui->listWidget_user->selectedItems();
    foreach(QListWidgetItem *item, seletedUsereItems)
    {
        users.append(item->text());
    }
    startTime = ui->dateEdit_start->text();
    endTime = ui->dateEdit_end->text();
    emit finishGetUsersAndTime(users,startTime,endTime);
    this->close();

}
