/**
 * Represents a layer in a neural network though a vector that holds Neuron objects.
 * @author Christopher Mouri, Anderson Tsai
 */
#include "Network.h"
#include "Layer.h"
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

/** Destructor for me. */
Layer::~Layer() {
    Neurons.clear();
}

/** Instantiates and places NUM_NEURONS in me. */
void Layer::construct(int num_neurons) {
    for (int i = 0; i < num_neurons; ++i) {
        Neuron new_neuron{};
        new_neuron.bias = 0;
        Neurons.push_back(new_neuron);
    }
}

/** Takes in a pointer to layer NEXT_OVER and initializes an adjacency matrix
 *  with random weights between the neurons in me and the layer NEXT_OVER */
void Layer::initialize_weights(Layer *next_over) {
    unsigned next_layer_size = next_over->Neurons.size();
    adjacencyMatrix = new double* [next_layer_size];
    for (unsigned i = 0; i < next_layer_size; ++i) {
        adjacencyMatrix[i] = new double[Neurons.size()];
    }

    for (unsigned i = 0; i < next_layer_size; ++i) {
        for (unsigned j = 0; j < Neurons.size(); ++j) {
            double random_weight = Network::fRand(-1,1);
            adjacencyMatrix[i][j] = random_weight;
//            cout << adjacencyMatrix[i][j] << ' ';
        }
//        cout << endl;
    }
    adjacency_rows = next_layer_size;
    adjacency_cols = Neurons.size();
//    cout << endl;
//    cout << endl;
}
