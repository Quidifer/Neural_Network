#include "Network.h"
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>

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

int Network::guessImage(vector<vector<unsigned int>> image) {
    unsigned stepper = 0;
    for (unsigned i = 0; i < image.size(); ++i) { //initialize acitvations of the input layer
        for (unsigned j = 0; j < image.at(i).size(); ++j) {
            double new_activation = (image.at(i).at(j)/255.0);
            Layers.at(0).Neurons.at(stepper).activation = new_activation;
            cout << Layers.at(0).Neurons.at(stepper).activation << ' ';
            ++stepper;
        }
        cout << endl;
    }
}

double Network::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
