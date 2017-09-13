#ifndef _IPCMESSAGE_IPCMESSAGEIDGENERATOR_H_
#define _IPCMESSAGE_IPCMESSAGEIDGENERATOR_H_
#include <stdint.h>

namespace IpcMessage {

class IpcMessageIdGenerator
{
    static uint64_t ipcMessagetId_;
public:
    IpcMessageIdGenerator();
    static uint64_t generateIpcMessageId();
};

}

#endif // _IPCMESSAGE_IPCMESSAGEIDGENERATOR_H_
