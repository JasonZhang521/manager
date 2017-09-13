#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>

template <typename T>
class Singleton
{
    static std::unique_ptr<T> instance_;
public:
    static T& instance();
};

template <typename T>
T& Singleton<T>::instance()
{
    if (!instance_)
    {
        instance_ = std::unique_ptr<T>(new T());
    }

    return *instance_;
}

#endif // SINGLETON_H
