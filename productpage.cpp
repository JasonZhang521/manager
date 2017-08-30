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
