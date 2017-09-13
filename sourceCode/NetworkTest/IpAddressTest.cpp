#include "IpAddress.h"
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include "Random.h"
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace Network;
using namespace Serialize;
class IpAddressTest : public ::testing::Test
{
};

static void constructorWithInt(uint32_t address)
{
    uint8_t* p = reinterpret_cast<uint8_t*>(&address);
    std::stringstream ss;
    ss << static_cast<int>(p[3]);
    ss << '.';
    ss << static_cast<int>(p[2]);
    ss << '.';
    ss << static_cast<int>(p[1]);
    ss << '.';
    ss << static_cast<int>(p[0]);
    std::string strIp = ss.str();

    IpAddress ipAddress(address);
    EXPECT_EQ(IPFamilyV4, ipAddress.getIPFamilyType());
    std::string ipToStr = ipAddress.toString();
    EXPECT_EQ(ipToStr, strIp);
}

TEST_F(IpAddressTest, Testing)
{
    Random ran;
    // constructor with uint32_t
    {
        for (uint32_t i = 0; i < 1; ++i)
        {
            uint32_t address = ran.generate32();
            constructorWithInt(address);
        }
    }

    // constructor with string
    {
        IpAddress ipAddressBase(0x01020304);
        IpAddress ipAddress(std::string("1.2.3.4"));
        EXPECT_EQ(ipAddressBase, ipAddress);
    }

    // constructor with SocketInetAddress
    {
        IpAddress ipAddressBase(0x01020304);
		uint32_t ip = 0x01020304;
        SocketInetAddress address;
		memcpy(reinterpret_cast<uint8_t*>(&address), reinterpret_cast<uint8_t*>(&ip), sizeof(uint32_t));
        IpAddress ipAddress(address);
        EXPECT_EQ(ipAddressBase, ipAddress);
    }

    // copy constructor
    {
        IpAddress ipAddress1(0x01020304);
        IpAddress ipAddress2(ipAddress1);
        EXPECT_EQ(ipAddress1, ipAddress2);
    }

    // assigning operator
    {
        IpAddress ipAddress1;
        IpAddress ipAddress2(0x01020304);
        ipAddress1 = ipAddress2;
        EXPECT_EQ(ipAddress1, ipAddress2);
    }

    // comparing
    {
        {
            IpAddress ipAddress1(0x01020305);
            IpAddress ipAddress2(0x01020304);
            EXPECT_TRUE(ipAddress1 > ipAddress2);
            EXPECT_TRUE(ipAddress1 != ipAddress2);
            EXPECT_FALSE(ipAddress1 < ipAddress2);
            EXPECT_FALSE(ipAddress1 == ipAddress2);
        }

        {
            IpAddress ipAddress1(0x01020304);
            IpAddress ipAddress2(0x01020304);
            EXPECT_TRUE(ipAddress1 == ipAddress2);
            EXPECT_FALSE(ipAddress1 != ipAddress2);
            EXPECT_FALSE(ipAddress1 < ipAddress2);
            EXPECT_FALSE(ipAddress1 > ipAddress2);
        }
    }

    // set
    {
        IpAddress ipAddress1(0x01020305);
		uint32_t ip = 0x01020304;
        SocketInetAddress address;
		memcpy(reinterpret_cast<uint8_t*>(&address), reinterpret_cast<uint8_t*>(&ip), sizeof(uint32_t));
        ipAddress1.setAddressIpv4(address);
        IpAddress ipAddress2(0x01020304);
        EXPECT_EQ(ipAddress1, ipAddress2);
    }
}
