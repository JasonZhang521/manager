#ifndef LOCK_H
#define LOCK_H
#include <mutex>


class Lock
{
    std::mutex& mutex_;
public:
    Lock(std::mutex& mutex);
    ~Lock();
};

#endif // LOCK_H
