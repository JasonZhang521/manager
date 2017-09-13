/*
 * WinWSAException.h
 *
 *  Created on: 2015Äê4ÔÂ21ÈÕ
 *      Author: euwyzbc
 */

#ifndef WINWSAEXCEPTION_H_
#define WINWSAEXCEPTION_H_

#include "GeneralException.h"


namespace WinNetwork {


enum WinWsaErrorCode
{
  WIN_WSANOERROR = 0,
  WIN_WSAEFAULT = 10014,
  WIN_WSAEINPROGRESS = 10036,
  WIN_WSAEPROCLIM = 10067,
  WIN_WSASYSNOTREADY = 10091,
  WIN_WSAVERNOTSUPPORTED = 10092
};



class WinWSAException: public GeneralException
{
public:
  WinWSAException(int errorCode) noexcept;
  WinWSAException(const WinWSAException&) noexcept;
  WinWSAException& operator= (const WinWSAException&) noexcept;
  virtual ~WinWSAException();
  virtual const char* what() const noexcept;
private:
  int errorCode_;
};

} /* namespace WinNetwork */

#endif /* WINWSAEXCEPTION_H_ */
