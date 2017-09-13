/*
 * Trace.h
 *
 *  Created on: 2015Äê4ÔÂ29ÈÕ
 *      Author: euwyzbc
 */

#ifndef TRACE_H_
#define TRACE_H_
#include "LocalTime.h"
#include "Configure_Define.h"
#include "Configure.h"
#include "TraceConsole.h"
#include "TraceFile.h"
#include "TraceBuf.h"
//General TRACE
#define TRACE_ENTER()            TRACE_PRINT(TRACE_LOG_DEBUG3, "")

#define TRACE_ENTER_DEBUG()      TRACE_PRINT(TRACE_LOG_DEBUG3, "")

#define TRACE_DEBUG3(traceStr)   TRACE_PRINT(TRACE_LOG_DEBUG3, traceStr)

#define TRACE_DEBUG(traceStr)    TRACE_PRINT(TRACE_LOG_DEBUG, traceStr)

#define TRACE_NOTICE(traceStr)   TRACE_PRINT(TRACE_LOG_NOTICE, traceStr)

#define TRACE_WARNING(traceStr)  TRACE_PRINT(TRACE_LOG_WARNING, traceStr)

#define TRACE_ERROR(traceStr)    TRACE_PRINT(TRACE_LOG_ERROR, traceStr)

#define TRACE_PRINT(level, traceStr)                                                              \
        do {                                                                            \
            if (::Configure::getInstance().getTraceLogTarget() == TRACE_LOG_TO_CONSOLE)   \
            {                                                                           \
              TRACECONSOLE_PRINT(level, traceStr);                                      \
            }                                                                           \
            else if (::Configure::getInstance().getTraceLogTarget() == TRACE_LOG_TO_FILE) \
            {                                                                           \
              TRACEFILE_PRINT(level, traceStr);                                         \
            }                                                                           \
            else if (::Configure::getInstance().getTraceLogTarget() == TRACE_LOG_BOTH)    \
            {                                                                           \
              TRACECONSOLE_PRINT(level, traceStr);                                      \
              TRACEFILE_PRINT(level, traceStr);                                         \
            }                                                                           \
            else {}                                                                     \
        } while(0)

// TRACEFILE Macro
#define TRACEFILE_PRINT(level, traceStr)                                                \
            do {                                                                        \
              if (TraceFile<level>::getInstance())                                      \
              {                                                                         \
                (*TraceFile<level>::getInstance()) << ::Configure::getInstance().getLogLineNumberInFile() \
                                                   << "  " << LocalTime::getCurrentTime() << "  "       \
                                                   << ": " << className() << "::" << __FUNCTION__ \
                                                   << "**" << ::Configure::getInstance().getTraceLogLevelString() \
                                                   << "**" << ": " << traceStr << std::endl;            \
                ::Configure::getInstance().increaseLogLineNumberInFile();                 \
              }                                                                         \
            }while(0)

//TRACECONSOLE macro
#define TRACECONSOLE_PRINT(level, traceStr)                                    \
            do {                                                               \
              if (TraceConsole<level>::getInstance())                          \
              {                                                                \
                (*TraceConsole<level>::getInstance()) << ::Configure::getInstance().getLogLineNumberInConsole() \
                                                   << "  " << LocalTime::getCurrentTime() << "  "             \
                                                   <<": " << className() << "::" << __FUNCTION__ \
                                                   << "**" << ::Configure::getInstance().getTraceLogLevelString() \
                                                   << "**" << ": " << traceStr << std::endl;            \
                ::Configure::getInstance().increaseLogLineNumberInConsole();     \
              }                                                                \
            }while(0)


//TRACEBUF macro
#define TRACEBUF_PRINT(level, traceStr)                                        \
        do {                                                                   \
          if (TraceBuf<level>::getInstance())                                  \
          {                                                                    \
            (*TraceBuf<level>::getInstance()) << ::Configure::getInstance().getLogLineNumberInConsole() \
                                              << "  " << LocalTime::getCurrentTime() << "  "             \
                                              <<": " << className() << "::" << __FUNCTION__ \
                                              << "**" << ::Configure::getInstance().getTraceLogLevelString() \
                                              << "**" << ": " << traceStr << std::endl;      \
          }                                                                    \
        } while(0)

class TraceManager
{
public:
  static void traceStop()
  {
    TraceFile<TRACE_LOG_DEBUG>::deleteInstance();
    TraceFile<TRACE_LOG_NOTICE>::deleteInstance();
    TraceFile<TRACE_LOG_WARNING>::deleteInstance();
    TraceFile<TRACE_LOG_ERROR>::deleteInstance();

    TraceConsole<TRACE_LOG_DEBUG>::deleteInstance();
    TraceConsole<TRACE_LOG_NOTICE>::deleteInstance();
    TraceConsole<TRACE_LOG_WARNING>::deleteInstance();
    TraceConsole<TRACE_LOG_ERROR>::deleteInstance();

    TraceBuf<TRACE_LOG_DEBUG>::deleteInstance();
    TraceBuf<TRACE_LOG_NOTICE>::deleteInstance();
    TraceBuf<TRACE_LOG_WARNING>::deleteInstance();
    TraceBuf<TRACE_LOG_ERROR>::deleteInstance();
  }
};

#endif /* TRACE_H_ */
