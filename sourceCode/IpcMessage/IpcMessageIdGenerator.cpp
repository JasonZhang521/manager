#include "IpcMessageIdGenerator.h"

namespace IpcMessage {

uint64_t IpcMessageIdGenerator::ipcMessagetId_ = 0;

IpcMessageIdGenerator::IpcMessageIdGenerator()
{
}

uint64_t IpcMessageIdGenerator::generateIpcMessageId()
{
    return ipcMessagetId_++;
}

}
