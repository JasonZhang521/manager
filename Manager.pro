QT += core gui
QT += widgets
QT += charts
QT += network

CONFIG += c++11

TARGET = HungClusterManager
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += sourceCode/Common/ \
               sourceCode/Configure/ \
               sourceCode/SshWrapper/ \
               sourceCode/TraceLog/ \
               sourceCode/include \
               sourceCode/QRoundProgressBar

SOURCES += \
    sourceCode/Common/FilePathHandler.cpp \
    sourceCode/Common/LocalTime.cpp \
    sourceCode/Common/remove_character.cpp \
    sourceCode/Common/replace_character.cpp \
    sourceCode/Configure/Configure.cpp \
    sourceCode/Configure/ExceptionConfigure.cpp \
    sourceCode/Configure/TraceLogConfigure.cpp \
    sourceCode/SshWrapper/SshClient.cpp \
    sourceCode/SshWrapper/SshClientSession.cpp \
    sourceCode/SshWrapper/SshFtpSession.cpp \
    sourceCode/SshWrapper/SshInteractiveShellChannel.cpp \
    sourceCode/SshWrapper/SshShellChannel.cpp \
    sourceCode/SshWrapper/SftpDirAttribute.cpp \
    mainwindow.cpp \
    main.cpp \
    sourceCode/QRoundProgressBar/QRoundProgressBar.cpp \
    loginpage.cpp \
    clientworker.cpp \
    ftpworker.cpp \
    shellworker.cpp \
    serverwindow.cpp \
    speedcalculator.cpp \
    servercreationwindow.cpp \
    simplecrypt.cpp \
    manageworker.cpp \
    timeuserselectionwidget.cpp \
    timeuserselectiondialog.cpp \
    contactpage.cpp \
    contactinfoform.cpp \
    productpage.cpp \
    loginpageii.cpp \
    flowlayout.cpp \
    monitorworker.cpp \
    monitorwindow.cpp \
    dataVisualPack/dynamicsplinechart.cpp \
    dataVisualPack/cpuusageinfo.cpp \
    dataVisualPack/datacontainer.cpp \
    dataVisualPack/mybarchart.cpp \
    highlighter.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    sourceCode/Common/App.h \
    sourceCode/Common/FilePathHandler.h \
    sourceCode/Common/LocalTime.h \
    sourceCode/Common/remove_character.h \
    sourceCode/Common/replace_character.h \
    sourceCode/Configure/Configure.h \
    sourceCode/Configure/Configure_Define.h \
    sourceCode/Configure/ExceptionConfigure.h \
    sourceCode/Configure/TraceLogConfigure.h \
    sourceCode/include/libssh/callbacks.h \
    sourceCode/include/libssh/legacy.h \
    sourceCode/include/libssh/libssh.h \
    sourceCode/include/libssh/libsshpp.hpp \
    sourceCode/include/libssh/server.h \
    sourceCode/include/libssh/sftp.h \
    sourceCode/include/libssh/ssh2.h \
    sourceCode/SshWrapper/ISshClient.h \
    sourceCode/SshWrapper/ISshClientSession.h \
    sourceCode/SshWrapper/ISshFtpSession.h \
    sourceCode/SshWrapper/ISshShellChannel.h \
    sourceCode/SshWrapper/SshClient.h \
    sourceCode/SshWrapper/SshClientSession.h \
    sourceCode/SshWrapper/SshConfigure.h \
    sourceCode/SshWrapper/SshFtpSession.h \
    sourceCode/SshWrapper/SshInteractiveShellChannel.h \
    sourceCode/SshWrapper/SshShellChannel.h \
    sourceCode/TraceLog/Trace.h \
    sourceCode/TraceLog/TraceBuf.h \
    sourceCode/TraceLog/TraceConsole.h \
    sourceCode/TraceLog/TraceFile.h \
    sourceCode/SshWrapper/Component.h \
    sourceCode/Common/Macro.h \
    sourceCode/SshWrapper/SftpDirAttribute.h \
    mainwindow.h \
    sourceCode/QRoundProgressBar/QRoundProgressBar.h \
    loginpage.h \
    clientworker.h \
    ftpworker.h \
    shellworker.h \
    serverwindow.h \
    speedcalculator.h \
    servercreationwindow.h \
    simplecrypt.h \
    main.h \
    manageworker.h \
    timeuserselectionwidget.h \
    timeuserselectiondialog.h \
    contactpage.h \
    contactinfoform.h \
    productpage.h \
    loginpageii.h \
    flowlayout.h \
    monitorworker.h \
    monitorwindow.h \
    dataVisualPack/dynamicsplinechart.h \
    dataVisualPack/cpuusageinfo.h \
    dataVisualPack/datacontainer.h \
    dataVisualPack/mybarchart.h \
    Highlighter.h



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/sourceCode/static_lib/ -lssh.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/sourceCode/static_lib/ -lssh.dll

INCLUDEPATH += $$PWD/sourceCode/static_lib
DEPENDPATH += $$PWD/sourceCode/static_lib
DLLDESTDIR += $$PWD/sourceCode/dynamic_lib/ssh

FORMS += \
    mainwindow.ui \
    loginpage.ui \
    serverwindow.ui \
    servercreationwindow.ui \
    timeuserselectiondialog.ui \
    contactpage.ui \
    contactinfoform.ui \
    productpage.ui \
    loginpageii.ui \
    monitorwindow.ui

RESOURCES += \
    hungclustermanager1.qrc

#win32:RC_ICONS += ./Resources/applicationIcon.ico
win32:RC_ICONS += ./Resources/ico.ico

DISTFILES += \
    thirdPartyLib/libSMTPEmail.a




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/thirdPartyLib/ -lSMTPEmail
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/thirdPartyLib/ -lSMTPEmail

INCLUDEPATH += $$PWD/thirdPartyLib
DEPENDPATH += $$PWD/thirdPartyLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/thirdPartyLib/libSMTPEmail.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/thirdPartyLib/libSMTPEmail.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/thirdPartyLib/SMTPEmail.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/thirdPartyLib/SMTPEmail.lib

win32: LIBS += -L$$PWD/thirdPartyLib/ -lSMTPEmail

INCLUDEPATH += $$PWD/thirdPartyLib
DEPENDPATH += $$PWD/thirdPartyLib

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/thirdPartyLib/SMTPEmail.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/thirdPartyLib/libSMTPEmail.a
