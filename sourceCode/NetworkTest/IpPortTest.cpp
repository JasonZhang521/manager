#include "IpPort.h"
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include "Random.h"
#include <string>
#include <sstream>
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace Network;
using namespace Serialize;
class IpPortTest : public ::testing::Test
{

};

static void testIpPortConstructor1(unsigned short port)
{
    IpPort ipPort(port);
    {
        EXPECT_EQ(ipPort.getPort(), port);
    }

    {
        std::stringstream sstr;
        sstr << port;
        std::string strPort;
        sstr >> strPort;
        EXPECT_EQ(ipPort.toString(), strPort);
    }

    {
        WriteBuffer writeBuffer;
        ipPort.serialize(writeBuffer);
        ReadBuffer readBuffer;
        std::copy(static_cast<uint8_t*>(writeBuffer.getBuffer()), 
				  static_cast<uint8_t*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), 
				  static_cast<uint8_t*>(readBuffer.getBuffer()));
        readBuffer.setDataSize(writeBuffer.getDataSize());
        IpPort ipPortRead;
        ipPortRead.unserialize(readBuffer);
        EXPECT_EQ(ipPortRead, ipPort);
    }
}

TEST_F(IpPortTest, Testing)
{
    Random ran;
    // constructor with unsigned short
    {
        testIpPortConstructor1(0xFFFF);
        testIpPortConstructor1(0);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            const unsigned short port = static_cast<unsigned short>(ran.generate16());
            testIpPortConstructor1(port);
        }
    }

    // constructor with string
    {
        IpPort sPort(std::string("2345"));
        IpPort port(2345);
        EXPECT_EQ(sPort, port);
    }

    // copy constructor
    {
        IpPort port1(2345);
        IpPort port2(port1);
        EXPECT_EQ(port1, port2);
    }

    // assigning operator
    {
        IpPort port1;
        IpPort port2(2345);
        port1 = port2;
        EXPECT_EQ(port1, port2);
    }

    // comparing
    {
        IpPort port1(234);
        IpPort port2(234);
        IpPort port3(235);
        EXPECT_TRUE(port1 == port2);
        EXPECT_FALSE(port1 != port2);
        EXPECT_FALSE(port1 == port3);
        EXPECT_TRUE(port2 != port3);
        EXPECT_TRUE(port2 < port3);
        EXPECT_FALSE(port2 > port3);
        EXPECT_TRUE(port3 > port2);
    }

    // set
    {
        IpPort port;
        port.setPort(123);
        EXPECT_EQ(123, port.getPort());
    }
}
