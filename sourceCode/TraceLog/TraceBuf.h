/*
 * TraceLog.h
 *
 *  Created on: 2015Äê4ÔÂ24ÈÕ
 *      Author: euwyzbc
 */

#ifndef TRACEBUF_H_
#define TRACEBUF_H_

#include <sstream>
#include "Configure.h"
#include "Configure_Define.h"
#include "TraceConsole.h"
#include "TraceBuf.h"

template<TraceLogLevel level>
class TraceBuf: public std::stringstream
{
private:
  TraceBuf();
  ~TraceBuf();
public:
  void writeBuf();
public:
  static TraceBuf<level>* getInstance();
  static void deleteInstance();
private:
  static TraceBuf<level>* traceBuf_;
};

template<TraceLogLevel level>
TraceBuf<level>* TraceBuf<level>::traceBuf_ = 0;

template<TraceLogLevel level>
void TraceBuf<level>::writeBuf()
{
  if (this->str().size() > Configure::getInstance().getTraceLogBufSize())
  {
    if (Configure::getInstance().getTraceLogTarget() == TRACE_LOG_TO_CONSOLE)
    {
      if (TraceConsole<level>::getInstance())
      {
        (*TraceConsole<level>::getInstance()) << this->str();
      }
    }
    else if (Configure::getInstance().getTraceLogTarget() == TRACE_LOG_TO_FILE)
    {
      if (TraceBuf<level>::getInstance())
      {
        (*TraceBuf<level>::getInstance()) << this->str();
      }
    }
    else if (Configure::getInstance().getTraceLogTarget() == TRACE_LOG_BOTH)
    {
      if (TraceConsole<level>::getInstance())
      {
        (*TraceConsole<level>::getInstance()) << this->str();
      }
      if (TraceBuf<level>::getInstance())
      {
        (*TraceBuf<level>::getInstance()) << this->str();
      }
    }

    this->str("");
  }

}
template<TraceLogLevel level>
TraceBuf<level>::TraceBuf()
{}

template<TraceLogLevel level>
TraceBuf<level>::~TraceBuf()
{}



template<TraceLogLevel level>
TraceBuf<level>* TraceBuf<level>::getInstance()
{
  if (Configure::getInstance().getTraceLogLevel() >= level)
  {
    if (traceBuf_ == 0)
    {
      traceBuf_ = new TraceBuf<level>();
    }
    return traceBuf_;
  }
  else
  {
    return 0;
  }
}

template<TraceLogLevel level>
void TraceBuf<level>::deleteInstance()
{
  if (traceBuf_ != 0)
  {
    traceBuf_->writeBuf();
    delete traceBuf_;
    traceBuf_ = 0;
  }
}


#endif /* TRACEBUF_H_ */
