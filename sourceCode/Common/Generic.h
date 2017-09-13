#ifndef _GENERIC_H_
#define _GENERIC_H_
#include <sstream>
template <typename Target, typename Source> Target lexical_cast(const Source& source)
{
    std::stringstream ss;
    ss << source;
    Target target;
    ss >> target;
    return target;
}

#endif // _GENERIC_H_
