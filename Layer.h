#ifndef _LAYER_H_
#define _LAYER_H_

#include "Neuron.h"
#include <vector>
#include <cmath>

// const int hidden_layer_size = 16;
// const int he_initialization = sqrt(2/hidden_layer_size);

using namespace std;

class Layer {
public:
    vector<Neuron> Neurons;
    double **adjacencyMatrix;
    unsigned adjacency_rows;
    unsigned adjacency_cols;

    void construct(int);
    void initialize_weights(Layer *);
    ~Layer();
private:
    double fRand(double, double);
};

#endif
