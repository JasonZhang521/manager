#ifndef _NETWORK_ITCPCLIENT_H_
#define _NETWORK_ITCPCLIENT_H_
#include "TcpResult.h"
#include <memory>

namespace Serialize {
class WriteBuffer;
}

namespace Network {

class TcpBuffer;
class IpSocketEndpoint;
class ITcpConnectionReceiver;
class ITcpClient
{
public:
    ITcpClient();
    virtual ~ITcpClient();
    virtual TcpResult init() = 0;
    virtual TcpResult bind() = 0;
    virtual TcpResult connect() = 0;
    virtual TcpResult send(const Serialize::WriteBuffer&) = 0;
    virtual TcpResult receive() = 0;
    virtual TcpResult disconnect() = 0;
    virtual TcpResult cleanup() = 0;
    virtual TcpResult restart() = 0;
    virtual void setConnectionReceiver(std::shared_ptr<ITcpConnectionReceiver> receiver) = 0;
    virtual IpSocketEndpoint getRemoteEndpoint() const = 0;
    virtual IpSocketEndpoint getLocalEndpoint() const = 0;
};

}

#endif // ITCPCLIENT_H
