/*
 * WinSocket.cpp
 *
 *  Created on: 2015Äê4ÔÂ20ÈÕ
 *      Author: euwyzbc
 */
#include <ws2tcpip.h>
#include <windows.h>

#include "WinSocket.h"
#include "WinWSAException.h"
#include "Configure.h"

namespace WinNetwork {

WinSocket::WinSocket()
:lpWSAData_(new WSADATA)
,socketId_(INVALID_SOCKET)
{
  // TODO Auto-generated constructor stub

}

WinSocket::~WinSocket() {
  // TODO Auto-generated destructor stub
  ::WSACleanup();
  delete lpWSAData_;
}

void WinSocket::initialSocket() const
{
  WORD wVersionRequested;
  wVersionRequested = MAKEWORD(2, 2);
  int error = ::WSAStartup(wVersionRequested, lpWSAData_);

  if (WIN_WSANOERROR != error)
  {
    if (Configure::getInstance().usingException())
    {
      throw WinWSAException(error);
    }
  }
}

int WinSocket::createSocket(int af, int type, int protocol)
{
  socketId_ = ::socket(af, type, protocol);
  if (INVALID_SOCKET == socketId_)
  {
    if (Configure::getInstance().usingException())
    {
      throw WinWSAException(WSAGetLastError());
    }
  }

  return static_cast<int>(socketId_);
}

int WinSocket::bind(int socketId, const struct sockaddr *name, int namelen)
{
  int error = ::bind(static_cast<SOCKET>(socketId), name, namelen);
  if (WIN_WSANOERROR != error)
  {
    if (Configure::getInstance().usingException())
    {
        throw WinWSAException(error);
    }
  }
  return error;
}


} /* namespace WinNetwork */
