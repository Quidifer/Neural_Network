#include "Network.h"
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

Network::Network() {
    for (unsigned i = 0; i < num_layers; ++i) {
        Layer new_Layer;
        if (i == 0) { //construct input layer
            new_Layer.construct(num_pixels);
        }
        else if (i == num_layers - 1) { //construct output layer
            new_Layer.construct(10);
        }
        else { //construct hidden layer
            new_Layer.construct(hidden_layer_size);
        }

        Layers.push_back(new_Layer); //add created layer to layers
    }

    for (unsigned i = 0; i < Layers.size() - 1; ++i) {
        Layers.at(i).initialize_weights(&Layers.at(i+1));
    }
}

double Network::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
