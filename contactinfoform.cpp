/*
 * embedded email account and password: embedded email account(hungclustermanager@163.com)
 * and password(123581321)
 *
*/


#include "contactinfoform.h"
#include "ui_contactinfoform.h"
#include <thirdPartyLib/src/SmtpMime>
#include <QMessageBox>

ContactInfoForm::ContactInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactInfoForm)
{
    ui->setupUi(this);
}

ContactInfoForm::~ContactInfoForm()
{
    delete ui;
}

void ContactInfoForm::on_pushButton_submit_clicked()
{
    ui->pushButton_submit->setEnabled(false);
    QString m_name;
    QString m_contact;
    QString m_type;
    QString m_message;

    m_name = ui->lineEdit_name->text();
    m_contact = ui->lineEdit_contact->text();
    m_type = ui->comboBox_category->currentText();
    m_message = ui->textEdit_message->toPlainText();

    SmtpClient smtp("smtp.qq.com", 465, SmtpClient::SslConnection);
//    smtp.setUser("hungclustermanager@163.com");
    smtp.setUser("728670667@qq.com");

    smtp.setPassword("123581321zj");

    MimeMessage message;

    EmailAddress sender("728670667@qq.com", m_name);
    message.setSender(&sender);

    EmailAddress to("zhangjincao@hzwtech.com", "["+m_type+"]");
    message.addRecipient(&to);
    message.setSubject("["+m_type+"]");

    MimeText text;
    text.setText("发件人: \n"+m_name+"\n\n"+"联系方式: \n"+m_contact+"\n\n"+m_message);

    message.addPart(&text);

    if (!smtp.connectToHost()) {
        qDebug() << "Failed to connect to host!" << endl;

    }
    if (!smtp.login()) {
        qDebug() << "Failed to login!" << endl;

    }
    if (!smtp.sendMail(message)) {
        QMessageBox msg;
        msg.setText("发送失败");
        msg.exec();
        ui->pushButton_submit->setEnabled(true);
    }
    else
    {
        QMessageBox msg;
        msg.setText("发送成功");
        msg.exec();
        this->close();
    }

    smtp.quit();

}
