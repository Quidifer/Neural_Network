#include "Network.h"
#include "Layer.h"
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

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

    int guess = forward_propogation();
}

int Network::forward_propogation() {
    Layer* test = &(Layers.at(0));
    return forward_propogation(test, 0);
}
int Network::forward_propogation(Layer* curr_layer, int index) {
    if (curr_layer == &Layers.at(Layers.size()-1)) {
        return 1;
    }
    vector<double> activations;
     matrix_vector_mult(curr_layer, activations);

     for (unsigned i = 0; i < activations.size(); ++i) { //add biases to activations
         activations.at(i) += curr_layer->Neurons.at(i).bias;
         cout << activations.at(i) << "    ";
         activations.at(i) = sigmoid(activations.at(i));
         Layers.at(index+1).Neurons.at(i).activation = activations.at(i);
         cout << activations.at(i) << endl;
     }
     cout << endl << endl;

    return forward_propogation(&(Layers.at(index+1)), index + 1);

}
void Network::matrix_vector_mult(Layer* curr_layer, vector<double> &activations) {
    double sum = 0;
    for (unsigned i = 0; i < curr_layer->adjacency_rows; ++i) {
        for (unsigned j = 0; j < curr_layer->adjacency_cols; ++j) {
            sum += curr_layer->adjacencyMatrix[i][j] * curr_layer->Neurons.at(j).activation;
            // cout << curr_layer->Neurons.at(j).activation << endl;
        }
        activations.push_back(sum);
        sum = 0;
    }
}

double Network::sigmoid(double x) {
    const double e = 2.71828;
    return 1.0 / (1.0 + pow(e,-x));
}

// double Network::ReLU(double x) {
//     if (x < 0) {
//         return 0;
//     }
//     else {
//         return x;
//     }
// }

double Network::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
