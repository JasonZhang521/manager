#include "productpage.h"
#include "ui_productpage.h"

ProductPage::ProductPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductPage)
{
    ui->setupUi(this);
}

ProductPage::~ProductPage()
{
    delete ui;
}

void ProductPage::on_pushButton_next_clicked()
{
    ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex()+1)%5);
}
