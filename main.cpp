// main.cpp file

#include <iostream>
#include <vector>
#include "nn/net.hpp"

int main()
{
    // typology specifies the shape of the input layers
    // eg: {3, 2, 1}
    std::vector<unsigned> typology;
    Net myNet(typology);
    std::vector<double> inputVals;
    myNet.feedForward(inputVals);
    std::vector<double> targetVals;
    myNet.backProp(targetVals);
    std::vector<double> resultVals;
    myNet.getResults(resultVals);
}
