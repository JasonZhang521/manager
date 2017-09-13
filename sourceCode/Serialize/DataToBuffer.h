#ifndef _SERIALIZE_DATATOBUFFER_H_
#define _SERIALIZE_DATATOBUFFER_H_
#include <string.h>
namespace Serialize {

class DataToBuffer
{
public:
    DataToBuffer();
    template <typename T>
    static inline void Write(void* buffer, const T& val)
    {
        *(reinterpret_cast<T*>(buffer)) = val;
    }

    static inline void Write(void* buffer, const void* newBuffer, unsigned int writeSize)
    {
        memcpy(buffer, newBuffer, writeSize);
    }
};

}

#endif // _SERIALIZE_DATATOBUFFER_H_
