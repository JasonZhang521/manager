/*
 * TraceConsole.h
 *
 *  Created on: 2015Äê4ÔÂ29ÈÕ
 *      Author: euwyzbc
 */

#ifndef TRACECONSOLE_H_
#define TRACECONSOLE_H_

#include <iostream>
#include "Configure_Define.h"
#include "Configure.h"
#include "LocalTime.h"



template<TraceLogLevel level>
class TraceConsole
{
private:
  TraceConsole();
  ~TraceConsole();
public:
  void flush();
public:
  static std::ostream* getInstance();
  static void deleteInstance();
private:
  static std::ostream* traceConsole_;
};

template<TraceLogLevel level>
TraceConsole<level>::TraceConsole()
{
}

template<TraceLogLevel level>
TraceConsole<level>::~TraceConsole()
{
}

template<TraceLogLevel level>
std::ostream* TraceConsole<level>::traceConsole_ = 0;

template<TraceLogLevel level>
std::ostream* TraceConsole<level>::getInstance()
{
  if (Configure::getInstance().getTraceLogLevel() >= level)
  {
    if (traceConsole_ == 0)
    {
      traceConsole_ = &std::cout;
      if (!Configure::getInstance().isConsoleLogStart())
      {
        Configure::getInstance().startConsoleLog();
        *traceConsole_ << "--------------------Log start--------------------" << std::endl;
        *traceConsole_ << "Start Time:" << LocalTime::getCurrentTime() << std::endl;
        *traceConsole_ << "*************************************************" << std::endl;
        *traceConsole_ << "*************************************************" << std::endl;
        *traceConsole_ << "*************************************************" << std::endl;
      }
    }
    return traceConsole_;
  }
  else
  {
    return 0;
  }
}

template<TraceLogLevel level>
void TraceConsole<level>::deleteInstance()
{
  if (traceConsole_)
  {
    if (Configure::getInstance().isConsoleLogStart())
    {
      Configure::getInstance().stopConsoleLog();
      *traceConsole_ << "--------------------Log Stop--------------------" << std::endl;
      *traceConsole_ << "Stop Time:" << LocalTime::getCurrentTime() << std::endl;
      *traceConsole_ << "*************************************************" << std::endl;
      *traceConsole_ << "*************************************************" << std::endl;
      *traceConsole_ << "*************************************************" << std::endl;
    }
    traceConsole_ = 0;
  }
}

#endif /* TRACECONSOLE_H_ */
