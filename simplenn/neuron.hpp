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
    Neuron(unsigned numOutputs, unsigned index);
    void setOutputVal(double outputVal);
    double getOutputVal(void) const;
    void feedForward(const Layer &prevLayer);

private:
    static double activationFunction(double x);
    static double activationFunctionDerivative(double x);
    double m_outputVal;
    unsigned m_index;
    std::vector<Connection> m_outputWeights;
};

#endif