#ifndef CONTACTINFOFORM_H
#define CONTACTINFOFORM_H

#include <QWidget>

namespace Ui {
class ContactInfoForm;
}

class ContactInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit ContactInfoForm(QWidget *parent = 0);
    ~ContactInfoForm();

private slots:
    void on_pushButton_submit_clicked();

private:
    Ui::ContactInfoForm *ui;
};

#endif // CONTACTINFOFORM_H
