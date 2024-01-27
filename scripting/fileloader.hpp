#ifndef _FileLoader_
#define _FileLoader_
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include "datatype.hpp"

BEGIN_NAMESPACE_SCRIPTING

template <typename T>
class FileLoader
{
private:
    std::vector<Layer<T>> data;
    void convertString(const std::stringstream *input, T &ouput) const;
    // void convertString(const std::stringstream *input, int &ouput) const;
    // void convertString(const std::stringstream *input, float &ouput) const;

public:
    void loadCSV(const char *path) const;
};

END_NAMESPACE_SCRIPTING

#endif