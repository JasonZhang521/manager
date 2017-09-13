#ifndef _NETWORK_TCPSOCKET_H
#define _NETWORK_TCPSOCKET_H
#include "SocketImp.h"
#include "IpSocketEndpoint.h"
#include "Component.h"
#include "Macro.h"

namespace Network {

enum class TcpSocketType
{
    TcpServer, // Socket as Server
    TcpClient, // Socket as Client
    TcpServerClient // Socket as accept client in Server
};

class TcpSocket : public SocketImp
{
    TcpSocketType type_;
    IpSocketEndpoint localEndpoint_;
    IpSocketEndpoint remoteEndpoint_;
public:
    // For server
    explicit TcpSocket(const IpSocketEndpoint& localEndpoint);
    // For accept client for server
    TcpSocket(const SocketHandle& fd,
              const IpSocketEndpoint& localEndpoint,
              const IpSocketEndpoint& remoteEndpoint);
    // For client
    TcpSocket(const IpSocketEndpoint& localEndpoint, const IpSocketEndpoint& remoteEndpoint);

    virtual ~TcpSocket();
    inline const IpSocketEndpoint& getLocalEndpoint() const {return localEndpoint_;}
    inline const IpSocketEndpoint& getRemoteEndpoint() const {return remoteEndpoint_;}

    int bind() const;
    int connect() const;
    int accept(IpSocketEndpoint& remoteEndPoint, SocketFlag flag) const;

    std::string toString() const;
    std::ostream& operator<< (std::ostream& os) const;

public:
     GETCLASSNAME(SocketImp)
};

std::ostream& operator<< (std::ostream& os, const TcpSocket& socket);

}
#endif // _NETWORK_TCPSOCKET_H
