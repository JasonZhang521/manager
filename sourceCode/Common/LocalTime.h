/*
 * LocalTime.h
 *
 *  Created on: 2015��5��6��
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
