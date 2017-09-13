/*
 * LocalTime.h
 *
 *  Created on: 2015Äê5ÔÂ6ÈÕ
 *      Author: euwyzbc
 */

#ifndef LOCALTIME_H_
#define LOCALTIME_H_
#include <stdint.h>
#include <string>
class LocalTime {
public:
  LocalTime();
  virtual ~LocalTime();
  static std::string getCurrentTime();
  static std::string getTimeBeforeCurrent(uint32_t elapseSecond);
  static std::string getTimeAfterCurrent(uint32_t elapseSecond);
  static std::string getTimeBytimeStamp(uint64_t timeStamp);
};

#endif /* LOCALTIME_H_ */
