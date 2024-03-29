#include "fileloader.hpp"

BEGIN_NAMESPACE_SCRIPTING

DEF_TEMPLATE(T)
FileLoader<T>::FileLoader(const char *path) //, FileType fileType = csv)
{
    std::ifstream csvFile(path);
    char c;
    std::stringstream colStream;
    Layer(std::string) rowList;
    column = 0;
    // row = 0;
    long colCount = 0;
    long count = 0; // number of chars in each col
    while (csvFile.get(c))
    {
        if (c == ',') // after each column
        {
            if (count <= 0)
            {
                rowList.push_back("");
            }
            else
            {
                std::string input;
                colStream >> input;
                colStream.clear();
                rowList.push_back(input);
                count = 0;
            }
            ++colCount;
        }
        else if (c == '\n') // at the end of the line
        {
            if (count > 0)
            {
                ++colCount;
                std::string input;
                colStream >> input;
                colStream.clear();
                rowList.push_back(input);
                count = 0;
            }
            column = (colCount > column) ? colCount : column;
            // ++row;
            colCount = 0;
            preview.push_back(rowList);
            rowList.clear(); // clear row
        }
        else
        {
            ++count;
            colStream << c; // insert item into stream
        }
    }
}

DEF_TEMPLATE(T)
void FileLoader<T>::loadData(unsigned long startIndex, unsigned long resultIndex) const
{
    Layer(T) rowList;
    std::stringstream s;
    for (unsigned long i = startIndex; i < preview.size(); ++i)
    {
        unsigned long rowSize = preview[i].size();
        for (unsigned long j = 0; j < rowSize; ++j)
        {
            s << preview[i][j];
            T x = convertString(s);
            if ((j == -1) && (j == (rowSize - 1)))
            {
                result.push_back(x);
            }
            else if (j == resultIndex)
            {
                result.push_back(x);
            }
            else
            {
                rowList.push_back(x);
            }
            s.clear();
        }
        data.push_back(rowList);
        rowList.clear();
    }
}

DEF_TEMPLATE(T)
T FileLoader<T>::convertString(std::stringstream &input)
{
    T x; // defaultValue();
    if (input >> x)
        ;
    return x;
}

DEF_TEMPLATE(T)
T FileLoader<T>::defaultValue(void) const
{
    // if ((T is u_int8_t) || (T is u_int16_t) || (T is u_int32_t) || (T is u_int64_t))
    T x;
    if (std::is_same<T, int>::value)
    {
        x = 0;
    }
    else if (std::is_same<T, double>::value)
    {
        x = 0.0;
    }
    else if (std::is_same<T, std::string>::value)
    {
        x = "";
    }
    else
    {
        assert(false);
    }
    return x;
}

DEF_TEMPLATE(T)
void FileLoader<T>::print(const int length) const
{
    assert(length < preview.size());
    std::cout << std::setw(10) << std::left;
    for (unsigned long i = 0; i < length; ++i)
    {
        for (unsigned long j = 0; j < preview[i].size(); ++j)
        {
            std::cout << std::setw(10) << std::left << preview[i][j];
        }
        std::cout << std::setw(10) << std::left << std::endl;
    }
}


END_NAMESPACE_SCRIPTING