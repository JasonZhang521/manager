#ifndef _SERIALIZE_WRITEBUFFER_H_
#define _SERIALIZE_WRITEBUFFER_H_
#include "DataToBuffer.h"
#include "NetworkHost.h"
#include "Component.h"
#include "Macro.h"
#include <string>
#include <vector>

namespace Serialize {

class WriteBuffer
{
    unsigned int bufferSize_;
    char* buffer_;
    unsigned int dataSize_;
    unsigned int pos_;
public:
    WriteBuffer(unsigned int size = DefaultWriteBufferSize);
    ~WriteBuffer();

    template <typename T>
    void write(const T& val)
    {
        if (pos_ + sizeof(T) > bufferSize_)
        {
            resizeBuffer(sizeof(T));
        }
        T v = PlatformWrapper::H2N(val);
        DataToBuffer::Write<T>(buffer_ + pos_, v);
        pos_ += sizeof(T);
        dataSize_ += sizeof(T);
    }

    void write(const void* newBuffer, unsigned int writeSize);

    void write(const std::string& str);

    template<typename T>
    void write(const std::vector<T>& vec)
    {
        write(static_cast<uint16_t>(vec.size()));
        for (auto value : vec)
        {
            write(value);
        }
    }

    inline void write(float f)
    {
        write(&f, sizeof(float));
    }

    inline void write(double d)
    {
        write(&d, sizeof(double));
    }

    void* getBuffer() const;
    unsigned int getBufferSize() const;
    unsigned int getDataSize() const;

    void swap(WriteBuffer& buffer);
    bool operator==(const WriteBuffer& buffer);
    std::ostream& operator << (std::ostream& os) const;
private:
    void resizeBuffer(unsigned int additionSize);
    template <typename T>
    T HtoN(T val)
    {

    }

public:
    const static unsigned int DefaultWriteBufferSize;

public:
    GETCLASSNAME(WriteBuffer)
};

}

inline std::ostream& operator << (std::ostream& os, const Serialize::WriteBuffer& buffer)
{
    return buffer.operator <<(os);
}

#endif // WRITEBUFFER_H
