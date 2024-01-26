#ifndef _NEURON_
#define _NEURON_
#include <vector>

struct Connection
{
    double weight;
    double deltaWeight;
};

class Neuron;

typedef std::vector<Neuron> Layer;

class Neuron
{
public:
    Neuron(unsigned numOutputs);

private:
    double m_outputVal;
    std::vector<Connection> m_outputWeights;
};

#endif