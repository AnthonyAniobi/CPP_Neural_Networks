#ifndef _FileLoader_
#define _FileLoader_
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <type_traits>
#include "../libconfig.hpp"

#define LayerString Layer(std::string)

BEGIN_NAMESPACE_SCRIPTING

template <typename T>
class FileLoader
{
private:
    std::vector<Layer(T)> data;
    std::vector<T> result;
    std::vector<LayerString> preview;
    T convertString(std::stringstream &input);
    T defaultValue(void) const;
    long row;
    long column;

public:
    FileLoader(const char *path); //, FileType fileType = FileType.csv);
    void print(const int length) const;
    void head(void) const { print(5); };
    long getColumn(void) const { return column; };
    void loadData(unsigned long startIndex = 1, unsigned long resultIndex = -1) const;
    std::vector<T> getResult(void) { return result; }
    std::vector<Layer(T)> getData(void) { return data; }
};

END_NAMESPACE_SCRIPTING

#endif