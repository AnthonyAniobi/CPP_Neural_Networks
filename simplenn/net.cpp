#include "net.hpp"
#include <iostream>

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
            m_layers.back().push_back(Neuron(numOutputs));
            std::cout << "Made a neuron-> layer: " << layerNum << " neuron num: " << neuronNum << std::endl;
        }
    }
}