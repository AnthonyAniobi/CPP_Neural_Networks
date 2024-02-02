#include <iostream>
#include "../scripting/fileloader.cpp"
#include "../simplenn/net.cpp"

using namespace std;

void print(int, Layer(double) &, Layer(double) &, Layer(double) &);

int main()
{
    scripting::FileLoader<double> file("xor.csv");
    vector<Layer(double)> data = file.loadData();
    Layer(unsigned) topology;
    topology.push_back(2);
    topology.push_back(2);
    topology.push_back(1);

    //
    Net net(topology);
    for (int i = 0; i < data.size(); ++i)
    {
        Layer(double) xTrain(data[i].begin(), data[i].begin() + 2);
        Layer(double) yTrain;
        yTrain.push_back(data[i].back());
        net.feedForward(xTrain);
        net.backProp(yTrain);
        Layer(double) result;
        net.getResults(result);
        print(i, xTrain, yTrain, result);
    }
}

void print(int i, Layer(double) & input, Layer(double) & output, Layer(double) & result)
{
    cout << "Training " << i + 1 << ":--------------------------------" << endl;
    cout << "Input: " << input[0] << " : " << input[1] << endl;
    cout << "Expected: " << output[0] << endl;
    cout << "Result: " << result[0] << endl;
}