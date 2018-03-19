QT += core gui
QT += widgets printsupport
QT += charts
QT += network

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O3
QMAKE_CXXFLAGS_RELEASE -= -Os
QMAKE_CXXFLAGS_RELEASE += -O0

#QMAKE_CXXFLAGS += -Wno-unused-parameter
#QMAKE_CXXFLAGS += -Wno-unused-variable

#QMAKE_LFLAGS_RELEASE -= -O1

CONFIG += c++11

TARGET = UiClient
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += sourceCode/Common/ \
               sourceCode/SshWrapper/ \
               sourceCode/TraceLog/ \
               sourceCode/include \
               sourceCode/QRoundProgressBar \
               sourceCode/Serialize \
               sourceCode/Configure \
               sourceCode/EventHandler \
               sourceCode/TimerHandler \
               sourceCode/Network \
               sourceCode/Ipc \
               sourceCode/Io \
               sourceCode/Core \
               sourceCode/Connection \
               sourceCode/PlatformWrapper \
               sourceCode/Environment \
               sourceCode/IpcMessage \
               sourceCode/SystemMonitorMessage \
               sourceCode/UiClient \
               thirdPartyLib/qcustomplot \
               sourceCode/ShellCommandMessage

SOURCES += \
    sourceCode/Common/FilePathHandler.cpp \
    sourceCode/Common/LocalTime.cpp \
    sourceCode/Common/RemoveCharacter.cpp \
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
    dataVisualPack/datacontainer.cpp \
    dataVisualPack/mybarchart.cpp \
    highlighter.cpp \
    sourceCode/Ipc/IIpcConnectionClientStrategy.cpp \
    sourceCode/Ipc/IpcClient.cpp \
    sourceCode/Ipc/IpcConnectionTcpClientStrategy.cpp \
    sourceCode/IpcMessage/IpcMessageIdGenerator.cpp \
    sourceCode/IpcMessage/IIpcMessage.cpp \
    sourceCode/Common/Random.cpp \
    sourceCode/Common/SystemTime.cpp \
    sourceCode/Common/TimeStat.cpp \
    sourceCode/SystemMonitorMessage/ISystemMonitorMessage.cpp \
    sourceCode/Serialize/ISerializable.cpp \
    sourceCode/Serialize/ReadBuffer.cpp \
    sourceCode/Serialize/WriteBuffer.cpp \
    sourceCode/Environment/CpuUsage.cpp \
    sourceCode/Environment/CpuUsageCalculator.cpp \
    sourceCode/Environment/CpuUsageInfo.cpp \
    sourceCode/Network/IpAddress.cpp \
    sourceCode/Network/IpPort.cpp \
    sourceCode/Network/IpSocketEndpoint.cpp \
    sourceCode/Network/ITcpClient.cpp \
    sourceCode/Network/ITcpServer.cpp \
    sourceCode/Network/SocketImp.cpp \
    sourceCode/Network/TcpClient.cpp \
    sourceCode/Network/TcpServer.cpp \
    sourceCode/Network/TcpSocket.cpp \
    sourceCode/PlatformWrapper/SocketWrapper.cpp \
    sourceCode/EventHandler/EventIdGenerator.cpp \
    sourceCode/EventHandler/IEvent.cpp \
    sourceCode/EventHandler/IEventQueue.cpp \
    sourceCode/EventHandler/ListEventQueue.cpp \
    sourceCode/TimerHandler/EventTimer.cpp \
    sourceCode/TimerHandler/ITimer.cpp \
    sourceCode/TimerHandler/ITimerQueue.cpp \
    sourceCode/TimerHandler/ListTimerQueue.cpp \
    sourceCode/TimerHandler/TimerIdGenerator.cpp \
    sourceCode/Core/EventLoop.cpp \
    sourceCode/Core/LoopMain.cpp \
    sourceCode/Io/IIoControl.cpp \
    sourceCode/Io/IoControlEventsHandler.cpp \
    sourceCode/Core/IoLoop.cpp \
    sourceCode/Core/TimerLoop.cpp \
    sourceCode/Io/IIoEvent.cpp \
    sourceCode/Ipc/IIpcClient.cpp \
    sourceCode/Network/ITcpConnectionReceiver.cpp \
    sourceCode/Ipc/IIpcConnectionReceiver.cpp \
    sourceCode/IpcMessage/IIpcMessageFactory.cpp \
    sourceCode/SystemMonitorMessage/SystemMonitorMessageFactory.cpp \
    sourceCode/Environment/CpuUsageDataType.cpp \
    sourceCode/Network/TcpState.cpp \
    sourceCode/Network/NetworkEnv.cpp \
    sourceCode/Ipc/IpcClientCreator.cpp \
    sourceCode/IpcMessage/IpcMessageType.cpp \
    sourceCode/Ipc/IpcHeartbeatTimer.cpp \
    sourceCode/IpcMessage/IpcLayerMessageFactory.cpp \
    sourceCode/IpcMessage/IpcHeartbeatReport.cpp \
    sourceCode/Ipc/IpcConnectionTimer.cpp \
    sourceCode/IpcMessage/IIpcComunicationMessage.cpp \
    sourceCode/IpcMessage/IpcAuthorizationRequest.cpp \
    sourceCode/IpcMessage/IpcAuthorizationResponse.cpp \
    sourceCode/UiClient/UiIpcConnectionReceiver.cpp \
    sourceCode/UiClient/IUiClientHandler.cpp \
    sourceCode/UiClient/UiClientHandler.cpp \
    sourceCode/UiClient/UiClientProcess.cpp \
#    sourceCode/UiClient/UiClientMain.cpp \
    sourceCode/IpcMessage/IIpcMessageQueue.cpp \
    sourceCode/Common/Lock.cpp \
    sourceCode/IpcMessage/IpcThreadSafeMessageQueue.cpp \
    sourceCode/UiClient/UiClientMessageSendTimer.cpp \
    sourceCode/Environment/ComputerNodeInfo.cpp \
    sourceCode/Environment/CpuInfo.cpp \
    sourceCode/Environment/CpuInfoBriefly.cpp \
    sourceCode/Environment/DiskUsageInfo.cpp \
    sourceCode/Environment/EnvironmentSystemInfomation.cpp \
    sourceCode/Environment/MemoryInfo.cpp \
    sourceCode/Environment/MemoryInfoBriefly.cpp \
    sourceCode/Environment/MemoryUsageInfo.cpp \
    sourceCode/Environment/MemoryUsageInfoDataType.cpp \
    sourceCode/Environment/MiscInfo.cpp \
    sourceCode/Environment/NetworkInfo.cpp \
    sourceCode/Environment/SystemInfoBriefly.cpp \
    sourceCode/PlatformWrapper/SystemErrorInfo.cpp \
    sourceCode/Environment/CpuInfoDataType.cpp \
    sourceCode/Environment/ShellCommandDataType.cpp \
    sourceCode/Environment/ShellCommandDfOutput.cpp \
    sourceCode/Environment/ShellCommandOutputParse.cpp \
    sourceCode/Environment/ShellCommandProcess.cpp \
    sourceCode/Environment/ShellCommandThread.cpp \
    sourceCode/Environment/Environment.cpp \
    sourceCode/Environment/IShellCommand.cpp \
    sourceCode/SystemMonitorMessage/ComputerNodeInfoReport.cpp \
    sourceCode/SystemMonitorMessage/ComputerNodeInfoRequest.cpp \
    sourceCode/SystemMonitorMessage/ControlNodeBrieflyInfoRequest.cpp \
    sourceCode/SystemMonitorMessage/ControlNodeBrieflyInfoResponse.cpp \
    sourceCode/PlatformWrapper/NetworkHost.cpp \
    thirdPartyLib/qcustomplot/qcustomplot.cpp \
    m.cpp \
    sourceCode/Environment/ShellCommandPsTopnCpuUsageOutput.cpp \
    sourceCode/Environment/ShellCommandPsTopnMemoryUsageOutput.cpp \
    sourceCode/ShellCommandMessage/IShellCommandMessage.cpp \
    sourceCode/ShellCommandMessage/ShellCommandMessageFactory.cpp \
    sourceCode/ShellCommandMessage/ShellCommandRequest.cpp \
    sourceCode/ShellCommandMessage/ShellCommandResponse.cpp \
    sourceCode/Environment/ShellCommandGenericOutput.cpp \
    sourceCode/Configure/SystemEnvironmentConfigure.cpp \
    sourceCode/PlatformWrapper/SystemApi.cpp \
    doubleclickedbutton.cpp \
    ftpdownloaddialog.cpp \
    formfortest.cpp \
    yunwei.cpp \
    ftpuploaddialog.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_NO_WARNING_OUTPUT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    sourceCode/Common/App.h \
    sourceCode/Common/FilePathHandler.h \
    sourceCode/Common/LocalTime.h \
    sourceCode/Common/RemoveCharacter.h \
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
    dataVisualPack/datacontainer.h \
    dataVisualPack/mybarchart.h \
    Highlighter.h \
    sourceCode/Ipc/Component.h \
    sourceCode/Ipc/IIpcConnectionClientStrategy.h \
    sourceCode/Ipc/IpcClient.h \
    sourceCode/Ipc/IpcConnectionTcpClientStrategy.h \
    sourceCode/IpcMessage/IpcMessageIdGenerator.h \
    sourceCode/IpcMessage/IIpcMessage.h \
    sourceCode/IpcMessage/IpcMessageType.h \
    sourceCode/Common/AppConst.h \
    sourceCode/Common/generic.h \
    sourceCode/Common/Macro.h \
    sourceCode/Common/operator.h \
    sourceCode/Common/Random.h \
    sourceCode/Common/SystemTime.h \
    sourceCode/Common/TimeStat.h \
    sourceCode/SystemMonitorMessage/ISystemMonitorMessage.h \
    sourceCode/SystemMonitorMessage/Component.h \
    sourceCode/Serialize/BufferToData.h \
    sourceCode/Serialize/DataToBuffer.h \
    sourceCode/Serialize/ISerializable.h \
    sourceCode/Serialize/ReadBuffer.h \
    sourceCode/Serialize/WriteBuffer.h \
    sourceCode/Environment/Component.h \
    sourceCode/Environment/CpuUsage.h \
    sourceCode/Environment/CpuUsageCalculator.h \
    sourceCode/Environment/CpuUsageDataType.h \
    sourceCode/Environment/CpuUsageInfo.h \
    sourceCode/Network/IpAddress.h \
    sourceCode/Network/IpPort.h \
    sourceCode/Network/IpSocketEndpoint.h \
    sourceCode/Network/ITcpClient.h \
    sourceCode/Network/ITcpServer.h \
    sourceCode/Network/SocketImp.h \
    sourceCode/Network/TcpClient.h \
    sourceCode/Network/tcpresult.h \
    sourceCode/Network/TcpServer.h \
    sourceCode/Network/TcpSocket.h \
    sourceCode/Network/TcpState.h \
    sourceCode/Network/Component.h \
    sourceCode/PlatformWrapper/SocketWrapper.h \
    sourceCode/PlatformWrapper/SocketWrapperDef.h \
    sourceCode/EventHandler/Component.h \
    sourceCode/EventHandler/EventIdGenerator.h \
    sourceCode/EventHandler/IEvent.h \
    sourceCode/EventHandler/IEventQueue.h \
    sourceCode/EventHandler/ListEventQueue.h \
    sourceCode/TimerHandler/Component.h \
    sourceCode/TimerHandler/EventTimer.h \
    sourceCode/TimerHandler/ITimer.h \
    sourceCode/TimerHandler/ITimerQueue.h \
    sourceCode/TimerHandler/ListTimerQueue.h \
    sourceCode/TimerHandler/TimerIdGenerator.h \
    sourceCode/Core/EventLoop.h \
    sourceCode/Core/LoopMain.h \
    sourceCode/Io/Component.h \
    sourceCode/Io/IIoControl.h \
    sourceCode/Io/IoControlEventsHandler.h \
    sourceCode/Core/IoLoop.h \
    sourceCode/Core/TimerLoop.h \
    sourceCode/Common/Singleton.h \
    sourceCode/Serialize/Component.h \
    sourceCode/Io/IIoEvent.h \
    sourceCode/Ipc/IIpcClient.h \
    sourceCode/Network/ITcpConnectionReceiver.h \
    sourceCode/Ipc/IIpcConnectionReceiver.h \
    sourceCode/IpcMessage/IIpcMessageFactory.h \
    sourceCode/SystemMonitorMessage/SystemMonitorMessageFactory.h \
    sourceCode/Network/NetworkEnv.h \
    sourceCode/Ipc/IpcClientCreator.h \
    sourceCode/Ipc/IpcHeartbeatTimer.h \
    sourceCode/IpcMessage/IpcLayerMessageFactory.h \
    sourceCode/IpcMessage/IpcHeartbeatReport.h \
    sourceCode/Ipc/IpcConnectionTimer.h \
    sourceCode/IpcMessage/IIpcComunicationMessage.h \
    sourceCode/IpcMessage/IpcAuthorizationRequest.h \
    sourceCode/IpcMessage/IpcAuthorizationResponse.h \
    sourceCode/UiClient/UiIpcConnectionReceiver.h \
    sourceCode/UiClient/IUiClientHandler.h \
    sourceCode/UiClient/UiClientHandler.h \
    sourceCode/UiClient/UiClientProcess.h \
    sourceCode/UiClient/Component.h \
    sourceCode/IpcMessage/IIpcMessageQueue.h \
    sourceCode/Common/Lock.h \
    sourceCode/IpcMessage/IpcThreadSafeMessageQueue.h \
    sourceCode/UiClient/UiClientMessageSendTimer.h \
    sourceCode/Environment/ComputerNodeInfo.h \
    sourceCode/Environment/CpuInfo.h \
    sourceCode/Environment/CpuInfoBriefly.h \
    sourceCode/Environment/cpuinfodatatype.h \
    sourceCode/Environment/DiskUsageInfo.h \
    sourceCode/Environment/EnvironmentSystemInfomation.h \
    sourceCode/Environment/MemoryInfo.h \
    sourceCode/Environment/MemoryInfoBriefly.h \
    sourceCode/Environment/MemoryUsageInfo.h \
    sourceCode/Environment/MemoryUsageInfoDataType.h \
    sourceCode/Environment/MiscInfo.h \
    sourceCode/Environment/NetworkInfo.h \
    sourceCode/Environment/SystemInfoBriefly.h \
    sourceCode/PlatformWrapper/SystemErrorInfo.h \
    sourceCode/Environment/ShellCommandDataType.h \
    sourceCode/Environment/ShellCommandDfOutput.h \
    sourceCode/Environment/ShellCommandOutputParse.h \
    sourceCode/Environment/ShellCommandProcess.h \
    sourceCode/Environment/ShellCommandThread.h \
    sourceCode/Environment/Environment.h \
    sourceCode/Environment/IShellCommand.h \
    sourceCode/SystemMonitorMessage/ComputerNodeInfoReport.h \
    sourceCode/SystemMonitorMessage/ComputerNodeInfoRequest.h \
    sourceCode/SystemMonitorMessage/ControlNodeBrieflyInfoRequest.h \
    sourceCode/SystemMonitorMessage/ControlNodeBrieflyInfoResponse.h \
    sourceCode/PlatformWrapper/NetworkHost.h \
    thirdPartyLib/qcustomplot/qcustomplot.h \
    m.h \
    sourceCode/Environment/ShellCommandPsTopnCpuUsageOutput.h \
    sourceCode/Environment/ShellCommandPsTopnMemoryUsageOutput.h \
    sourceCode/ShellCommandMessage/Component.h \
    sourceCode/ShellCommandMessage/IShellCommandMessage.h \
    sourceCode/ShellCommandMessage/ShellCommandMessageFactory.h \
    sourceCode/ShellCommandMessage/ShellCommandRequest.h \
    sourceCode/ShellCommandMessage/ShellCommandResponse.h \
    sourceCode/Environment/ShellCommandGenericOutput.h \
    sourceCode/Configure/SystemEnvironmentConfigure.h \
    sourceCode/TraceLog/Trace.h \
    sourceCode/TraceLog/TraceBuf.h \
    sourceCode/TraceLog/TraceConsole.h \
    sourceCode/TraceLog/TraceFile.h \
    sourceCode/PlatformWrapper/SystemApi.h \
    doubleclickedbutton.h \
    ftpdownloaddialog.h \
    alphanum.h \
    formfortest.h \
    yunwei.h \
    ftpuploaddialog.h



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
    monitorwindow.ui \
    m.ui \
    ftpdownloaddialog.ui \
    formfortest.ui \
    yunwei.ui \
    ftpuploaddialog.ui

RESOURCES += \
    hungclustermanager1.qrc

win32:RC_ICONS += ./Resources/applicationIcon.ico
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


LIBS += -lWs2_32
