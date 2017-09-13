#ifndef _SERIALIZE_ISERIALIZABLE_H_
#define _SERIALIZE_ISERIALIZABLE_H_

namespace Serialize {

class WriteBuffer;
class ReadBuffer;
class ISerializable
{
public:
    ISerializable();
    virtual void serialize(WriteBuffer& buffer) const = 0;
    virtual void unserialize(ReadBuffer& buffer) = 0;
};

}

#endif // ISERIALIZABLE_H
