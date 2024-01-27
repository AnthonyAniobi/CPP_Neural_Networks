#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    float x = 0.0;

    for (unsigned i = 0; i < 10; ++i)
    {
        x += 0.1;
    }
    if (x == 1.0)
    {
        cout << "it is equal to 1.0" << endl;
    }
    else
    {
        cout << "something went wrong" << endl;
    }
    cout << x << endl;
}