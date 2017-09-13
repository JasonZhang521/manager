#ifndef _CONNECTION_ICONNECTIONRX_H
#define _CONNECTION_ICONNECTIONRX_H


namespace Connection {

class IConnectionMessage;

class IConnectionRx
{
public:
    IConnectionRx();
    virtual ~IConnectionRx();

    virtual void connect() = 0;
    virtual void send(const IConnectionMessage& msg) = 0;
    virtual void disconnect() = 0;
};

}
#endif // _CONNECTION_ICONNECTIONRX_H
