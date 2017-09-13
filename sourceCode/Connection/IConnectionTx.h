#ifndef _CONNECTION_ICONNECTIONRX_H_
#define _CONNECTION_ICONNECTIONRX_H_

namespace Serialize {
class ReadBuffer;
}

namespace Connection {

class IConnectionTx
{
public:
    IConnectionTx();
    virtual ~IConnectionTx();
    virtual void onConnect() = 0;
    virtual void onReceive(Serialize::ReadBuffer& readBuffer) = 0;
    virtual void onDisconnect() = 0;
};

}

#endif // _CONNECTION_ICONNECTIONRX_H_
