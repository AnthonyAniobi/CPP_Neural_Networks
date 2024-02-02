#ifndef _LIB_CONFIG_
#define _LIB_CONFIG_
// imports
#include <vector>

// definitions
#define BEGIN_NAMESPACE_SCRIPTING \
    namespace scripting           \
    {

#define END_NAMESPACE_SCRIPTING }

#define DEF_TEMPLATE(T) template <typename T>
#define Layer(T) std::vector<T>

enum FileType
{
    csv,
    d4,
};

#endif