#include "WriteBuffer.h"
#include "Trace.h"
#include <algorithm>
#include <iostream>

namespace Serialize {
const unsigned int WriteBuffer::DefaultWriteBufferSize = 1024 * 128;

WriteBuffer::WriteBuffer(unsigned int bufferSize)
:bufferSize_(bufferSize)
,buffer_(new char[bufferSize])
,dataSize_(0)
,pos_(0)
{
}

WriteBuffer::~WriteBuffer()
{
   delete []  buffer_;
}

void WriteBuffer::write(const void* newBuffer, unsigned int writeSize)
{
    if (pos_ + writeSize > bufferSize_)
    {
        resizeBuffer(writeSize);
    }

    DataToBuffer::Write(&buffer_[pos_], newBuffer, writeSize);
    pos_ += writeSize;
    dataSize_ += writeSize;
}

void WriteBuffer::write(const std::string& str)
{
    write(static_cast<uint16_t>(str.size()));
    write(str.c_str(), str.size());
}

void* WriteBuffer::getBuffer() const
{
    return buffer_;
}

unsigned int WriteBuffer::getBufferSize() const
{
    return bufferSize_;
}

unsigned int WriteBuffer::getDataSize() const
{
    return dataSize_;
}

void WriteBuffer::swap(WriteBuffer& buffer)
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

bool WriteBuffer::operator==(const WriteBuffer& buffer)
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

std::ostream& WriteBuffer::operator << (std::ostream& os) const
{
    os << "["
       << "bufferSize=" << bufferSize_
       << ", dataSize=" << dataSize_
       << ", pos=" << pos_
       << ",stream=";
    for (unsigned int i = 0; i < dataSize_; ++i)
    {
        os << std::hex << (int)buffer_[i];
    }
    os << std::dec << "]";
    return os;
}

void WriteBuffer::resizeBuffer(unsigned int additionSize)
{
    bufferSize_ = bufferSize_ * 2 + additionSize;
    char* tempBuffer = new char[bufferSize_];
    std::copy(buffer_, buffer_ + dataSize_, tempBuffer);
    delete [] buffer_;
    buffer_ = tempBuffer;
}

}
