/*
 * Configure.h
 *
 *  Created on: 2015��4��23��
 *      Author: euwyzbc
 */

#ifndef CONFIGURE_H_
#define CONFIGURE_H_

#include <string>
#include "Configure_Define.h"
//namespace Common{

class ExceptionConfigure;
class TraceLogConfigure;
class SystemEnvironmentConfigure;

class Configure {
private:
  Configure();
  virtual ~Configure();
private:
  ExceptionConfigure* exceptionConfigure_;
  TraceLogConfigure* traceLogConfigure_;
  SystemEnvironmentConfigure* systemEnvironmentConfigure_;

public:
  /* Exception Configuration */
  void setExceptionFlag(bool usingException);
  bool usingException() const;
  /* Trace Log Configuration */
  void setTraceLogLevel(TraceLogLevel traceLogLevel);
  TraceLogLevel getTraceLogLevel() const;
  std::string getTraceLogLevelString() const;
  void setTraceLogTarget(TraceLogTarget target);
  TraceLogTarget getTraceLogTarget() const;
  void setTraceLogFilePath(const std::string& filePath);
  std::string getTraceLogFilePath() const;
  void setTraceLogBufSize(unsigned int logBufSize);
  unsigned int getTraceLogBufSize() const;
  unsigned short getLogLineNumberInFile() const;
  void increaseLogLineNumberInFile();
  unsigned short getLogLineNumberInConsole() const;
  void increaseLogLineNumberInConsole();
  bool isFileLogStart() const;
  void startFileLog();
  void stopFileLog();
  bool isConsoleLogStart() const;
  void startConsoleLog();
  void stopConsoleLog();
  /* System environment */
  const std::string& getEnvironmentTempPath();
  void setEnvironmentTempPath(const std::string& path);
private:
  static Configure* instance_;
public:
  static Configure& getInstance();
  static void deleteInstance();
};

//}//namespace Common
#endif /* CONFIGURE_H_ */
