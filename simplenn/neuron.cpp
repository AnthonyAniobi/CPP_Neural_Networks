#include "neuron.hpp"
#include <cstdlib>
#include <cmath>

double randomWeights(void);

Neuron::Neuron(unsigned numOutputs, unsigned index)
{
    m_index = index;
    for (unsigned c = 0; c < numOutputs; ++c)
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
    for (unsigned i = 0; i < prevLayer.size(); ++i)
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
void Neuron::calculateOutputGradients(double targetValues)
{
    double delta = targetValues - m_outputVal;
    m_gradient = delta * Neuron::activationFunctionDerivative(m_outputVal);
}

void Neuron::calculateHiddenGradients(const Layer &prevLayer)
{
    double dow = sumDOW(prevLayer);
    m_gradient = dow * Neuron::activationFunctionDerivative(m_outputVal);
}

double Neuron::sumDOW(const Layer &nextLayer) const
{
    double sum = 0.0;
    // sum(w*(loss))
    for (unsigned i = 0; i < nextLayer.size() - 1; ++i)
    {
        sum += m_outputWeights[i].weight * nextLayer[i].m_gradient;
    }
    return sum;
}

void Neuron::updateInputWeights(Layer &prevLayer)
{
    for (unsigned i = 0; i < prevLayer.size(); ++i)
    {
        Neuron &neuron = prevLayer[i];
        double oldDeltaWeight = neuron.m_outputWeights[m_index].deltaWeight;
        // individual input magnified by the gradient and training rate
        double newDeltaWeight = eta * neuron.getOutputVal() * oldDeltaWeight * m_gradient * alpha;
        neuron.m_outputWeights[m_index].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_index].weight += newDeltaWeight;
    }
}

double Neuron::eta = 0.15;  // overall learning rate
double Neuron::alpha = 0.5; // overall momentum

double randomWeights(void)
{
    return rand() / double(RAND_MAX);
}