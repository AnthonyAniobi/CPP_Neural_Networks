#ifndef _NET_
#define _NET_
#include <vector>
#include <cassert>
#include <cmath>
#include "neuron.cpp"
#include "../libconfig.hpp"

class Net
{
public:
    Net(const std::vector<unsigned> &topology);
    void feedForward(const std::vector<double> &inputVals);
    void backProp(const std::vector<double> &targetVals);
    void getResults(std::vector<double> resultVals) const;

private:
    std::vector<Layer(Neuron)> m_layers; // m_layers[layer][neurons]
    double m_error;
    double m_recentAverageError;
    double m_recentAverageSmoothingFactor;
};

#endif