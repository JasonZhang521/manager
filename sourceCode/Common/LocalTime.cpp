/*
 * LocalTime.cpp
 *
 *  Created on: 2015Äê5ÔÂ6ÈÕ
 *      Author: euwyzbc
 */
#include <iostream>
#include <time.h>
#include <stdio.h>
#include "LocalTime.h"

LocalTime::LocalTime() {
  // TODO Auto-generated constructor stub

}

LocalTime::~LocalTime() {
  // TODO Auto-generated destructor stub
}


std::string LocalTime::getCurrentTime()
{
  time_t rawTime = time(0);
  struct tm* timeinfo;
  timeinfo = localtime(&rawTime);
  std::string str = std::string(asctime(timeinfo));
  return str.substr(0, str.size() - 1);
}
