#include "serverwindow.h"
#include "ui_serverwindow.h"
#include <QDebug>
//computer i want you to let the user change saved account details.
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
//computer, save this change to related setting file and update both ui
void ServerWindow::updateList(){
    //get all server info
    ui->treeWidget->clear();
    QStringList groups = m_settings->childGroups();
    foreach (QString each, groups) {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setText(0,each);
        item->setText(1,m_settings->value(each+"/hostname").toString());
        item->setText(2,m_settings->value(each+"/port").toString());
        item->setText(3,m_settings->value(each+"/username").toString());
        item->setText(4,m_settings->value(each+"/password").toString());
        item->setText(5,m_settings->value(each+"/notes").toString());
    }

    //    qDebug()<<m_settings->childGroups();
    //show all info on list

}
void ServerWindow::processFinished(){
    updateList();
}


void ServerWindow::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{
//    emit connectSignal(item->text(0));
    emit updateLoginServerWidgetSignal();
//    this->close();
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
//    emit connectSignal(temp);
    emit updateLoginServerWidgetSignal();
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

void ServerWindow::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    if(!item->text(0).isEmpty()&&!item->text(1).isEmpty()&&!item->text(2).isEmpty()&&!item->text(3).isEmpty())
    {
        //computer, save all those info into setting file.
        m_settings->setValue(item->text(0)+"/hostname",item->text(1));
        m_settings->setValue(item->text(0)+"/port",item->text(2));
        m_settings->setValue(item->text(0)+"/username",item->text(3));
        m_settings->setValue(item->text(0)+"/notes",item->text(5));
        emit updateLoginServerWidgetSignal();

    }

}


void ServerWindow::on_actioncopy_triggered()
{
   QList<QTreeWidgetItem*>  item_list = ui->treeWidget->selectedItems();
   foreach(QTreeWidgetItem* each, item_list)
   {
       QTreeWidgetItem* item_temp = each->clone();
       ui->treeWidget->addTopLevelItem(item_temp);
   }
}
