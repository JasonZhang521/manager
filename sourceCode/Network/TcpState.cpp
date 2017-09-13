#include "TcpState.h"
namespace Network {

std::string toString(TcpState state)
{
    switch (state) {
    case TcpState::Tcp_Closed:
        return "Tcp_Closed";
    case TcpState::Tcp_Connecting:
        return "Tcp_Connecting";
    case TcpState::Tcp_Sending:
        return "Tcp_Sending";
    case TcpState::Tcp_Receiving:
        return "Tcp_Receiving";
    case TcpState::Tcp_Listening:
        return "Tcp_Listening";
    case TcpState::Tcp_Established:
        return "Tcp_Established";
    default:
        return std::string("");
    }
}

}
