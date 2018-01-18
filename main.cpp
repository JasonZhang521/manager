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

//
#include "m.h"
int main(int argc, char *argv[])
{
    MyApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    MyApplication a(argc, argv);
    LoginPageII *l=new LoginPageII();
    l->show();

//    FormForTest f;
//    f.show();

    return a.exec();


}
