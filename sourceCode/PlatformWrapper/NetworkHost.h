#ifndef _IOPLATFORMWRAPPER_NETWORKHOST_H_
#define _IOPLATFORMWRAPPER_NETWORKHOST_H_
#include <stdint.h>
#ifdef WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

namespace PlatformWrapper {

enum ByteOrder
{
    LittleEndian,
    BigEndian
};

ByteOrder CheckByteOrder();

inline unsigned long Htonl(unsigned long hostlong)
{
    return htonl(hostlong);
}

inline unsigned long Ntohl(unsigned long netlong)
{
    return ntohl(netlong);
}

inline unsigned short Htons(unsigned short hostshort)
{
    return htons(hostshort);
}

inline unsigned short Ntohs(unsigned short netshort)
{
    return ntohs(netshort);
}

unsigned long long Ntohll(unsigned long long netllong);
inline unsigned long long Htonll(unsigned long long hostllong)
{
    return Ntohll(hostllong);
}


uint16_t Ntoh16(uint16_t netU16);

inline uint16_t Hton16(uint16_t hostU16)
{
    return Ntoh16(hostU16);
}

uint32_t Ntoh32(uint32_t netU32);

inline uint32_t Hton32(uint32_t hostU32)
{
    return Ntoh32(hostU32);
}

uint64_t Ntoh64(uint64_t netU64);

inline uint64_t Hton64(uint64_t hostU64)
{
    return Ntoh64(hostU64);
}

template <typename T>
T H2N(T val)
{
    if (sizeof(T) == sizeof(uint16_t))
    {
        return static_cast<T>(Hton16(static_cast<uint16_t>(val)));
    }
    else if (sizeof(T) == sizeof(uint32_t))
    {
        return static_cast<T>(Hton32(static_cast<uint32_t>(val)));
    }
    else if (sizeof(T) == sizeof(uint64_t))
    {
        return static_cast<T>(Hton64(static_cast<uint64_t>(val)));
    }
    else
    {
        return val;
    }
}

template <typename T>
T N2H(T val)
{
    if (sizeof(T) == sizeof(uint16_t))
    {
        return static_cast<T>(Ntoh16(static_cast<uint16_t>(val)));
    }
    else if (sizeof(T) == sizeof(uint32_t))
    {
        return static_cast<T>(Ntoh32(static_cast<uint32_t>(val)));
    }
    else if (sizeof(T) == sizeof(uint64_t))
    {
        return static_cast<T>(Ntoh64(static_cast<uint64_t>(val)));
    }
    else
    {
        return val;
    }
}

}


#endif // _IOPLATFORMWRAPPER_NETWORKHOST_H_
