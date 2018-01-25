#include "mainwindow.h"
#include <QApplication>
#include "loginpage.h"
#include <QMessageBox>
#include "main.h"
#include "loginpageii.h"

#include "Sleep.h"
#include "Trace.h"
#include <memory>
#include "formfortest.h"

#include <QFile>
#include <QNetworkInterface>
#include <QDebug>
#include "simplecrypt.h"

//
#include "m.h"

QString getMacAddress();

int main(int argc, char *argv[])
{
    MyApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    MyApplication a(argc, argv);

    SimpleCrypt crypto(Q_UINT64_C(0x0c2ad4a4acb9f083)); //some random number
    crypto.setCompressionMode(SimpleCrypt::CompressionAlways); //always compress the data, see section below
    crypto.setIntegrityProtectionMode(SimpleCrypt::ProtectionHash); //properly protect the integrity of the data

    QString read_mac;
    QString current_mac;
    current_mac = getMacAddress().toUpper();
    QFile file("lic");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in >> read_mac;
        if(crypto.decryptToString(read_mac).toUpper().compare(current_mac)==0)
        {
            LoginPageII *l=new LoginPageII();
            l->show();
        }

        else
        {
            QMessageBox::information(0,"error","invalid lisence");
            return a.exec();
        }
    }

    else
    {
        QMessageBox::information(0,"error","there is no lisence file!");
        return a.exec();
    }





//    FormForTest f;
//    f.show();

    file.close();
    return a.exec();


}

QString getMacAddress()
{
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
            return netInterface.hardwareAddress();
    }
    return QString();
}
