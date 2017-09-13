#ifndef _NETWORK_TCPSTATE_H_
#define _NETWORK_TCPSTATE_H_
#include <string>

namespace Network {
enum class TcpState
{
    Tcp_Closed,
    Tcp_Connecting,
    Tcp_Sending,
    Tcp_Receiving,
    Tcp_Listening,
    Tcp_Established
};

std::string toString(TcpState state);

}

#endif // _NETWORK_TCPSTATE_H_
