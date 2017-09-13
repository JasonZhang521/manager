/*
 * LocalTime.h
 *
 *  Created on: 2015Äê5ÔÂ6ÈÕ
 *      Author: euwyzbc
 */

#ifndef LOCALTIME_H_
#define LOCALTIME_H_
#include <string>
class LocalTime {
public:
  LocalTime();
  virtual ~LocalTime();
  static std::string getCurrentTime();
};

#endif /* LOCALTIME_H_ */
