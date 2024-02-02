#include <iostream>
#include <cstdlib>
#include "../scripting/fileloader.cpp"

using namespace std;

int main()
{
    scripting::FileLoader<double> file("xor.csv");

    file.loadData();

    vector<Layer(double)> data = file.getData();
    vector<double> results = file.getResult();

    for (unsigned long i = 0; i < 20; ++i)
    {
        for (unsigned long j = 0; j < file.getColumn(); ++j)
        {
            cout << data[i][j] << " , ";
        }
        cout << " -  result: " << results[i] << endl;
    }
}