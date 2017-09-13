#include "IpcThreadSafeMessageQueue.h"
#include "IIpcMessage.h"
#include "Lock.h"
namespace IpcMessage {

IpcThreadSafeMessageQueue::IpcThreadSafeMessageQueue()
{

}

IpcThreadSafeMessageQueue::~IpcThreadSafeMessageQueue()
{

}

bool IpcThreadSafeMessageQueue::isEmpty()
{
    Lock lock(mutex_);
    return messageList_.empty();
}

size_t IpcThreadSafeMessageQueue::getSize()
{
    Lock lock(mutex_);
    return messageList_.size();
}

std::unique_ptr<IIpcMessage> IpcThreadSafeMessageQueue::popFront()
{
    Lock lock(mutex_);
    if (!messageList_.empty())
    {
        std::unique_ptr<IIpcMessage> msg = std::move(messageList_.front());
        messageList_.pop_front();
        return msg;
    }
    else
    {
        return nullptr;
    }
}

void IpcThreadSafeMessageQueue::pushBack(std::unique_ptr<IIpcMessage> msg)
{
    Lock lock(mutex_);
    messageList_.push_back(std::move(msg));
}
}
