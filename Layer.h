#ifndef _LAYER_H_
#define _LAYER_H_

#include "Neuron.h"
#include <vector>

using namespace std;

class Layer {
public:
    vector<Neuron> Neurons;
    double **adjacencyMatrix;

    void construct(int);
    void initialize_weights(Layer *);
    ~Layer();
private:
    double fRand(double, double);

};

#endif
