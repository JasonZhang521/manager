/*
 * LocalTime.cpp
 *
 *  Created on: 2015Äê5ÔÂ6ÈÕ
 *      Author: euwyzbc
 */
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <ratio>
#include <chrono>
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

std::string LocalTime::getTimeBeforeCurrent(uint32_t elapseSecond)
{
    using namespace std::chrono;
    system_clock::time_point now = system_clock::now();
    std::time_t last = system_clock::to_time_t(now - std::chrono::seconds(elapseSecond));
    struct tm* timeinfo;
    timeinfo = localtime(&last);
    std::string str = std::string(asctime(timeinfo));
    return str.substr(0, str.size() - 1);
}

std::string LocalTime::getTimeAfterCurrent(uint32_t elapseSecond)
{
    using namespace std::chrono;
    system_clock::time_point now = system_clock::now();
    std::time_t future = system_clock::to_time_t(now + std::chrono::seconds(elapseSecond));
    struct tm* timeinfo;
    timeinfo = localtime(&future);
    std::string str = std::string(asctime(timeinfo));
    return str.substr(0, str.size() - 1);
}

std::string LocalTime::getTimeBytimeStamp(uint64_t timeStamp)
{
    using namespace std::chrono;
    std::time_t timePoint = system_clock::to_time_t(system_clock::from_time_t(timeStamp));
    struct tm* timeinfo;
    timeinfo = localtime(&timePoint);
    std::string str = std::string(asctime(timeinfo));
    return str.substr(0, str.size() - 1);
}
