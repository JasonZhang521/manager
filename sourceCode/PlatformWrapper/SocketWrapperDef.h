#ifndef _IOPLATFORMWRAPPER_SOCKETWRAPPERDEF_H_
#define _IOPLATFORMWRAPPER_SOCKETWRAPPERDEF_H_

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>
#include <errno.h>
#include <netinet/in.h>
#include <ifaddrs.h>
#endif

#define UNSUPPORTED_SOCKET_VERION 0X7FFFFFFF

#ifdef WIN32
#define SOCKET_SUCCESS 0

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#else
#define SOCKET_SUCCESS 0
#define SOCKET_ERROR -1
#endif


#ifdef WIN32
// type
using SocketError = int;
using SocketHandle = SOCKET;
using SocketLength = int;
using SocketAddressFamily = int;
using SocketType = int;
using SocketProtocol = int;
using SocketAddress = struct sockaddr;
using SocketAddressIn = struct sockaddr_in;
using SocketAddressIn6 = struct sockaddr_in6;
using SocketAddresstLength = int;
using SocketFlag = int;
using SocketDataSize = int;
using SocketDataBuffer = char*;
using SocketDataBufferSize = int;
using SocketShutDownFlag = int;
using SocketFdSet = fd_set;
using SocketTimeVal = struct timeval;
using SocketInetAddress = struct in_addr;
using SocketInet6Address = struct in6_addr;
using SocketOptLevel = int;
using SocketOptName = int;
using SocketOptVal = char*;
using SocketHostent = struct hostent;
using SocketOptLength = int;
using SocketIfAddress = void;

// const value
const SocketHandle InvalidSocketHandle = INVALID_SOCKET;

// Error Code
const SocketError SOCKET_NOTINITIALISED = WSANOTINITIALISED;
const SocketError SOCKET_NETDOWN = WSAENETDOWN;
const SocketError SOCKET_ADDRNOTAVAIL = WSAEADDRNOTAVAIL;
const SocketError SOCKET_EINVAL = WSAEINVAL;
const SocketError SOCKET_EHOSTUNREACH = WSAEHOSTUNREACH;
const SocketError SOCKET_ENOBUFS = WSAENOBUFS;
// const SocketError SOCKET_EWOULDBLOCK = WSAEWOULDBLOCK;

const SocketError SOCKET_EACCES = WSAEACCES;
//const SocketError SOCKET_EPERM = EPERM;
const SocketError SOCKET_EADDRINUSE = WSAEADDRINUSE;
const SocketError SOCKET_EAFNOSUPPORT = WSAEAFNOSUPPORT;
const SocketError SOCKET_EAGAIN = WSAEWOULDBLOCK;
const SocketError SOCKET_EALREADY = WSAEALREADY;
//const SocketError SOCKET_EBADF = EBADF;
const SocketError SOCKET_ECONNREFUSED = WSAECONNREFUSED;
const SocketError SOCKET_EFAULT = WSAEFAULT;
const SocketError SOCKET_EINPROGRESS = WSAEINPROGRESS;
const SocketError SOCKET_EINTR = WSAEINTR;
const SocketError SOCKET_EISCONN = WSAEISCONN;
const SocketError SOCKET_ENETUNREACH = WSAENETUNREACH;
const SocketError SOCKET_ENOTSOCK = WSAENOTSOCK;
const SocketError SOCKET_ETIMEDOUT = WSAETIMEDOUT;
// Error Code end

// Socket Address Family
const SocketAddressFamily SOCKET_AF_UNSPEC = AF_UNSPEC;
const SocketAddressFamily SOCKET_AF_NETBIOS = AF_NETBIOS;
const SocketAddressFamily SOCKET_AF_IRDA = AF_IRDA;
const SocketAddressFamily SOCKET_AF_BTH = AF_BTH;
const SocketAddressFamily SOCKET_AF_INET = AF_INET;
const SocketAddressFamily SOCKET_AF_IPX = AF_IPX;
const SocketAddressFamily SOCKET_AF_APPLETALK = AF_APPLETALK;
const SocketAddressFamily SOCKET_AF_INET6 = AF_INET6;
// Socket Address Family end

// Socket Type
const SocketType SOCKET_SOCK_STREAM = SOCK_STREAM;
const SocketType SOCKET_SOCK_DGRAM = SOCK_DGRAM;
const SocketType SOCKET_SOCK_RAW = SOCK_RAW;
const SocketType SOCKET_SOCK_RDM = SOCK_RDM;
const SocketType SOCKET_SOCK_SEQPACKET = SOCK_SEQPACKET;
// Socket Type end

// Socket Protocol
const SocketProtocol SOCKET_IPPROTO_ICMP = IPPROTO_ICMP;
const SocketProtocol SOCKET_IPPROTO_IGMP = IPPROTO_IGMP;
//const SocketProtocol SOCKET_BTHPROTO_RFCOMM = BTHPROTO_RFCOMM;
const SocketProtocol SOCKET_IPPROTO_TCP = IPPROTO_TCP;
const SocketProtocol SOCKET_IPPROTO_UDP = IPPROTO_UDP;
const SocketProtocol SOCKET_IPPROTO_ICMPV6 = IPPROTO_ICMPV6;
//const SocketProtocol SOCKET_IPPROTO_RM = IPPROTO_RM;
// Socket Protocol end

// Socket Flag
const SocketFlag SOCKET_FLAG_NONE = 0;
const SocketFlag SOCKET_FLAG_MSG_DONTROUTE = MSG_DONTROUTE;
const SocketFlag SOCKET_FLAG_MSG_OOB = MSG_OOB;
// Socket Flag end

// Socket ShutDown Flag
const SocketShutDownFlag SOCKET_SD_RECEIVE = SD_RECEIVE;
const SocketShutDownFlag SOCKET_SD_SEND = SD_SEND;
const SocketShutDownFlag SOCKET_SD_BOTH = SD_BOTH;
// Socket ShutDown Flag end

#else

// type
using SocketError = int;
using SocketHandle = int;
using SocketLength = socklen_t;
using SocketAddressFamily = int;
using SocketType = int;
using SocketProtocol = int;
using SocketAddress = struct sockaddr;
using SocketAddressIn = struct sockaddr_in;
using SocketAddressIn6 = struct sockaddr_in6;
using SocketAddresstLength = socklen_t;
using SocketFlag = int;
using SocketDataSize = ssize_t;
using SocketDataBuffer = void*;
using SocketDataBufferSize = ssize_t;
using SocketShutDownFlag = int;
using SocketFdSet = fd_set;
using SocketTimeVal = struct timeval;
using SocketPollFdSet = struct pollfd;
using SocketPollFdNumber = nfds_t;
using SocketPollEvent = short;
using SocketInetAddress = struct in_addr;
using SocketInet6Address = struct in6_addr;
using SocketOptLevel = int;
using SocketOptName = int;
using SocketOptVal = void*;
using SocketOptLength = socklen_t;
using SocketHostent = struct hostent;
using SocketIfAddress = struct ifaddrs*;

// const value
const SocketHandle InvalidSocketHandle = -1;

// Error Code
const SocketError SOCKET_EACCES = EACCES;
const SocketError SOCKET_EPERM = EPERM;
const SocketError SOCKET_EADDRINUSE = EADDRINUSE;
const SocketError SOCKET_EAFNOSUPPORT = EAFNOSUPPORT;
const SocketError SOCKET_EAGAIN = EAGAIN;
const SocketError SOCKET_EALREADY = EALREADY;
const SocketError SOCKET_EBADF = EBADF;
const SocketError SOCKET_ECONNREFUSED = ECONNREFUSED;
const SocketError SOCKET_EFAULT = EFAULT;
const SocketError SOCKET_EINPROGRESS = EINPROGRESS;
const SocketError SOCKET_EINTR = EINTR;
const SocketError SOCKET_EISCONN = EISCONN;
const SocketError SOCKET_ENETUNREACH = ENETUNREACH;
const SocketError SOCKET_ENOTSOCK = ENOTSOCK;
const SocketError SOCKET_ETIMEDOUT = ETIMEDOUT;
// Error Code end

// Socket Address Family
const SocketAddressFamily SOCKET_AF_UNIX = AF_UNIX;
const SocketAddressFamily SOCKET_AF_LOCAL = AF_LOCAL;
const SocketAddressFamily SOCKET_AF_NETLINK  = AF_NETLINK;
const SocketAddressFamily SOCKET_AF_X25  = AF_X25;
const SocketAddressFamily SOCKET_AF_AX25 = AF_AX25;
const SocketAddressFamily SOCKET_AF_ATMPVC = AF_ATMPVC;
const SocketAddressFamily SOCKET_AF_PACKET = AF_PACKET;
const SocketAddressFamily SOCKET_AF_INET = AF_INET;
const SocketAddressFamily SOCKET_AF_IPX = AF_IPX;
const SocketAddressFamily SOCKET_AF_APPLETALK = AF_APPLETALK;
const SocketAddressFamily SOCKET_AF_INET6 = AF_INET6;
const SocketAddressFamily SOCKET_AF_UNSPEC = AF_UNSPEC;
// Socket Address Family end

// Socket Type
const SocketType SOCKET_SOCK_STREAM = SOCK_STREAM;
const SocketType SOCKET_SOCK_DGRAM = SOCK_DGRAM;
const SocketType SOCKET_SOCK_RAW = SOCK_RAW;
const SocketType SOCKET_SOCK_RDM = SOCK_RDM;
const SocketType SOCKET_SOCK_SEQPACKET = SOCK_SEQPACKET;
const SocketType SOCKET_SOCK_NONBLOCK = SOCK_NONBLOCK;
const SocketType SOCKET_SOCK_CLOEXEC = SOCK_CLOEXEC;
// Socket Type end

// Socket Protocol
const SocketProtocol SOCKET_IPPROTO_ICMP = IPPROTO_ICMP;
const SocketProtocol SOCKET_IPPROTO_IGMP = IPPROTO_IGMP;
//const SocketProtocol SOCKET_BTHPROTO_RFCOMM = BTHPROTO_RFCOMM;
const SocketProtocol SOCKET_IPPROTO_TCP = IPPROTO_TCP;
const SocketProtocol SOCKET_IPPROTO_UDP = IPPROTO_UDP;
const SocketProtocol SOCKET_IPPROTO_ICMPV6 = IPPROTO_ICMPV6;
//const SocketProtocol SOCKET_IPPROTO_RM = IPPROTO_RM;
// Socket Protocol end

// Socket Flag
const SocketFlag SOCKET_FLAG_NONE = 0;
const SocketFlag SOCKET_FLAG_MSG_CONFIRM = MSG_CONFIRM;
const SocketFlag SOCKET_FLAG_MSG_DONTROUTE = MSG_DONTROUTE;
const SocketFlag SOCKET_FLAG_MSG_DONTWAIT = MSG_DONTWAIT;
const SocketFlag SOCKET_FLAG_MSG_EOR = MSG_EOR;
const SocketFlag SOCKET_FLAG_MSG_MORE = MSG_MORE;
const SocketFlag SOCKET_FLAG_MSG_NOSIGNAL = MSG_NOSIGNAL;
const SocketFlag SOCKET_FLAG_MSG_OOB = MSG_OOB;
// Socket Flag end

// Socket Shutdown Flag
const SocketShutDownFlag SOCKET_SD_RECEIVE = SHUT_RD;
const SocketShutDownFlag SOCKET_SD_SEND = SHUT_WR;
const SocketShutDownFlag SOCKET_SD_BOTH = SHUT_RDWR;
// Socket Shutdown Flag end

// Poll Event
const SocketPollEvent SOCKET_POLLIN = POLLIN;
const SocketPollEvent SOCKET_POLLPRI = POLLPRI;
const SocketPollEvent SOCKET_POLLOUT = POLLOUT;
const SocketPollEvent SOCKET_POLLRDHUP = POLLRDHUP;
const SocketPollEvent SOCKET_POLLERR = POLLERR;
const SocketPollEvent SOCKET_POLLHUP = POLLHUP;
const SocketPollEvent SOCKET_POLLNVAL = POLLNVAL;
// Poll Event end

#endif

#endif // _NETWORK_SOCKETWRAPPERDEF_H_
