#include "neuron.hpp"
#include <cstdlib>
#include <cmath>

double randomWeights(void);

Neuron::Neuron(unsigned numOutputs, unsigned index)
{
    m_index = index;
    for (unsigned c = 0; c < numOutputs; c++)
    {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeights();
    }
}

void Neuron::setOutputVal(double outputVal)
{
    m_outputVal = outputVal;
}

double Neuron::getOutputVal(void) const
{
    return m_outputVal;
}

void Neuron::feedForward(const Layer &prevLayer)
{
    double sum = 0.0;
    for (unsigned i = 0; i < prevLayer.size(); i++)
    {
        sum += prevLayer[i].getOutputVal() * prevLayer[i].m_outputWeights[m_index].weight;
    }
    m_outputVal = activationFunction(sum);
}

double Neuron::activationFunction(double x)
{
    return std::tanh(x);
}

double Neuron::activationFunctionDerivative(double x)
{
    // The actual derivative is
    // d
    // - (tanh x)= 1- tanh^2 (x)
    // dx
    return 1.0 - x * x;
}

double randomWeights(void)
{
    return rand() / double(RAND_MAX);
}