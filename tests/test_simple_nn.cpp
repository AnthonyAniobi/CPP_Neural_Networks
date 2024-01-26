#include <iostream>
#include <cstdlib>
#include "../simplenn/net.cpp"

using namespace std;

int main()
{
    // test simple nn using xor
    vector<unsigned> lengthOfLayersVector;
    lengthOfLayersVector.push_back(2);
    lengthOfLayersVector.push_back(2);
    lengthOfLayersVector.push_back(1);

    // initialize vector
    Net net(lengthOfLayersVector);
    //
    for (int i = 0; i < 2000; i++)
    {
        // get test data
        int n1 = (int)(2.0 * rand() / double(RAND_MAX));
        int n2 = (int)(2.0 * rand() / double(RAND_MAX));
        int r = n1 ^ n2;
        vector<double> x_train;
        vector<double> y_train;
        x_train.clear();
        y_train.clear();
        x_train.push_back(double(n1));
        x_train.push_back(double(n2));
        y_train.push_back(double(r));
        net.feedForward(x_train);
        net.backProp(y_train);
        vector<double> result;
        result.clear();
        net.getResults(result);
        // some data
        cout << "Input:            " << x_train[0] << " : " << x_train[1] << endl
             << "Expected Output:  " << y_train[0] << endl
             //  << "Actual Output:    " << result[0] << endl
             << endl;
    }
    return 0;
}