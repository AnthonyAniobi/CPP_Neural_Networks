// main.cpp file

#include <iostream>
#include <vector>
#include "nn/net.cpp"

int main()
{
    // typology specifies the shape of the input layers
    // eg: {3, 2, 1}
    std::vector<unsigned> typology;
    typology.push_back(3);
    typology.push_back(2);
    typology.push_back(1);
    Net myNet(typology);
    std::vector<double> inputVals;
    myNet.feedForward(inputVals);
    std::vector<double> targetVals;
    myNet.backProp(targetVals);
    std::vector<double> resultVals;
    myNet.getResults(resultVals);
    return 0;
}
