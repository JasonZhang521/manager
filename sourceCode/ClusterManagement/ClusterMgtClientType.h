#ifndef _CLUSTERMANAGEMENT_CLUSTERMGTCLIENTTYPE_H_
#define _CLUSTERMANAGEMENT_CLUSTERMGTCLIENTTYPE_H_

namespace ClusterManagement {
enum ClientType
{
    NodeType,
    UiType
};

class ClientTypeHasher
{
public:
    inline int operator() (ClientType type)
    {
        return static_cast<int>(type);
    }
};

class ClientTypeCompare
{
public:
    bool operator()(ClientType type1, ClientType type2)
    {
        return (type1 == type2);
    }
};
}

#endif // _CLUSTERMANAGEMENT_CLUSTERMGTCLIENTTYPE_H_
