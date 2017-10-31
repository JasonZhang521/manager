#include "Configure.h"
#include "ExceptionConfigure.h"
#include "TraceLogConfigure.h"
#include "SystemEnvironmentConfigure.h"

//namespace Common{

Configure* Configure::instance_ = 0;
Configure::Configure()
 : exceptionConfigure_(new ExceptionConfigure())
 , traceLogConfigure_(new TraceLogConfigure())
 , systemEnvironmentConfigure_(new SystemEnvironmentConfigure())
{
  // TODO Auto-generated constructor stub
}

Configure::~Configure() {
  // TODO Auto-generated destructor stub
  delete exceptionConfigure_;
  delete traceLogConfigure_;
  delete systemEnvironmentConfigure_;
}


void Configure::setExceptionFlag(bool usingException)
{
  exceptionConfigure_->setExceptionFlag(usingException);
}

bool Configure::usingException() const
{
  return exceptionConfigure_->usingException();
}

void Configure::setTraceLogLevel(TraceLogLevel traceLogLevel)
{
  traceLogConfigure_->setTraceLogLevel(traceLogLevel);
}

TraceLogLevel Configure::getTraceLogLevel() const
{
  return traceLogConfigure_->getTraceLogLevel();
}

std::string Configure::getTraceLogLevelString() const
{
  return traceLogConfigure_->getTraceLogLevelString();
}

void Configure::setTraceLogTarget(TraceLogTarget target)
{
  traceLogConfigure_->setTraceLogTarget(target);
}
TraceLogTarget Configure::getTraceLogTarget() const
{
  return traceLogConfigure_->getTraceLogTarget();
}
void Configure::setTraceLogFilePath(const std::string& filePath)
{
  traceLogConfigure_->setTraceLogFilePath(filePath);
}
std::string Configure::getTraceLogFilePath() const
{
  return traceLogConfigure_->getTraceLogFilePath();
}

void Configure::setTraceLogBufSize(unsigned int logBufSize)
{
  traceLogConfigure_->setTraceLogBufSize(logBufSize);
}

unsigned int Configure::getTraceLogBufSize() const
{
  return traceLogConfigure_->getTraceLogBufSize();
}

unsigned short  Configure::getLogLineNumberInFile() const
{
  return traceLogConfigure_->getLogLineNumberInFile();
}
void  Configure::increaseLogLineNumberInFile()
{
  traceLogConfigure_->increaseLogLineNumberInFile();
}

unsigned short Configure::getLogLineNumberInConsole() const
{
  return traceLogConfigure_->getLogLineNumberInConsole();
}

void Configure::increaseLogLineNumberInConsole()
{
  traceLogConfigure_->increaseLogLineNumberInConsole();
}

bool Configure::isFileLogStart() const
{
  return traceLogConfigure_->isFileLogStart();
}
void Configure::startFileLog()
{
  traceLogConfigure_->startFileLog();
}
void Configure::stopFileLog()
{
  traceLogConfigure_->stopFileLog();
}
bool Configure::isConsoleLogStart() const
{
  return traceLogConfigure_->isConsoleLogStart();
}
void Configure::startConsoleLog()
{
  traceLogConfigure_->startConsoleLog();
}
void Configure::stopConsoleLog()
{
  traceLogConfigure_->stopConsoleLog();
}

/* System environment */
const std::string& Configure::getEnvironmentTempPath()
{
    return systemEnvironmentConfigure_->getTempPath();
}

void Configure::setEnvironmentTempPath(const std::string& path)
{
    systemEnvironmentConfigure_->setTempPath(path);
}


Configure& Configure::getInstance()
{
  if (instance_ == 0)
  {
    instance_ = new Configure();
  }

  return *instance_;
}

void Configure::deleteInstance()
{
  delete instance_;
  instance_ = 0;
}

//}//namespace Common
