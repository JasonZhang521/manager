#ifndef _NETWORK_ITCPSERVER_H_
#define _NETWORK_ITCPSERVER_H_
#include "TcpResult.h"
#include <memory>
namespace Network {
class ITcpConnectionAcceptor;
class ITcpServer
{
public:
    ITcpServer();
    ~ITcpServer();
    virtual TcpResult init() = 0;
    virtual TcpResult bind() = 0;
    virtual TcpResult listen(int backlog) = 0;
    virtual TcpResult accept(int flag) = 0;
    virtual TcpResult disconnect() = 0;
    virtual TcpResult cleanup() = 0;
    virtual void setConnectionAcceptor(std::shared_ptr<ITcpConnectionAcceptor> acceptor) = 0;
};

}
#endif // _NETWORK_ITCPSERVER_H_
