#include "Random.h"
#include <stdlib.h>
#include<time.h>

Random::Random()
{
    srand((int)time(0));
}

uint64_t Random::generate64(uint64_t max, uint64_t min)
{
    uint64_t val1 = 0x0000000000007FFF & rand();
    uint64_t val2 = 0x0000000000007FFF & rand();
    uint64_t val3 = 0x0000000000007FFF & rand();
    uint64_t val4 = 0x0000000000007FFF & rand();
    uint64_t val5 = rand() % 16;
    uint64_t val = (val1 | val2 << 15 | val3 << 30 | val4 << 45 | val5 << 60);
    uint64_t interval = max - min;
    return val % interval + min;
}

uint32_t Random::generate32(uint32_t max, uint32_t min)
{
    uint32_t val1 = 0x00007FFF & rand();
    uint32_t val2 = 0x00007FFF & rand();
    uint32_t val3 = rand() % 4;
    uint32_t val = (val1 | val2 << 15 | val3 << 30);
    uint32_t interval = max - min;
    return val % interval + min;
}

uint16_t Random::generate16(uint16_t max, uint16_t min)
{
    uint16_t val1 = rand();
    uint16_t val2 = rand() % 2;
    uint32_t val = (val1 | val2 << 15);
    uint32_t interval = max - min;
    return val % interval + min;
}

uint8_t Random::generate8(uint8_t max, uint8_t min)
{
    uint16_t val = rand();
    uint32_t interval = max - min;
    return val % interval + min;
}

std::string Random::generateString(uint16_t len)
{
    std::string str;
    str.reserve(len);
    for (uint16_t i = 0; i < len; ++i)
    {
        str.push_back(static_cast<char>(generate8(255, 1)));
    }
    return str;
}

std::string Random::generateUpLetterString(uint16_t len)
{
    std::string str;
    str.reserve(len);
    for (uint16_t i = 0; i < len; ++i)
    {
        str.push_back(static_cast<char>(generate8('Z', 'A')));
    }
    return str;
}
