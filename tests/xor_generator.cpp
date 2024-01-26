// xor_generator.cpp
// a function to generate a list of

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{

    cout << "Input, Output,Result\n";
    for (int i = 0; i < 2000; i++)
    {
        int n1 = (int)(2.0 * rand() / double(RAND_MAX));
        int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int res = n1 ^ n2;
        cout << n1 << ".0, " << n2 << ".0, " << res << ".0" << endl;
    }
}