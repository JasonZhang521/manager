#ifndef _NETWORK_SOCKETIMP_H_
#define _NETWORK_SOCKETIMP_H_
#include "SystemErrorInfo.h"
#include "SocketWrapper.h"
#include "Component.h"
#include "Macro.h"
#include <sstream>
#include <string>
#include <iostream>

namespace Network {

class SocketImp
{
    SocketAddressFamily addrFamily_;
    SocketType type_;
    SocketProtocol protocol_;
    SocketHandle fd_;
public:
    SocketImp(const SocketAddressFamily& addrFamily,
              const SocketType& type,
              const SocketProtocol& protocol,
              const SocketHandle& fd);
    SocketImp(const SocketAddressFamily& addrFamily,
           const SocketType& type,
           const SocketProtocol& protocol);
    ~SocketImp();

    virtual void handleRead() { }

    virtual void handleWrite() { }

    std::string getErrorInfo();
    int getErrorNo();
    inline SocketHandle getFd()
    {
        return fd_;
    }

    inline int init()
    {
        int ret = PlatformWrapper::InitSocket();
        if ( ret != SOCKET_SUCCESS)
        {
            return ret;
        }
        int yes = 1;
        // set reuse address
        ret = setSockOpt(SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<SocketOptVal>(&yes), sizeof(yes));
        if ( ret != SOCKET_SUCCESS)
        {
            return ret;
        }

        // set non-blocking
        ret = setBlocking(false);
        if ( ret != SOCKET_SUCCESS)
        {
            return ret;
        }

        return SOCKET_SUCCESS;
    }

    inline int bind(const SocketAddress* localAddress, SocketAddresstLength addrLen) const
    {
        return PlatformWrapper::Bind(fd_, localAddress, addrLen);
    }

    inline int connect(const SocketAddress* remoteAddress, SocketAddresstLength addrLen) const
    {
        return PlatformWrapper::Connect(fd_, remoteAddress, addrLen);
    }

    inline int close()
    {
        return PlatformWrapper::Close(fd_);
    }

    inline int shutdown(SocketShutDownFlag how) const
    {
        return PlatformWrapper::Shutdown(fd_, how);
    }

    inline int accept(SocketAddress* clientAddr, SocketAddresstLength* addrLen, SocketFlag flags) const
    {
        return PlatformWrapper::Accept(fd_, clientAddr, addrLen, flags);
    }

    inline int listen(int backlog) const
    {
        return PlatformWrapper::Listen(fd_, backlog);
    }

    inline int recv(SocketDataBuffer buf, SocketDataBufferSize bufLen, SocketFlag flags) const
    {
        return PlatformWrapper::Recv(fd_, buf, bufLen, flags);
    }

    inline int recvFrom(SocketDataBuffer buf, SocketDataBufferSize bufLen, SocketFlag flags,
                 SocketAddress* srcAddr, SocketAddresstLength& addrLen) const
    {
        return PlatformWrapper::RecvFrom(fd_, buf, bufLen, flags, srcAddr, &addrLen);
    }

    inline int send(const SocketDataBuffer buf, SocketDataBufferSize bufLen, SocketFlag flags) const
    {
        return PlatformWrapper::Send(fd_, buf, bufLen, flags);
    }

    inline int sendTo(const SocketDataBuffer buf, SocketDataBufferSize bufLen, SocketFlag flags,
               const SocketAddress* destAddr, SocketAddresstLength addrLen) const
    {
        return PlatformWrapper::SendTo(fd_, buf, bufLen, flags, destAddr, addrLen);
    }

    inline int setSockOpt(SocketOptLevel level, SocketOptName optname,
                          const SocketOptVal optval, SocketOptLength optlen)
    {
        return PlatformWrapper::SetSockOpt(fd_, level, optname, optval, optlen);
    }

    inline int getSockOpt(SocketOptLevel level, SocketOptName optname,
                          SocketOptVal optval, SocketOptLength* optlen)
    {
        return PlatformWrapper::GetSockOpt(fd_, level, optname, optval, optlen);
    }

    inline int getSockName(SocketAddress* addr, SocketAddresstLength& addrLen)
    {
        return PlatformWrapper::GetSockName(fd_, addr, &addrLen);
    }

    inline int getPeerName(SocketAddress* addr, SocketAddresstLength& addrLen)
    {
        return PlatformWrapper::GetPeerName(fd_, addr, &addrLen);
    }

    inline int setBlocking(bool blocking)
    {
        return PlatformWrapper::SetBlocking(fd_, blocking);
    }

    inline std::string toString() const
    {
        std::stringstream ss;
        ss << "[" << "addressFamily=" << addrFamily_ <<", socketType=" << type_ << ", socketProtocol=" << protocol_ << ", fd=" << fd_ << "]";
        return ss.str();
    }

public:
     GETCLASSNAME(SocketImp)
};

}

#endif // _NETWORK_SOCKETIMP_H_
