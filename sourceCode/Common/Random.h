#ifndef RANDOM_H
#define RANDOM_H
#include <stdint.h>
#include <string>

class Random
{
public:
    Random();
    uint64_t generate64(uint64_t max = 0xFFFFFFFFFFFFFFFF, uint64_t min = 0);
    uint32_t generate32(uint32_t max = 0xFFFFFFFF, uint32_t min = 0);
    uint16_t generate16(uint16_t max = 0xFFFF, uint16_t min = 0);
    uint8_t generate8(uint8_t max = 0xFF, uint8_t min = 0);
    std::string generateString(uint16_t len);
    std::string generateUpLetterString(uint16_t len);
};

#endif // RANDOM_H
