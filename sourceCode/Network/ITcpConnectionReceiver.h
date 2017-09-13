#ifndef ITCPCONNECTIONRECEIVER_H
#define ITCPCONNECTIONRECEIVER_H

namespace Serialize {
class ReadBuffer;
}
namespace Network {
class ITcpConnectionReceiver
{
public:
    ITcpConnectionReceiver();
    virtual ~ITcpConnectionReceiver();
    virtual void onConnect() = 0;
    virtual void onReceive(Serialize::ReadBuffer& readBuffer) = 0;
    virtual void onDisconnect() = 0;
};
}

#endif // ITCPCONNECTIONRECEIVER_H
