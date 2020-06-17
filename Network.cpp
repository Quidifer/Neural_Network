/**
 * Static-typed class that manages all layers in the network.
 * @author Christopher Mouri, Anderson Tsai
 */
#include "Network.h"
#include "Layer.h"
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
static vector<Layer> Layers;

/** Sets up network. Creates a neural network with biases of each neuron set to 0
and random weights between -1 and 1.
There are 4 layers in total:
    - 1 input layer of 784 nodes to represent all pixels in the initial image
    - 2 hidden layers, each with 16 nodes each
    - 1 output layer with ten nodes representing the answers for 0-9 */
void Network::setup(int num_layers, int hidden_layer_size) {
    for (unsigned i = 0; i < num_layers; ++i) {
        Layer new_Layer{};
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

/** Takes a 2D vector of unsigned integers representing a grayscale image. Dimensions of
    2D vector should be 28x28. Returns an integer corresponding to the network's prediction
    of what number is written in the image.*/
int Network::guessImage(vector<vector<unsigned int>> image) {
    unsigned stepper = 0;
    for (auto & i : image) { //initialize activations of the input layer
        for (unsigned int j : i) {
            double new_activation = (j/255.0);
            Layers.at(0).Neurons.at(stepper).activation = new_activation;
//            cout << Layers.at(0).Neurons.at(stepper).activation << ' ';
            ++stepper;
        }
//        cout << endl;
    }

    int guess = forward_propagation();
    return guess;
}

/** Public function that runs forward propagation on the Network. Returns the result of running
 *  the propogation. */
int Network::forward_propagation() {
    Layer* test = &(Layers.at(0));
    return forward_propagation(test, 0);
}


/** Helper function for forward propogation. Takes a layer CURR_LAYER, and an INDEX.
 *  If the CURR_LAYER is the output layer, then the result of guess_number is returned.
 *  Otherwise, */
int Network::forward_propagation(Layer* curr_layer, int index) {
    if (curr_layer == &Layers.at(Layers.size()-1)) {
        return Network::guess_number(curr_layer);
    }
    vector<double> activations;
    matrix_vector_mult(curr_layer, activations);

//     cout << "ACTIVATIONS" << endl;
//     cout << "before sig  " << "after sig" << endl;
     for (unsigned i = 0; i < activations.size(); ++i) { //add biases to activations
         activations.at(i) += sigmoid(curr_layer->Neurons.at(i).bias);
//         cout << activations.at(i) << "    ";
         Layers.at(index+1).Neurons.at(i).z = activations.at(i);
         activations.at(i) = sigmoid(activations.at(i));
         Layers.at(index+1).Neurons.at(i).activation = activations.at(i);
//         cout << activations.at(i) << endl;
     }
//     cout << endl << endl;

    return forward_propagation(&(Layers.at(index+1)), index + 1);
}

/** Takes in a Layer CURR_LAYER and a vector of doubles ACTIVATIONS and carries out
 *  matrix multiplication by multiplying each value in the adjacency matrix of each
 *  layer by the activation energy. */
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

/** Takes in the OUTPUT_LAYER and finds the neuron with the maximum activation. Returns
 *  the position of the neuron in the output layer, which corresponds to the number
 *  predicted by the network. */
int Network::guess_number(Layer* output_layer) {
    int max = 0;
    for (unsigned i = 0; i < output_layer->Neurons.size(); ++i) { //get the max activation index
        if (output_layer->Neurons.at(i).activation > output_layer->Neurons.at(max).activation) {
            max = i;
        }
    }
    return max;
}

/** Sigmoid function. Takes in a double X and returns X scaled between 0 and 1. */
double Network::sigmoid(double x) {
    const double e = 2.71828;
    return 1.0 / (1.0 + pow(e,-x));
}

/** Takes derivative of a function F with an input X. Returns the output of f'(x). */
double derivation(double (Network::*f)(double), double x) {
    double h = 1e-8;
    return (f(x + h) - f(x + h)) / (2 * h);
}

// double Network::ReLU(double x) {
//     if (x < 0) {
//         return 0;
//     }
//     else {
//         return x;
//     }
// }

/** Takes in doubles FMIN and FMAX and returns a number between FMIN and FMAX. */
double Network::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

/** Takes in the OUTPUT_LAYER and returns the cost of the neural network. */
double Network::Cost(Layer* output_layer) {
    double sum = 0;
    for (unsigned i = 0; i < output_layer->Neurons.size(); ++i) {
        sum += pow(output_layer->Neurons.at(i).adjustment_activation,2);
    }
    return sum;
}

/** FIXME: add method header */
void Network::compute_adjustments(Layer* curr_layer, int label) {
    for (unsigned i = 0; i < curr_layer->Neurons.size(); ++i) {
        if (i == label) { // activation needs to be 1 at the correct neuron
            curr_layer->Neurons.at(i).adjustment_activation = 1 - curr_layer->Neurons.at(i).activation;
        }
        else { //activation needs to be 0 at the incorrect neurons
            curr_layer->Neurons.at(i).adjustment_activation = 0 - curr_layer->Neurons.at(i).activation;
        }
    }
}

/** FIXME: add method header *//*
void Network::back_propagation() {
    back_propagation(&(Layers.at(Layers.size()-2)), Layers.size()-2);
}

*//** FIXME: add method header and complete back propagation helper functions *//*
void Network::back_propagation(Layer* curr_layer, int index) {
    for (unsigned i = 0; i < curr_layer->adjacency_rows; ++i) {
        for (unsigned j = 0; j < curr_layer->adjacency_cols; ++j) {
            double weight_adjustment = adjust_weight(curr_layer, index, i, j);
        }
    }
}

*//** FIXME: Add method header. *//*
double adjust_weight(Layer* curr_layer, int index, unsigned i, unsigned j) {
    Layer* next_over = &(Layers.at(index+1));
    Neuron* right_neuron;
    Neuron* left_neuron;
    double dzdw = curr_layer->Neurons.at(j).activation;
    double dadz = derivation(sigmoid(), )
    double answer =
}*/

/** Changes adjustment bias in each neuron in L. */
void Network::adjust_bias(Layer* l) {
    for (Neuron &n : l->Neurons) {
        n.bias -= sigmoid(n.z) * (2 * (n.adjustment_activation));
    }
}
