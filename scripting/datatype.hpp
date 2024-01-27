#ifndef _DATATYPE_
#define _DATATYPE_
// imports
#include <vector>

// definitions
#define BEGIN_NAMESPACE_SCRIPTING \
    namespace scripting           \
    {

#define END_NAMESPACE_SCRIPTING }

#define DEF_TEMPLATE(T) template <typename T>

template <typename T>
using Layer = std::vector<T>;

enum FileType
{
    csv,
    d4,
};

#endif