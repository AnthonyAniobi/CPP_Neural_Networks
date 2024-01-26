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
    void calculateOutputGradients(double targetValues);
    void calculateHiddenGradients(const Layer &prevLayer);
    void updateInputWeights(Layer &prevLayer);

private:
    static double eta;   // anywhere between {0 and 1}
    static double alpha; // anywhere between {0 and 1}
    static double activationFunction(double x);
    static double activationFunctionDerivative(double x);
    double sumDOW(const Layer &nextLayer) const;
    double m_outputVal;
    unsigned m_index;
    double m_gradient;
    std::vector<Connection> m_outputWeights;
};

#endif