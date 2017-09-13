#include "ReadBuffer.h"
#include "Trace.h"
#include <exception>

namespace Serialize {

const unsigned int ReadBuffer::DefaultReadBufferSize = 1024 * 128;
const unsigned int ReadBuffer::MaxStringSize = 2048;

ReadBuffer::ReadBuffer(unsigned int bufferSize)
:bufferSize_(bufferSize)
,buffer_(new char[bufferSize])
,dataSize_(0)
,pos_(0)
{
}

ReadBuffer::~ReadBuffer()
{
    delete [] buffer_;
}

bool ReadBuffer::read(void* newBuffer, unsigned int readSize)
{
    if (pos_ + readSize > dataSize_)
    {
        return false;
    }
    BufferToData::Read(buffer_ + pos_, newBuffer, readSize);
    pos_ += readSize;
    return true;
}

bool ReadBuffer::read(std::string& str)
{
    uint16_t size = 0;
    read(size);
    // suppose the max length of string is 2048
    char buffer[MaxStringSize];
    read(buffer, size);
    str = std::string(buffer, size);
    return true;
}

void ReadBuffer::setDataSize(unsigned int dataSize)
{
    if (dataSize > bufferSize_)
    {
        TRACE_ERROR("Data size is bigger than the buffer size: data size = " << dataSize << ", buffer size = " << bufferSize_);
        throw std::out_of_range("Data size is bigger than the buffer size");
    }
    dataSize_ = dataSize;
}

void* ReadBuffer::getBuffer() const
{
    return buffer_;
}

unsigned int ReadBuffer::getBufferSize() const
{
    return bufferSize_;
}

bool ReadBuffer::isEndOfData() const
{
    return (dataSize_ == pos_);
}

unsigned int ReadBuffer::getDataSize() const
{
    return dataSize_;
}

void ReadBuffer::swap(ReadBuffer& buffer)
{
    unsigned int tempBufferSize = buffer.bufferSize_;
    char* tempBuffer = buffer.buffer_;
    unsigned int tempDataSize = buffer.dataSize_;
    unsigned int tempPos = buffer.pos_;

    buffer.bufferSize_ = bufferSize_;
    buffer.buffer_ = buffer_;
    buffer.dataSize_ = dataSize_;
    buffer.pos_ = pos_;

    bufferSize_ = tempBufferSize;
    buffer_ = tempBuffer;
    dataSize_ = tempDataSize;
    pos_ = tempPos;

}

bool ReadBuffer::operator==(const ReadBuffer& buffer)
{
    if (bufferSize_ != buffer.bufferSize_ ||
        dataSize_ != buffer.dataSize_ ||
        pos_ != buffer.pos_)
    {
        return false;
    }

    for (unsigned int i = 0; i < dataSize_; ++i)
    {
        if (buffer_[i] != buffer.buffer_[i])
        {
            return false;
        }
    }

    return true;
}

std::ostream& ReadBuffer::operator << (std::ostream& os) const
{
    os << "["
       << "bufferSize=" << bufferSize_
       << ", dataSize=" << dataSize_
       << ", pos=" << pos_
       << ",stream=";
    for (unsigned int i = 0; i < dataSize_; ++i)
    {
        os << std::hex;
        if ((uint32_t)buffer_[i] <= 0x0F)
        {
            os << "0" << (uint32_t)buffer_[i];
        }
        else
        {
            os << (uint32_t)buffer_[i];
        }
    }
    os << std::dec << "]";
    return os;
}

}
