#include "Lock.h"

Lock::Lock(std::mutex& mutex)
    :mutex_(mutex)
{
    mutex_.lock();
}

Lock::~Lock()
{
    mutex_.unlock();
}
