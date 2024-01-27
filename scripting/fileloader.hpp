#ifndef _FileLoader_
#define _FileLoader_
#include <iostream>
#include <iomanip>
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
    std::vector<Layer<std::string>> preview;
    T convertString(const std::stringstream *input) const;
    T defaultValue(void) const;
    long maxRow = 20;
    long minRow;

public:
    FileLoader(const char *path, FileType fileType = FileType.csv);
    void print(const int length) const;
    void head(void) const;
    std::vector<Layer<T>> loadData(const unsigned long startIndex = 0, const T fillValue = 0);
};

END_NAMESPACE_SCRIPTING

#endif