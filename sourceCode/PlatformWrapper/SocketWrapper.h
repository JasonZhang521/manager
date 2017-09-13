#ifndef _IOPLATFORMWRAPPER_SOCKETWRAPPER_H_
#define _IOPLATFORMWRAPPER_SOCKETWRAPPER_H_
#include "SocketWrapperDef.h"
#include <string>

#ifdef WIN32
#include <winsock2.h>
#else
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

namespace PlatformWrapper {

// Ip address handling
inline SocketAddressIn& SocketAddressToAddressIn(SocketAddress& address)
{
    return *reinterpret_cast<SocketAddressIn*>(&address);
}

inline SocketAddressIn6& SocketAddressToAddressIn6(SocketAddress& address)
{
    return *reinterpret_cast<SocketAddressIn6*>(&address);
}

inline SocketInetAddress& getInetAddressFromSocketAddress(SocketAddress& address)
{
    return *reinterpret_cast<SocketInetAddress*>(&SocketAddressToAddressIn(address).sin_addr);
}

inline SocketInet6Address& getInet6AddressFromSocketAddress(SocketAddress& address)
{
    return *reinterpret_cast<SocketInet6Address*>(&SocketAddressToAddressIn6(address).sin6_addr);
}

inline std::string InetNtoa(SocketInetAddress address)
{
    char* addrStr = inet_ntoa(address);
    return std::string(addrStr);
}

// Ip address handling end

#ifdef WIN32

int InitSocket();

inline int Cleanup()
{
    return ::WSACleanup();
}

inline Close(SocketHandle sockfd)
{
    return ::closesocket(sockfd);
}

inline int Accept(SocketHandle sockfd, SocketAddress* addr, SocketAddresstLength *addrlen, SocketFlag flags)
{
    static_cast<void>(flags);
    return ::accept(sockfd, addr, addrlen);
}

#if (_WIN32_WINNT >= 0x0600)
inline int InetPton(SocketAddressFamily af, const char *src, void *dst)
{
    ::InetPton(af, src, dst);
}

inline const char* InetNtop(SocketAddressFamily af, const void *src, char *dst, SocketLength size)
{
    return ::InetNtop(af, src, dst, size);
}
#else
int InetPton(SocketAddressFamily af, const char *src, void *dst);
const char* InetNtop(SocketAddressFamily af, const void *src, char *dst, SocketAddresstLength size);
#endif
inline int GetIfAddrs(SocketIfAddress* ifAddr)
{
  static_cast<void>(ifAddr);
  return SOCKET_SUCCESS;
}


#else

inline int InitSocket()
{
    return SOCKET_SUCCESS;
}

inline int Cleanup()
{
    return 0;
}

inline int Close(SocketHandle sockfd)
{
    return ::close(sockfd);
}

inline int Accept(SocketHandle sockfd, SocketAddress* addr, SocketLength *addrlen, SocketFlag flags)
{
	static_cast<void>(flags);
    return ::accept(sockfd, addr, addrlen);
}

inline int Poll(SocketPollFdSet* fds, SocketPollFdNumber nfds, int timeout)
{
    ::poll(fds, nfds, timeout);
}

inline int InetPton(SocketAddressFamily af, const char *src, void *dst)
{
    ::inet_pton(af, src, dst);
}

inline const char* InetNtop(SocketAddressFamily af, const void *src, char *dst, SocketLength size)
{
    return ::inet_ntop(af, src, dst, size);
}

inline int GetIfAddrs(SocketIfAddress* ifAddr)
{
	 return getifaddrs(ifAddr);
}
#endif

inline SocketHandle CreateSocket(SocketAddressFamily addrFamily, SocketType type, SocketProtocol protocol)
{
    return ::socket(addrFamily, type, protocol);
}

inline int Connect(SocketHandle sockfd, const SocketAddress* addr, SocketAddresstLength addrLen)
{
    return ::connect(sockfd, addr, addrLen);
}

inline SocketDataSize Send(SocketHandle sockfd, const SocketDataBuffer buf, SocketDataBufferSize len, SocketFlag flags)
{
    return ::send(sockfd, buf, len, flags);
}

inline SocketDataSize SendTo(SocketHandle sockfd, const SocketDataBuffer buf, SocketDataBufferSize len, SocketFlag flags,
               const SocketAddress* destAddr, SocketAddresstLength addrLen)
{
    return ::sendto(sockfd, buf, len, flags, destAddr, addrLen);
}

inline SocketDataSize Recv(SocketHandle sockfd, SocketDataBuffer buf, SocketDataBufferSize len, SocketFlag flags)
{
    return ::recv(sockfd, buf, len, flags);
}

inline SocketDataSize RecvFrom(SocketHandle sockfd, SocketDataBuffer buf, SocketDataBufferSize len, SocketFlag flags,
                 SocketAddress* srcAddr, SocketAddresstLength *addrLen)
{
    return ::recvfrom(sockfd, buf, len, flags, srcAddr, addrLen);
}

inline int Shutdown(SocketHandle sockfd, SocketShutDownFlag how)
{
    return ::shutdown(sockfd, how);
}

inline int Bind(SocketHandle sockfd, const SocketAddress* addr, SocketAddresstLength addrLen)
{
    return ::bind(sockfd, addr, addrLen);
}

inline int Listen(SocketHandle sockfd, int backlog)
{
    return ::listen(sockfd, backlog);
}

inline int Select(SocketHandle nfds, SocketFdSet* readfds, SocketFdSet* writefds,
           SocketFdSet* exceptfds, SocketTimeVal* timeout)
{
    return ::select(nfds, readfds, writefds, exceptfds, timeout);
}

inline void FdSet(SocketHandle sockfd, SocketFdSet* fds)
{
    FD_SET(sockfd, fds);
}

inline void FdZero(SocketFdSet* fds)
{
    FD_ZERO(fds);
}

inline void FdClear(SocketHandle sockfd, SocketFdSet* fds)
{
    FD_CLR(sockfd, fds);
}

inline int FdIsSet(SocketHandle sockfd, SocketFdSet* fds)
{
    return FD_ISSET(sockfd, fds);
}

inline int SetSockOpt(SocketHandle sockfd, SocketOptLevel level, SocketOptName optname,
                      const SocketOptVal optval, SocketOptLength optlen)
{
    return ::setsockopt(sockfd, level, optname, optval, optlen);
}

inline int GetSockOpt(SocketHandle sockfd, SocketOptLevel level, SocketOptName optname,
                      SocketOptVal optval, SocketOptLength* optlen)
{
    return ::getsockopt(sockfd, level, optname, optval, optlen);
}

inline int GetSockName(SocketHandle sockfd, SocketAddress *addr, SocketAddresstLength *addrLen)
{
    return ::getsockname(sockfd, addr, addrLen);
}

inline int GetPeerName(SocketHandle sockfd, SocketAddress *addr, SocketAddresstLength *addrLen)
{
    return ::getpeername(sockfd, addr, addrLen);
}

int SetBlocking(SocketHandle sockfd, bool blocking);

int GetHostName(std::string& hostname);

inline std::string GetHostName()
{
    std::string hostName;
    GetHostName(hostName);
    return hostName;
}

inline SocketHostent* GetHostByName(const std::string& hostname)
{
    return gethostbyname(hostname.c_str());
}

}


#endif // SOCKETWRAPPER_H
