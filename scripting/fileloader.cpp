#include "fileloader.hpp"

BEGIN_NAMESPACE_SCRIPTING

DEF_TEMPLATE(T)
void FileLoader<T>::loadCSV(const char *path) const
{
    // get a csv file and load the data
    // note this file loader does not have
    std::ifstream csvFile(path);
    char c;
    std::stringstream colStream;
    Layer<T> row;
    while (csvFile.get(c))
    {
        if (c == ',') // after each column
        {
            T input;
            convertString(colStream, input);
            colStream.clear();
            row.push_back(input);
        }
        else if (c == '\n') // at the end of the line
        {
            if (value.size() > 0)
            {
                T input;
                convertString(colStream, input);
                value.clear();
                row.push_back(input);
            }
            data.push_back(row);
            row.clear(); // clear row
        }
        else
        {
            colStream.put(c); // insert item into stream
        }
    }
}

DEF_TEMPLATE(T)
void FileLoader<T>::convertString(const std::stringstream *input, T &output) const
{
    T x;
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
        assert("Template must be a fundamental type");
    }
    if (input >> x)
        ;
    output = x;
}

END_NAMESPACE_SCRIPTING