/*
 * WinWSAException.cpp
 *
 *  Created on: 2015Äê4ÔÂ21ÈÕ
 *      Author: euwyzbc
 */
#include <sstream>
#include "WinWSAException.h"

namespace WinNetwork {

WinWSAException::WinWSAException(int errorCode) noexcept
:errorCode_(errorCode)
{

}
WinWSAException::WinWSAException(const WinWSAException& e) noexcept
:GeneralException(e)
,errorCode_(e.errorCode_)
{

}
WinWSAException& WinWSAException::operator= (const WinWSAException& e) noexcept
{
  errorMsg_ = e.errorMsg_;
  errorCode_ = e.errorCode_;
  return *this;
}
WinWSAException::~WinWSAException()
{

}
const char* WinWSAException::what() const noexcept
{
      std::stringstream strErrorBuf;
      strErrorBuf << "WSA Error Code:" << errorCode_ << ", ";
      if (errorMsg_.size() > 0)
      {
          strErrorBuf << " addition error msg:" << errorMsg_;
      }
      strErrorBuf << std::endl;

      return strErrorBuf.str().data();
}

} /* namespace WinNetwork */
