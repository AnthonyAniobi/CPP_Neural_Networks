#include "fileloader.hpp"

BEGIN_NAMESPACE_SCRIPTING

DEF_TEMPLATE(T)
FileLoader<T>::FileLoader(const char *path, FileType fileType = FileType.csv)
{
    std::ifstream csvFile(path);
    char c;
    std::stringstream colStream;
    Layer<std::string> row;
    long count = 0; // number of chars in each col
    while (csvFile.get(c))
    {
        if (c == ',') // after each column
        {
            if (count <= 0)
            {
                row.push_back("");
            }
            else
            {
                std::string input;
                colStream >> input;
                colStream.clear();
                row.push_back(input);
                count = 0;
            }
        }
        else if (c == '\n') // at the end of the line
        {
            if (count > 0)
            {
                std::string input;
                colStream >> input;
                colStream.clear();
                row.push_back(input);
                count = 0;
            }
            data.push_back(row);
            row.clear(); // clear row
        }
        else
        {
            ++count;
            colStream << c // insert item into stream
        }
    }
}

DEF_TEMPLATE(T)
std::vector<Layer<T>> FileLoader<T>::loadData(const unsigned long startIndex = 0, const T fillValue = 0)
{
    std::vector<Layer<T>> matrix;
    Layer<T> row;
    std::stringstream s;
    for (unsigned long i = startIndex; i < preview.size(); ++i)
    {
        for (unsigned long j = 0; j < preview[i].size(); ++j)
        {
            s << preview[i][j];
            row.push_back(convertString(s));
            s.clear();
        }
        matrix.push_back(row);
        row.clear();
    }
}

DEF_TEMPLATE(T)
T FileLoader<T>::convertString(const std::stringstream *input) const
{
    T x = defaultValue();
    if (input >> x)
        ;
    return x;
}

DEF_TEMPLATE(T)
T FileLoader<T>::defaultValue(void) const
{
    if ((T is u_int8_t) || (T is u_int16_t) || (T is u_int32_t) || (T is u_int64_t))
    {
        x = 0;
    }
    else if (T is float || T is double)
    {
        x = 0.0;
    }
    else if (T is std::string)
    {
        x = "";
    }
    else
    {
        assert(false);
    }
}

DEF_TEMPLATE(T)
void FileLoader<T>::print(const int length) const
{
    assert(length < preview.size());
    std::cout << std::setw(maxRow + 2) << std::left;
    for (unsigned long i = 0; i < length; ++i)
    {
        for (unsigned long j = 0; j < preview[i].length(); ++j)
        {
            cout << preview[i][j];
        }
        cout << endl;
    }
}
DEF_TEMPLATE(T)
void FileLoader<T>::head(void) const
{
    print(5);
}

END_NAMESPACE_SCRIPTING