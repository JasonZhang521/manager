#ifndef _SERIALIZE_READBUFFER_H_
#define _SERIALIZE_READBUFFER_H_
#include "BufferToData.h"
#include "NetworkHost.h"
#include "Component.h"
#include "Macro.h"
#include <ostream>
#include <string>
#include <vector>
namespace Serialize {

class ReadBuffer
{
public:
    const static unsigned int DefaultReadBufferSize;
    const static unsigned int MaxStringSize;
private:
    unsigned int bufferSize_;
    char* buffer_;
    unsigned int dataSize_;
    unsigned int pos_;
public:
    ReadBuffer(unsigned int bufferSize = DefaultReadBufferSize);
    ~ReadBuffer();
    template <typename T>
    bool read(T& val)
    {
        if (pos_ + sizeof(T) > dataSize_)
        {
            return false;
        }
        val = BufferToData::Read<T>(buffer_ + pos_);
        val = PlatformWrapper::N2H(val);
        pos_ += sizeof(T);
        return true;
    }

    bool read(void* newBuffer, unsigned int readSize);

    bool read(std::string& str);

    template <typename T>
    bool read(std::vector<T>& vec)
    {
        std::vector<T> temp;
        uint16_t size = 0;
        read(size);
        for (uint16_t i = 0; i < size; ++i)
        {
            T value;
            read(value);
            temp.push_back(value);
        }
        vec.swap(temp);
        return true;
    }

    inline bool read(float& f)
    {
        return read(&f, sizeof(float));
    }

    inline bool read(double& d)
    {
        return read(&d, sizeof(double));
    }


    template <typename T>
    bool peek(T& val, unsigned int start = 0)
    {
        if (pos_ + start + sizeof(T) > dataSize_)
        {
            return false;
        }
        val = BufferToData::Read<T>(buffer_ + pos_ + start);
        return true;
    }

    void* getBuffer() const;
    unsigned int getDataSize() const;
    void setDataSize(unsigned int dataSize);
    unsigned int getBufferSize() const;
    bool isEndOfData() const;

    void swap(ReadBuffer& buffer);
    bool operator==(const ReadBuffer& buffer);

    std::ostream& operator << (std::ostream& os) const;

public:
    GETCLASSNAME(ReadBuffer)
};

}

inline std::ostream& operator << (std::ostream& os, const Serialize::ReadBuffer& buffer)
{
    return buffer.operator <<(os);
}


#endif // _SERIALIZE_READBUFFERR_H_
