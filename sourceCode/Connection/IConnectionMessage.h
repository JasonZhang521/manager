#ifndef ICONNECTIONMESSAGE_H
#define ICONNECTIONMESSAGE_H
#include <stdint.h>

namespace Connection {

namespace Serialize
{
class WriteBuffer;
class ReadBuffer;
}

class IConnectionMessage
{
public:
    IConnectionMessage();
    virtual ~IConnectionMessage();
    virtual uint64_t getMessageId() const = 0;
    virtual void serialize(Serialize::WriteBuffer& writeBuffer) const = 0;
    virtual void unserialize(Serialize::ReadBuffer& readBuffer) = 0;
};

}
#endif // ICONNECTIONMESSAGE_H
