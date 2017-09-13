// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A sample program demonstrating using Google C++ testing framework.
//
// Author: wan@google.com (Zhanyong Wan)


// In this example, we use a more advanced feature of Google Test called
// test fixture.
//
// A test fixture is a place to hold objects and functions shared by
// all tests in a test case.  Using a test fixture avoids duplicating
// the test code necessary to initialize and cleanup those common
// objects for each test.  It is also useful for defining sub-routines
// that your tests need to invoke a lot.
//
// <TechnicalDetails>
//
// The tests share the test fixture in the sense of code sharing, not
// data sharing.  Each test is given its own fresh copy of the
// fixture.  You cannot expect the data modified by one test to be
// passed on to another test, which is a bad idea.
//
// The reason for this design is that tests should be independent and
// repeatable.  In particular, a test should not fail as the result of
// another test's failure.  If one test depends on info produced by
// another test, then the two tests should really be one big test.
//
// The macros for indicating the success/failure of a test
// (EXPECT_TRUE, FAIL, etc) need to know what the current test is
// (when Google Test prints the test result, it tells you which test
// each failure belongs to).  Technically, these macros invoke a
// member function of the Test class.  Therefore, you cannot use them
// in a global function.  That's why you should put test sub-routines
// in a test fixture.
//
// </TechnicalDetails>

#include "gtest/gtest.h"
#include "Configure_Define.h"
#include "Configure.h"
#include "TraceLogConfigure.h"
#include "ExceptionConfigure.h"

class TraceLogConfigureTest: public testing::Test
{
protected:
  virtual void SetUp()
  {
  }

  TraceLogConfigure traceLogConfig;
};

class ExceptionConfigureTest: public testing::Test
{
protected:
  virtual void SetUp()
  {
  }

  ExceptionConfigure exceptionConfigure;
};

// When you have a test fixture, you define a test using TEST_F
// instead of TEST.
TEST_F(TraceLogConfigureTest, DefaultConstructor) {
  // You can access data in the test fixture here.
  EXPECT_EQ(TRACE_LOG_NOTICE, traceLogConfig.getTraceLogLevel());
  EXPECT_EQ(TRACE_LOG_TO_FILE, traceLogConfig.getTraceLogTarget());
  EXPECT_EQ(TraceLogFilePath, traceLogConfig.getTraceLogFilePath());
  EXPECT_EQ(LogBufSize, traceLogConfig.getTraceLogBufSize());
  EXPECT_EQ((unsigned short)0, traceLogConfig.getLogLineNumberInFile());
  EXPECT_EQ(false, traceLogConfig.isFileLogStart());
  EXPECT_EQ(false, traceLogConfig.isConsoleLogStart());
  traceLogConfig.setTraceLogLevel(TRACE_LOG_ERROR);
  EXPECT_EQ(TRACE_LOG_ERROR, traceLogConfig.getTraceLogLevel());
  traceLogConfig.setTraceLogTarget(TRACE_LOG_BOTH);
  EXPECT_EQ(TRACE_LOG_BOTH, traceLogConfig.getTraceLogTarget());
  traceLogConfig.setTraceLogFilePath("/home/jack/my.log");
  EXPECT_EQ(std::string("/home/jack/my.log"), traceLogConfig.getTraceLogFilePath());
  traceLogConfig.setTraceLogBufSize((unsigned int)10000);
  EXPECT_EQ((unsigned int)10000, traceLogConfig.getTraceLogBufSize());
  traceLogConfig.increaseLogLineNumberInFile();
  EXPECT_EQ((unsigned short)1, traceLogConfig.getLogLineNumberInFile());
  traceLogConfig.startFileLog();
  EXPECT_EQ(true, traceLogConfig.isFileLogStart());
  traceLogConfig.startConsoleLog();
  EXPECT_EQ(true, traceLogConfig.isConsoleLogStart());
}

TEST_F(ExceptionConfigureTest, DefaultConstructor)
{
  EXPECT_EQ(false, exceptionConfigure.usingException());
  exceptionConfigure.setExceptionFlag(true);
  EXPECT_EQ(true, exceptionConfigure.usingException());
}

// Tests the default c'tor.
TEST(Configure, Singleton)
{
  EXPECT_EQ(TRACE_LOG_NOTICE, Configure::getInstance().getTraceLogLevel());
  EXPECT_EQ(TRACE_LOG_TO_FILE, Configure::getInstance().getTraceLogTarget());
  EXPECT_EQ(TraceLogFilePath, Configure::getInstance().getTraceLogFilePath());
  EXPECT_EQ(LogBufSize, Configure::getInstance().getTraceLogBufSize());
  EXPECT_EQ((unsigned short)0, Configure::getInstance().getLogLineNumberInFile());
  EXPECT_EQ((unsigned short)0, Configure::getInstance().getLogLineNumberInConsole());
  EXPECT_EQ(false, Configure::getInstance().isFileLogStart());
  EXPECT_EQ(false, Configure::getInstance().isConsoleLogStart());

  Configure::getInstance().setTraceLogLevel(TRACE_LOG_ERROR);
  EXPECT_EQ(TRACE_LOG_ERROR, Configure::getInstance().getTraceLogLevel());
  Configure::getInstance().setTraceLogTarget(TRACE_LOG_BOTH);
  EXPECT_EQ(TRACE_LOG_BOTH, Configure::getInstance().getTraceLogTarget());
  Configure::getInstance().setTraceLogFilePath("/home/jack/my.log");
  EXPECT_EQ(std::string("/home/jack/my.log"), Configure::getInstance().getTraceLogFilePath());
  Configure::getInstance().setTraceLogBufSize((unsigned int)10000);
  EXPECT_EQ((unsigned int)10000, Configure::getInstance().getTraceLogBufSize());
  Configure::getInstance().increaseLogLineNumberInFile();
  EXPECT_EQ((unsigned short)1, Configure::getInstance().getLogLineNumberInFile());
  Configure::getInstance().increaseLogLineNumberInConsole();
  EXPECT_EQ((unsigned short)1, Configure::getInstance().getLogLineNumberInConsole());
  Configure::getInstance().startFileLog();
  EXPECT_EQ(true, Configure::getInstance().isFileLogStart());
  Configure::getInstance().stopFileLog();
  EXPECT_EQ(false, Configure::getInstance().isFileLogStart());

  Configure::getInstance().startConsoleLog();
  EXPECT_EQ(true, Configure::getInstance().isConsoleLogStart());
  Configure::getInstance().stopConsoleLog();
  EXPECT_EQ(false, Configure::getInstance().isConsoleLogStart());

  EXPECT_EQ(false, Configure::getInstance().usingException());
  Configure::getInstance().setExceptionFlag(true);
  EXPECT_EQ(true, Configure::getInstance().usingException());
}



