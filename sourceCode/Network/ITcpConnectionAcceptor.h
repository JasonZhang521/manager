#ifndef _NETWORK_ITCPCONNECTIONACCEPTOR_H_
#define _NETWORK_ITCPCONNECTIONACCEPTOR_H_

namespace Network {
class IpSocketEndpoint;
class ITcpConnectionAcceptor
{
public:
    ITcpConnectionAcceptor();
    virtual ~ITcpConnectionAcceptor();
    virtual void onAccept(int fd, const IpSocketEndpoint& localEndPoint, const IpSocketEndpoint& remoteEndPoint) = 0;
};

}

#endif // _NETWORK_ITCPCONNECTIONACCEPTOR_H_
