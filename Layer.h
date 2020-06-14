#ifndef _LAYER_H_
#define _LAYER_H_

#include "Neuron.h"
#include <vector>

using namespace std;

class Layer {
public:
    vector<Neuron> Neurons;
    vector<vector<double>> adjacencyMatrix;

    void construct(int);
    ~Layer();
private:
    double fRand(double, double);

};

#endif