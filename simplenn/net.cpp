#include "net.hpp"
#include <iostream>
#include <cassert>

Net::Net(const std::vector<unsigned> &typology)
{
    unsigned numLayers = typology.size();
    for (unsigned layerNum = 0; layerNum < numLayers; layerNum++)
    {
        // create a new layer
        m_layers.push_back(Layer());
        // get the number of outputs of the next layer
        unsigned numOutputs = layerNum == (numLayers - 1) ? 0 : typology[layerNum + 1];

        // add neurons and bias to the new layer
        for (unsigned neuronNum = 0; neuronNum <= typology[layerNum]; neuronNum++)
        {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));
            std::cout << "Made a neuron-> layer: " << layerNum << " neuron num: " << neuronNum << std::endl;
        }
    }
}

void Net::feedForward(const std::vector<double> &inputVals)
{
    assert(inputVals.size() == (m_layers[0].size() - 1));

    // assign the input values into the input layer ie. The first layer
    for (unsigned i = 0; i < inputVals.size(); i++)
    {
        m_layers[0][i].setOutputVal(inputVals[i]);
    }
    // forward propgation through the whole neural network
    // loop through all the neruons in each layer
    // and call the feed forward function for each neuron

    // for loop skip the input because it is already set in the for loop above
    for (unsigned layerNum = 1; layerNum < m_layers.size(); layerNum++)
    {
        // get a reference to the previous layer
        Layer &prevLayer = m_layers[layerNum - 1];
        // loop through each neuron in each layer except the bias neuron
        for (unsigned neuron = 0; neuron < m_layers[layerNum].size() - 1; neuron++)
        {
            m_layers[layerNum][neuron].feedForward(prevLayer);
        }
    }
};