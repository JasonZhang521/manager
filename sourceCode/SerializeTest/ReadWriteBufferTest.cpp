#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "ReadBuffer.h"
#include "WriteBuffer.h"
#include "Random.h"

class ReadWriteBufferTest : public ::testing::Test
{

};

template <typename T>
static void TestHelp(const std::vector<T>& vVal)
{
    Serialize::WriteBuffer writeBuffer;
    Serialize::ReadBuffer readBuffer;

    for (typename std::vector<T>::const_iterator it = vVal.begin(); it != vVal.end(); ++it)
    {
        writeBuffer.write(*it);
    }
    std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer.getBuffer()));
    readBuffer.setDataSize(writeBuffer.getDataSize());

    T readVal;
    for (typename std::vector<T>::const_iterator it = vVal.begin(); it != vVal.end(); ++it)
    {
        const T& val = *it;
        readBuffer.read(readVal);
        ASSERT_EQ(val, readVal);
    }

    ASSERT_TRUE(readBuffer.isEndOfData());
}

TEST_F(ReadWriteBufferTest, TestSameType)
{
    {
        Random ran;
        using TestType = uint8_t;
        std::vector<TestType> vec;
        vec.push_back(0);
        vec.push_back(0xFF);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            vec.push_back(static_cast<TestType>(ran.generate8()));
        }
        TestHelp<TestType>(vec);
    }

    {
        Random ran;
        using TestType = int8_t;
        std::vector<TestType> vec;
        vec.push_back(0);
        vec.push_back(0x80);
        vec.push_back(0x7F);
        vec.push_back(0xFF);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            vec.push_back(static_cast<TestType>(ran.generate8()));
        }
        TestHelp<TestType>(vec);
    }

    {
        Random ran;
        using TestType = uint16_t;
        std::vector<TestType> vec;
        vec.push_back(0);
        vec.push_back(0xFFFF);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            vec.push_back(static_cast<TestType>(ran.generate16()));
        }
        TestHelp<TestType>(vec);
    }

    {
        Random ran;
        using TestType = int16_t;
        std::vector<TestType> vec;
        vec.push_back(0);
        vec.push_back(0x8000);
        vec.push_back(0x7FFF);
        vec.push_back(0xFFFF);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            vec.push_back(static_cast<TestType>(ran.generate16()));
        }
        TestHelp<TestType>(vec);
    }

    {
        Random ran;
        using TestType = uint32_t;
        std::vector<TestType> vec;
        vec.push_back(0);
        vec.push_back(0xFFFFFFFF);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            vec.push_back(static_cast<TestType>(ran.generate32()));
        }
        TestHelp<TestType>(vec);
    }

    {
        Random ran;
        using TestType = int32_t;
        std::vector<TestType> vec;
        vec.push_back(0);
        vec.push_back(0x8000000);
        vec.push_back(0x7FFFFFFF);
        vec.push_back(0xFFFFFFFF);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            vec.push_back(static_cast<TestType>(ran.generate32()));
        }
        TestHelp<TestType>(vec);
    }

    {
        Random ran;
        using TestType = uint64_t;
        std::vector<TestType> vec;
        vec.push_back(0);
        vec.push_back(0xFFFFFFFFFFFFFFFF);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            vec.push_back(static_cast<TestType>(ran.generate64()));
        }
        TestHelp<TestType>(vec);
    }

    {
        Random ran;
        using TestType = int64_t;
        std::vector<TestType> vec;
        vec.push_back(0);
        vec.push_back(0x8000000000000000);
        vec.push_back(0x7FFFFFFFFFFFFFFF);
        vec.push_back(0xFFFFFFFFFFFFFFFF);
        for (unsigned int i = 0; i < 1000; ++i)
        {
            vec.push_back(static_cast<TestType>(ran.generate64()));
        }
        TestHelp<TestType>(vec);
    }
}

TEST_F(ReadWriteBufferTest, TestString)
{
    Random ran;
    std::vector<std::string> vec;
    for (unsigned int i = 0; i < 1000; ++i)
    {
        const std::string str= ran.generateString(ran.generate16(100, 1));
        vec.push_back(str);
    }

    Serialize::WriteBuffer writeBuffer;
    Serialize::ReadBuffer readBuffer;

    for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        const std::string& str = *it;
        uint16_t len = str.size();
        writeBuffer.write(len);
        writeBuffer.write(str.c_str(), len);
    }
    std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer.getBuffer()));
    readBuffer.setDataSize(writeBuffer.getDataSize());

    for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        const std::string& str = *it;
        uint16_t len = 0;
        readBuffer.read(len);
        ASSERT_EQ(len, str.size());
        char buffer[1024];
        readBuffer.read(buffer, len);
        const std::string readStr(buffer, len);
        ASSERT_EQ(readStr, str);
    }
}

TEST_F(ReadWriteBufferTest, TestCombination)
{
    std::string str1("abcde");
    int8_t int8Val = -15;
    uint64_t uint64Val = 123456577;
    std::string str2("dddddddddddd");
    uint8_t uint8Val = 24;
    int32_t int32Val = -2346;
    int64_t int64Val = 899993343;
    short shortVal = 23456;
    std::string str3("ccccccccccccccccc");
    bool isTrue = true;

    Serialize::WriteBuffer writeBuffer;
    writeBuffer.write<uint16_t>(str1.length());
    writeBuffer.write(str1.c_str(), str1.length());
    writeBuffer.write(int8Val);
    writeBuffer.write(uint64Val);
    writeBuffer.write<uint16_t>(str2.length());
    writeBuffer.write(str2.c_str(), str2.length());
    writeBuffer.write(uint8Val);
    writeBuffer.write(int32Val);
    writeBuffer.write(int64Val);
    writeBuffer.write(shortVal);
    writeBuffer.write<uint16_t>(str3.length());
    writeBuffer.write(str3.c_str(), str3.length());
    writeBuffer.write(isTrue);

    Serialize::ReadBuffer readBuffer;
    std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer.getBuffer()));
    readBuffer.setDataSize(writeBuffer.getDataSize());

    char buffer[256];
    uint16_t len = 0;

    readBuffer.read(len);
    ASSERT_EQ(len, str1.size());
    readBuffer.read(buffer, len);
    std::string readStr1(buffer, len);
    ASSERT_EQ(readStr1, str1);
    int8_t readInt8Val = 0;
    readBuffer.read(readInt8Val);
    ASSERT_EQ(readInt8Val, int8Val);
    uint64_t readUint64Val = 0;
    readBuffer.read(readUint64Val);
    ASSERT_EQ(readUint64Val, uint64Val);

    readBuffer.read(len);
    ASSERT_EQ(len, str2.size());
    readBuffer.read(buffer, len);
    std::string readStr2(buffer, len);
    ASSERT_EQ(readStr2, str2);

    int8_t readuUint8Val = 0;
    readBuffer.read(readuUint8Val);
    ASSERT_EQ(readuUint8Val, uint8Val);
    int32_t readint32Val = 0;
    readBuffer.read(readint32Val);
    ASSERT_EQ(readint32Val, int32Val);
    int64_t readint64Val = 0;
    readBuffer.read(readint64Val);
    ASSERT_EQ(readint64Val, int64Val);
    short readShortVal = 0;
    readBuffer.read(readShortVal);
    ASSERT_EQ(readShortVal, shortVal);

    readBuffer.read(len);
    ASSERT_EQ(len, str3.size());
    readBuffer.read(buffer, len);
    std::string readStr3(buffer, len);
    ASSERT_EQ(readStr3, str3);

    bool readBool = false;
    readBuffer.read(readBool);
    ASSERT_EQ(readBool, isTrue);
}

TEST_F(ReadWriteBufferTest, WriteBufferSwap)
{
    Serialize::WriteBuffer writeBuffer1(10);
    Serialize::WriteBuffer writeBuffer2(20);
    writeBuffer1.write<int>(5);
    writeBuffer2.write<int>(6);
    writeBuffer2.write<int>(7);

    Serialize::WriteBuffer writeBuffer3(10);
    Serialize::WriteBuffer writeBuffer4(20);
    writeBuffer3.write<int>(5);
    writeBuffer4.write<int>(6);
    writeBuffer4.write<int>(7);

    writeBuffer3.swap(writeBuffer4);

    EXPECT_FALSE((writeBuffer3 == writeBuffer1));
    EXPECT_FALSE((writeBuffer4 == writeBuffer2));
    EXPECT_TRUE((writeBuffer3 == writeBuffer2));
    EXPECT_TRUE((writeBuffer4 == writeBuffer1));
}

TEST_F(ReadWriteBufferTest, ReadBufferSwap)
{
    Serialize::ReadBuffer readBuffer1(10);
    readBuffer1.setDataSize(8);
    for (unsigned int i = 0; i < 8; ++i)
    {
        *(reinterpret_cast<char*>(readBuffer1.getBuffer()) + i) = static_cast<char>(i);
    }
    Serialize::ReadBuffer readBuffer2(20);
    readBuffer2.setDataSize(18);
    for (unsigned int i = 0; i < 18; ++i)
    {
        *(reinterpret_cast<char*>(readBuffer2.getBuffer()) + i) = static_cast<char>(2 * i);
    }

    Serialize::ReadBuffer readBuffer3(10);
    readBuffer3.setDataSize(8);
    for (unsigned int i = 0; i < 8; ++i)
    {
        *(reinterpret_cast<char*>(readBuffer3.getBuffer()) + i) = static_cast<char>(i);
    }

    Serialize::ReadBuffer readBuffer4(20);
    readBuffer4.setDataSize(18);
    for (unsigned int i = 0; i < 18; ++i)
    {
        *(reinterpret_cast<char*>(readBuffer4.getBuffer()) + i) = static_cast<char>(2 * i);
    }

    readBuffer3.swap(readBuffer4);

    EXPECT_FALSE((readBuffer3 == readBuffer1));
    EXPECT_FALSE((readBuffer4 == readBuffer2));
    EXPECT_TRUE((readBuffer3 == readBuffer2));
    EXPECT_TRUE((readBuffer4 == readBuffer1));
}

TEST_F(ReadWriteBufferTest, TestReadWriteString)
{
    Random ran;
    std::vector<std::string> vec1;
    for (unsigned int i = 0; i < 1000; ++i)
    {
        const std::string str= ran.generateString(ran.generate16(100, 1));
        vec1.push_back(str);
    }

    Serialize::WriteBuffer writeBuffer;
    Serialize::ReadBuffer readBuffer;

    writeBuffer.write(vec1);
    std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer.getBuffer()));
    readBuffer.setDataSize(writeBuffer.getDataSize());

    std::vector<std::string> vec2;
    readBuffer.read(vec2);
    ASSERT_EQ(vec1, vec2);
}

TEST_F(ReadWriteBufferTest, TestReadBufferExpand)
{
    Serialize::WriteBuffer writeBuffer;
    writeBuffer.write(static_cast<int>(6));
    writeBuffer.write(static_cast<short>(6));

    Serialize::ReadBuffer readBuffer1;
    Serialize::ReadBuffer readBuffer2;
    std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer1.getBuffer()));
    readBuffer1.setDataSize(writeBuffer.getDataSize());
    std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer2.getBuffer()));
    readBuffer2.setDataSize(writeBuffer.getDataSize());

    readBuffer2.expand(6);
    ASSERT_EQ(readBuffer1.getBufferSize() + 6, readBuffer2.getBufferSize());
    ASSERT_EQ(readBuffer1.getDataSize(), readBuffer2.getDataSize());
    int v = 0;
    readBuffer2.read(v);
    ASSERT_EQ(6, v);

    short vs = 0;
    readBuffer2.read(vs);
    ASSERT_EQ(6, vs);
}

TEST_F(ReadWriteBufferTest, TestReadBufferRemoveReadedData)
{
    Serialize::WriteBuffer writeBuffer;
    writeBuffer.write(static_cast<int>(6));
    writeBuffer.write(static_cast<short>(6));

    Serialize::ReadBuffer readBuffer1;
    Serialize::ReadBuffer readBuffer2;
    std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer1.getBuffer()));
    readBuffer1.setDataSize(writeBuffer.getDataSize());
    std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer2.getBuffer()));
    readBuffer2.setDataSize(writeBuffer.getDataSize());

    ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
    ASSERT_EQ(readBuffer1.getDataSize(), readBuffer2.getDataSize());
    int v = 0;
    readBuffer2.read(v);
    ASSERT_EQ(6, v);
    readBuffer2.removeReadedData();
    ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
    ASSERT_EQ(readBuffer1.getDataSize() - sizeof(int), readBuffer2.getDataSize());

    short vs = 0;
    readBuffer2.read(vs);
    ASSERT_EQ(6, vs);
    ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
    ASSERT_EQ(readBuffer1.getDataSize() - sizeof(int), readBuffer2.getDataSize());

    readBuffer2.removeReadedData();
    ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
    ASSERT_EQ(0, readBuffer2.getDataSize());
}

TEST_F(ReadWriteBufferTest, TestReadBufferConcatenate)
{
    {
        Serialize::WriteBuffer writeBuffer;
        writeBuffer.write(static_cast<int>(6));
        writeBuffer.write(static_cast<short>(60));

        Serialize::ReadBuffer readBuffer1;
        Serialize::ReadBuffer readBuffer2;
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer1.getBuffer()));
        readBuffer1.setDataSize(writeBuffer.getDataSize());
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer2.getBuffer()));
        readBuffer2.setDataSize(writeBuffer.getDataSize());

        ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
        ASSERT_EQ(readBuffer1.getDataSize(), readBuffer2.getDataSize());

        int vi = 0;
        short vs = 0;
        readBuffer1.concatenate(readBuffer2);
        ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
        ASSERT_EQ(readBuffer1.getDataSize(), 2*(sizeof(int) + sizeof(short)));

        readBuffer1.read(vi);
        readBuffer1.read(vs);
        ASSERT_EQ(6, vi);
        ASSERT_EQ(60, vs);
        ASSERT_TRUE(readBuffer1.read(vi));
        ASSERT_TRUE(readBuffer1.read(vs));
        ASSERT_EQ(6, vi);
        ASSERT_EQ(60, vs);
    }

    {
        Serialize::WriteBuffer writeBuffer;
        writeBuffer.write(static_cast<int>(6));
        writeBuffer.write(static_cast<short>(60));

        Serialize::ReadBuffer readBuffer1;
        Serialize::ReadBuffer readBuffer2;
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer1.getBuffer()));
        readBuffer1.setDataSize(writeBuffer.getDataSize());
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer2.getBuffer()));
        readBuffer2.setDataSize(writeBuffer.getDataSize());

        ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
        ASSERT_EQ(readBuffer1.getDataSize(), readBuffer2.getDataSize());

        int vi = 0;
        short vs = 0;

        readBuffer1.read(vi);

        readBuffer1.concatenate(readBuffer2);
        ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
        ASSERT_EQ(readBuffer1.getDataSize(), 2 * (sizeof(int) + sizeof(short)));

        readBuffer1.read(vs);
        ASSERT_EQ(60, vs);
        ASSERT_TRUE(readBuffer1.read(vi));
        ASSERT_TRUE(readBuffer1.read(vs));
        ASSERT_EQ(6, vi);
        ASSERT_EQ(60, vs);
    }

    {
        Serialize::WriteBuffer writeBuffer;
        writeBuffer.write(static_cast<int>(6));
        writeBuffer.write(static_cast<short>(60));

        Serialize::ReadBuffer readBuffer1;
        Serialize::ReadBuffer readBuffer2;
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer1.getBuffer()));
        readBuffer1.setDataSize(writeBuffer.getDataSize());
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer2.getBuffer()));
        readBuffer2.setDataSize(writeBuffer.getDataSize());

        ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
        ASSERT_EQ(readBuffer1.getDataSize(), readBuffer2.getDataSize());

        int vi = 0;
        short vs = 0;

        readBuffer2.read(vi);
        ASSERT_EQ(6, vi);

        readBuffer1.concatenate(readBuffer2);
        ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
        ASSERT_EQ(readBuffer1.getDataSize(), 2*(sizeof(int) + sizeof(short)));

        readBuffer1.read(vi);
        readBuffer1.read(vs);
        ASSERT_EQ(6, vi);
        ASSERT_EQ(60, vs);
        ASSERT_TRUE(readBuffer1.read(vs));
        ASSERT_EQ(60, vs);
    }

    {
        Serialize::WriteBuffer writeBuffer;
        writeBuffer.write(static_cast<int>(6));
        writeBuffer.write(static_cast<short>(60));

        Serialize::ReadBuffer readBuffer1;
        Serialize::ReadBuffer readBuffer2;
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer1.getBuffer()));
        readBuffer1.setDataSize(writeBuffer.getDataSize());
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer2.getBuffer()));
        readBuffer2.setDataSize(writeBuffer.getDataSize());

        ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
        ASSERT_EQ(readBuffer1.getDataSize(), readBuffer2.getDataSize());

        int vi = 0;
        short vs = 0;
        readBuffer1.read(vi);
        ASSERT_EQ(6, vi);
        readBuffer2.read(vi);
        ASSERT_EQ(6, vi);

        readBuffer1.concatenate(readBuffer2);
        ASSERT_EQ(readBuffer1.getBufferSize(), readBuffer2.getBufferSize());
        ASSERT_EQ(readBuffer1.getDataSize(), 2*(sizeof(int) + sizeof(short)));

        ASSERT_TRUE(readBuffer1.read(vs));
        ASSERT_EQ(60, vs);
        ASSERT_TRUE(readBuffer1.read(vs));
        ASSERT_EQ(60, vs);
    }

    {
        Serialize::WriteBuffer writeBuffer;
        writeBuffer.write(static_cast<int>(6));
        writeBuffer.write(static_cast<short>(60));

        Serialize::ReadBuffer readBuffer1(8);
        Serialize::ReadBuffer readBuffer2;
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer1.getBuffer()));
        readBuffer1.setDataSize(writeBuffer.getDataSize());
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer2.getBuffer()));
        readBuffer2.setDataSize(writeBuffer.getDataSize());

        int vi = 0;
        short vs = 0;
        readBuffer1.concatenate(readBuffer2);
        ASSERT_EQ(readBuffer1.getBufferSize(), 2*(sizeof(int) + sizeof(short)));
        ASSERT_EQ(readBuffer1.getDataSize(), 2*(sizeof(int) + sizeof(short)));

        readBuffer1.read(vi);
        readBuffer1.read(vs);
        ASSERT_EQ(6, vi);
        ASSERT_EQ(60, vs);
        ASSERT_TRUE(readBuffer1.read(vi));
        ASSERT_TRUE(readBuffer1.read(vs));
        ASSERT_EQ(6, vi);
        ASSERT_EQ(60, vs);
    }

    {
        Serialize::WriteBuffer writeBuffer;
        writeBuffer.write(static_cast<int>(6));
        writeBuffer.write(static_cast<short>(60));

        Serialize::ReadBuffer readBuffer1(8);
        Serialize::ReadBuffer readBuffer2;
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer1.getBuffer()));
        readBuffer1.setDataSize(writeBuffer.getDataSize());
        std::copy(reinterpret_cast<char*>(writeBuffer.getBuffer()), reinterpret_cast<char*>(writeBuffer.getBuffer()) + writeBuffer.getDataSize(), reinterpret_cast<char*>(readBuffer2.getBuffer()));
        readBuffer2.setDataSize(writeBuffer.getDataSize());

        int vi = 0;
        short vs = 0;
        readBuffer1.read(vi);
        ASSERT_EQ(6, vi);

        readBuffer1.concatenate(readBuffer2);

        ASSERT_EQ(readBuffer1.getBufferSize(), (sizeof(int) + 2*sizeof(short)));
        ASSERT_EQ(readBuffer1.getDataSize(), (sizeof(int) + 2*sizeof(short)));

        readBuffer1.read(vs);
        ASSERT_EQ(60, vs);
        ASSERT_TRUE(readBuffer1.read(vi));
        ASSERT_TRUE(readBuffer1.read(vs));
        ASSERT_EQ(6, vi);
        ASSERT_EQ(60, vs);
    }
}
