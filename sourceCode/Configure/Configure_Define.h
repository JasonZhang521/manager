#ifndef CONFIGURE_DEFINE_H_
#define CONFIGURE_DEFINE_H_

enum TraceLogLevel
{
  TRACE_LOG_ERROR,
  TRACE_LOG_WARNING,
  TRACE_LOG_NOTICE,
  TRACE_LOG_DEBUG,
  TRACE_LOG_DEBUG3
};

enum TraceLogTarget
{
  TRACE_LOG_TO_CONSOLE,
  TRACE_LOG_TO_FILE,
  TRACE_LOG_BOTH
};

#define TraceLogFilePath  ("/opt/HongClusterMgt/log/message.log")
#define SystemTempDir ("/opt/HongClusterMgt/temp")

#define LogBufSize (1024 * 1024)

#endif /* CONFIGURE_DEFINE_H_ */
