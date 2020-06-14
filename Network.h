#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <vector>
#include "Layer.h"

const int num_pixels = 784;

const int num_layers = 4;

const int num_hidden_layers = 2;
const int hidden_layer_size = 16;


class Network {
private:
    //size 4
    //input layer
    //2 hidden layers
    //output layer
    vector<Layer> Layers;
public:
    Network();
private:
    double fRand(double, double);

};

#endif
