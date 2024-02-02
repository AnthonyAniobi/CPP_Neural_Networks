#include "net.hpp"

Net::Net(const std::vector<unsigned> &typology)
{
    unsigned numLayers = typology.size();
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum)
    {
        // create a new layer
        m_layers.push_back(Layer(Neuron)());
        // get the number of outputs of the next layer
        unsigned numOutputs = layerNum == (numLayers - 1) ? 0 : typology[layerNum + 1];

        // add neurons and bias to the new layer
        for (unsigned neuronNum = 0; neuronNum <= typology[layerNum]; ++neuronNum)
        {
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));
        }

        // force the output layer to 1.0 it is the last neuron created above
        m_layers.back().back().setOutputVal(1.0);
    }
}

void Net::feedForward(const std::vector<double> &inputVals)
{
    std::cout << "input Size: " << inputVals.size() << ", m_layers size: " << m_layers[0].size() << std::endl;
    assert(inputVals.size() == (m_layers[0].size() - 1));

    // assign the input values into the input layer ie. The first layer
    for (unsigned i = 0; i < inputVals.size(); ++i)
    {
        m_layers[0][i].setOutputVal(inputVals[i]);
    }
    // forward propgation through the whole neural network
    // loop through all the neruons in each layer
    // and call the feed forward function for each neuron

    // for loop skip the input because it is already set in the for loop above
    for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum)
    {
        // get a reference to the previous layer
        Layer(Neuron) &prevLayer = m_layers[layerNum - 1];
        // loop through each neuron in each layer except the bias neuron
        for (unsigned neuron = 0; neuron < m_layers[layerNum].size() - 1; ++neuron)
        {
            m_layers[layerNum][neuron].feedForward(prevLayer);
        }
    }
};

void Net::backProp(const std::vector<double> &targetVals)
{
    // calculate the overall erro on the output layer
    Layer(Neuron) &outputLayer = m_layers.back();
    //              1
    // rms = sqrt(  - * sum (target - actual)^2 )
    //              n
    // using the rms error function we first get the sum of the changes
    double m_error = 0.0;
    // get the rms of all the output neurons except the bias
    for (unsigned i = 0; i < outputLayer.size() - 1; ++i)
    {
        double delta = targetVals[i] - outputLayer[i].getOutputVal();
        m_error += delta * delta;
    }
    m_error /= outputLayer.size() - 1;
    m_error = std::sqrt(m_error);

    // save some values for error
    m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1);

    // calculate the output gradients excluding the bias
    for (unsigned i = 0; i < outputLayer.size() - 1; ++i)
    {
        outputLayer[i].calculateOutputGradients(targetVals[i]);
    }

    // calculate hidden gradients
    for (unsigned hiddenNum = m_layers.size() - 2; hiddenNum > 0; --hiddenNum)
    {
        // get reference to the hidden layer and the layer before that (when coming from the back)
        Layer(Neuron) &hiddenLayer = m_layers[hiddenNum];
        Layer(Neuron) &prevLayer = m_layers[hiddenNum + 1];
        // calculate hidden gradients for each neuron except the bias
        for (unsigned i = 0; i < hiddenLayer.size() - 1; ++i)
        {
            hiddenLayer[i].calculateHiddenGradients(prevLayer);
        }
    }

    // update the weights of the connections from the hidden layers to the output layers
    for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum)
    {
        // get reference to the layer and the layer after that (when moving forward)
        Layer(Neuron) &layer = m_layers[layerNum];
        Layer(Neuron) &prevLayer = m_layers[layerNum - 1];

        // update the value on each node except the bias
        for (unsigned i = 0; i < layer.size(); ++i)
        {
            layer[i].updateInputWeights(prevLayer);
        }
    }
}

void Net::getResults(std::vector<double> resultVals) const
{
    resultVals.clear();
    const Layer(Neuron) &lastLayer = m_layers.back();
    for (unsigned i = 0; i < lastLayer.size() - 1; ++i)
    {
        resultVals.push_back(lastLayer[i].getOutputVal());
    }
}