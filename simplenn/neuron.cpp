#include "neuron.hpp"
#include <cstdlib>

double randomWeights(void);

Neuron::Neuron(unsigned numOutputs)
{
    for (unsigned c = 0; c < numOutputs; c++)
    {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeights();
        }
}

double randomWeights(void)
{
    return rand() / double(RAND_MAX);
}