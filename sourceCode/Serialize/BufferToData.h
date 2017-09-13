#ifndef _SERIALIZE_BUFFERTODATA_H_
#define _SERIALIZE_BUFFERTODATA_H_
#include <string.h>
namespace Serialize {

class BufferToData
{
public:
    template <typename T>
    static inline T Read(void* buffer)
    {
        return *(reinterpret_cast<T*>(buffer));
    }

    static inline void Read(void* buffer, void* newBuffer, unsigned int readSize)
    {
        memcpy(newBuffer, buffer, readSize);
    }
};

}

#endif // _SERIALIZE_BUFFERTODATA_H_
