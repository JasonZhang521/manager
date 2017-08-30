/*
 * TraceFile.h
 *
 *  Created on: 2015Äê4ÔÂ29ÈÕ
 *      Author: euwyzbc
 */

#ifndef TRACEFILE_H_
#define TRACEFILE_H_

#include <fstream>
#include "Configure_Define.h"
#include "Configure.h"
#include "LocalTime.h"

template <TraceLogLevel level>
class TraceFile
{
private:
  TraceFile();
  ~TraceFile();
public:
  static std::ofstream* getInstance();
  static void deleteInstance();
private:
  static std::ofstream* traceFile_;
};

template <TraceLogLevel level>
TraceFile<level>::TraceFile()
{}

template <TraceLogLevel level>
TraceFile<level>::~TraceFile()
{}


template <TraceLogLevel level>
std::ofstream* TraceFile<level>::traceFile_ = 0;

template <TraceLogLevel level>
std::ofstream* TraceFile<level>::getInstance()
{
  if (Configure::getInstance().getTraceLogLevel() >= level)
  {
    if (traceFile_ == 0)
    {
      traceFile_ = new std::ofstream(Configure::getInstance().getTraceLogFilePath().c_str(), std::ofstream::app);
      if (!Configure::getInstance().isFileLogStart())
      {
        Configure::getInstance().startFileLog();
        *traceFile_ << "--------------------Log start--------------------" << std::endl;
        *traceFile_ << "Start Time:" << LocalTime::getCurrentTime() << std::endl;
        *traceFile_ << "*************************************************" << std::endl;
        *traceFile_ << "*************************************************" << std::endl;
        *traceFile_ << "*************************************************" << std::endl;
      }
    }
    return traceFile_;
  }
  else
  {
    return 0;
  }
}

template <TraceLogLevel level>
void TraceFile<level>::deleteInstance()
{
  if (traceFile_ != 0)
  {
    if (Configure::getInstance().isFileLogStart())
    {
      Configure::getInstance().stopFileLog();
      *traceFile_ << "--------------------Log Sop--------------------" << std::endl;
      *traceFile_ << "Stop Time:" << LocalTime::getCurrentTime() << std::endl;
      *traceFile_ << "*************************************************" << std::endl;
      *traceFile_ << "*************************************************" << std::endl;
      *traceFile_ << "*************************************************" << std::endl;
    }
    delete traceFile_;
    traceFile_ = 0;
  }
}

#endif /* TRACEFILE_H_ */
