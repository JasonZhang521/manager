#ifndef _GENERIC_H_
#define _GENERIC_H_
#include <sstream>
#include <type_traits>

template <typename Target, typename Source> Target lexical_cast(const Source& source)
{
    std::stringstream ss;
    ss << source;
    Target target;
    ss >> target;
    return target;
}


template <typename E>
constexpr auto toIntegral(E e)->typename std::underlying_type<E>::type
{
    return static_cast<typename std::underlying_type<E>::type>(e);
}

#endif // _GENERIC_H_
