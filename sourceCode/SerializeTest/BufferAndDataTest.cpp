#include <string>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "BufferToData.h"
#include "DataToBuffer.h"
#include "Random.h"

class BufferAndDataTest : public ::testing::Test
{

};

template<typename T>
static void test(const T& val)
{
   char buffer[256] = {0};
   // std::cout << "val = " << val << std::endl;
   Serialize::DataToBuffer::Write<T>(buffer, val);
   T readVal = Serialize::BufferToData::Read<T>(buffer);
   ASSERT_EQ(readVal, val);
}

static void testStr(const std::string& str)
{
    char buffer[256] = {0};
    Serialize::DataToBuffer::Write(buffer, str.c_str(), str.size());
    char newBuffer[256] = {0};
    Serialize::BufferToData::Read(buffer, newBuffer, str.size());
    std::string readStr(newBuffer, str.size());
    ASSERT_EQ(readStr, str);
}

TEST_F(BufferAndDataTest, TestU8)
{
    Random ran;
    test<uint8_t>(0);
    test<uint8_t>(255);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        test<uint8_t>(ran.generate8());
    }
}

TEST_F(BufferAndDataTest, Test8)
{
    Random ran;
    test<int8_t>(0);
    test<int8_t>(0xFF);
    test<int8_t>(0x7F);
    test<int8_t>(0x80);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        test<int8_t>(ran.generate8());
    }
}

TEST_F(BufferAndDataTest, TestU16)
{
    Random ran;
    test<uint16_t>(0);
    test<uint16_t>(0xFFFF);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        test<uint16_t>(ran.generate16());
    }
}

TEST_F(BufferAndDataTest, Test16)
{
    Random ran;
    test<int16_t>(0);
    test<int16_t>(0xFFFF);
    test<int16_t>(0x7FFF);
    test<int16_t>(0x8000);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        test<int16_t>(ran.generate16());
    }
}

TEST_F(BufferAndDataTest, TestU32)
{
    Random ran;
    test<uint32_t>(0);
    test<uint32_t>(0xFFFFFFFF);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        test<uint32_t>(ran.generate32());
    }
}

TEST_F(BufferAndDataTest, Test32)
{
    Random ran;
    test<int32_t>(0);
    test<int32_t>(0xFFFFFFFF);
    test<int32_t>(0x7FFFFFFF);
    test<int32_t>(0x80000000);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        test<int32_t>(ran.generate32());
    }
}

TEST_F(BufferAndDataTest, TestU64)
{
    Random ran;
    test<uint64_t>(0);
    test<uint64_t>(0xFFFFFFFFFFFFFFFF);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        test<uint64_t>(ran.generate64());
    }
}

TEST_F(BufferAndDataTest, Test64)
{
    Random ran;
    test<int64_t>(0);
    test<int64_t>(0xFFFFFFFFFFFFFFFF);
    test<int64_t>(0x7FFFFFFFFFFFFFFF);
    test<int64_t>(0x8000000000000000);
    for (unsigned int i = 0; i < 1000; ++i)
    {
        test<int64_t>(ran.generate64());
    }
}

TEST_F(BufferAndDataTest, TestBool)
{
    test<bool>(true);
    test<bool>(false);
}

TEST_F(BufferAndDataTest, TestString)
{
    testStr("");
    testStr("hello world");
    testStr("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}

