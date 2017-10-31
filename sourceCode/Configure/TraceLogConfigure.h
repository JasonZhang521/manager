#ifndef TRACELOGCONFIGURE_H_
#define TRACELOGCONFIGURE_H_

#include <string>
#include "Configure_Define.h"

class TraceLogConfigure {
public:
  TraceLogConfigure();
  virtual ~TraceLogConfigure();
  void setTraceLogLevel(TraceLogLevel traceLogLevel);
  TraceLogLevel getTraceLogLevel() const;
  void setTraceLogTarget(TraceLogTarget target);
  TraceLogTarget getTraceLogTarget() const;
  std::string getTraceLogLevelString() const;
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
private:
  TraceLogLevel level_;
  TraceLogTarget target_;
  std::string filePath_;
  unsigned int logBufSize_;
  unsigned short logLineNumberInFile_;
  unsigned short logLineNumberInConsole_;
  bool fileLogStart_;
  bool consoleLogStart_;
};

#endif /* TRACELOGCONFIGURE_H_ */
