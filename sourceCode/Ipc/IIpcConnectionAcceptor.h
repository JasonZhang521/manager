#ifndef IIPCCONNECTIONACCEPTOR_H
#define IIPCCONNECTIONACCEPTOR_H

namespace Network {
class ITcpServer;
class IpSocketEndpoint;
}

namespace Ipc {

class IIpcConnectionAcceptor
{
public:
    IIpcConnectionAcceptor();
    ~IIpcConnectionAcceptor();
    virtual void onAccept(int fd,
                          const Network::IpSocketEndpoint& localEndPoint,
                          const Network::IpSocketEndpoint& remoteEndPoint) = 0;
};

}

#endif // IIPCCONNECTIONACCEPTOR_H
