#include "NetworkHost.h"

namespace PlatformWrapper {

ByteOrder CheckByteOrder()
{
    if (htons((short)1) == 1)
    {
        return BigEndian;
    }
    else
    {
        return LittleEndian;
    }
}

unsigned long long Ntohll(unsigned long long netllong)
{
    if (CheckByteOrder() == BigEndian)
    {
        return netllong;
    }
    else
    {
       return (unsigned long long)ntohl((unsigned long)(netllong >> 32)) |
       (((unsigned long long)ntohl((unsigned long)(netllong & 0xFFFFFFFF))) << 32);
    }
}

uint16_t Ntoh16(uint16_t netU16)
{
    if (CheckByteOrder() == BigEndian)
    {
        return netU16;
    }
    else
    {
       return ((netU16 >> 8) | (netU16 & 0x00FF) << 8);
    }
}

uint32_t Ntoh32(uint32_t netU32)
{
    if (CheckByteOrder() == BigEndian)
    {
        return netU32;
    }
    else
    {
       return  (uint32_t)Ntoh16((uint16_t)(netU32 >> 16)) |
               ((uint32_t)Ntoh16((uint16_t)(netU32 & 0xFFFF)) << 16);
    }
}

uint64_t Ntoh64(uint64_t netU64)
{
    if (CheckByteOrder() == BigEndian)
    {
        return netU64;
    }
    else
    {
       return (uint64_t)Ntoh32((uint32_t)(netU64 >> 32)) |
              ((uint64_t)Ntoh32((uint32_t)(netU64 & 0xFFFFFFFF)) << 32);
    }
}

}
