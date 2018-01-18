#include "yunwei.h"
#include "ui_yunwei.h"

YunWei::YunWei(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YunWei)
{
    ui->setupUi(this);
}

YunWei::~YunWei()
{
    delete ui;
}

void YunWei::on_pushButton_clicked()
{
    this->close();
}
