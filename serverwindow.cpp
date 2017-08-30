#include "serverwindow.h"
#include "ui_serverwindow.h"
#include <QDebug>

ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    m_settings = new QSettings("servers.ini",QSettings::IniFormat);//initilizing qsettings
    updateList();
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::on_action_triggered()
{
    c = new ServerCreationWindow;
    connect(c,SIGNAL(finished()),this,SLOT(processFinished()));
    c->show();

}

void ServerWindow::updateList(){
    //get all server info
    ui->treeWidget->clear();
    QStringList groups = m_settings->childGroups();
    foreach (QString each, groups) {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0,each);
        item->setText(1,m_settings->value(each+"/hostname").toString());
        item->setText(2,m_settings->value(each+"/username").toString());
        item->setText(3,m_settings->value(each+"/password").toString());
        item->setText(4,m_settings->value(each+"/notes").toString());
    }

    //    qDebug()<<m_settings->childGroups();
    //show all info on list

}
void ServerWindow::processFinished(){
    updateList();
}


void ServerWindow::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{
    emit connectSignal(item->text(0));
    this->close();
}

void ServerWindow::on_pushButton_2_clicked()
{
    this->close();
}

void ServerWindow::on_pushButton_clicked()
{
    QString temp;
    QModelIndexList indexList = ui->treeWidget->selectionModel()->selectedRows(0);
    foreach (QModelIndex index, indexList) {
        temp = index.data().toString();
    }
    emit connectSignal(temp);
    this->close();
}

void ServerWindow::on_actiondelete_triggered()
{
    QString temp;
    QModelIndexList indexList = ui->treeWidget->selectionModel()->selectedRows(0);
    foreach (QModelIndex index, indexList) {
        temp = index.data().toString();

        if(!temp.isEmpty()){
            m_settings->remove(temp);
        }
    }
    updateList();
}
