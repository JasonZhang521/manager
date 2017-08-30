/*
 * ExceptionConfigure.cpp
 *
 *  Created on: 2015Äê4ÔÂ23ÈÕ
 *      Author: euwyzbc
 */

#include "ExceptionConfigure.h"

//namespace Common{

ExceptionConfigure::ExceptionConfigure()
:usingException_(false)
{
  // TODO Auto-generated constructor stub

}

ExceptionConfigure::~ExceptionConfigure() {
  // TODO Auto-generated destructor stub
}

void ExceptionConfigure::setExceptionFlag(bool usingException)
{
  usingException_ = usingException;
}

bool ExceptionConfigure::usingException() const
{
  return usingException_;
}

//} //namespace Common

