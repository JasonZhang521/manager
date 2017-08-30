#include "contactpage.h"
#include "ui_contactpage.h"
#include "contactinfoform.h"
#include "productpage.h"
#include <QMouseEvent>

ContactPage::ContactPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactPage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);
}

ContactPage::~ContactPage()
{
    delete ui;
}

void ContactPage::on_pushButton_2_clicked()
{
    ContactInfoForm *c = new ContactInfoForm;
    c->show();

}

void ContactPage::on_pushButton_3_clicked()
{
    ContactInfoForm *c = new ContactInfoForm;
    c->show();
}

void ContactPage::on_pushButton_4_clicked()
{
    ContactInfoForm *c = new ContactInfoForm;
    c->show();
}

void ContactPage::on_pushButton_clicked()
{
    ProductPage *p = new ProductPage;
    p->show();
}


void ContactPage::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->pos();
    }
}

void ContactPage::mouseMoveEvent(QMouseEvent* event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}

void ContactPage::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}
