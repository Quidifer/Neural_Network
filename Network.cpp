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
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
#include <queue>

using namespace std;
static vector<Layer> Layers;

double sigmoid(double);
double derivation(double (*f)(double), double x);

/** Creates a neural network with biases of each neuron set to 0
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
    of what number is written in the image.
*/
int Network::guessImage(vector<vector<unsigned int>> image) {
    unsigned stepper = 0;
    for (auto & i : image) { //initialize activations of the input layer
        for (unsigned int j : i) {
            double new_activation = (j/255.0);
            Layers.at(0).Neurons.at(stepper).activation = new_activation;
            // cout << Layers.at(0).Neurons.at(stepper).activation << ' ';
            ++stepper;
        }
        // cout << endl;
    }

    int guess = forward_propagation();
    return guess;
}

/** Public function that runs forward propagation on the Network. Returns the result of running
 *  the propagation. */
int Network::forward_propagation() {
    Layer* test = &(Layers.at(0));
    return forward_propagation(test, 0);
}

/** Helper function for forward propagation. Takes a layer CURR_LAYER, and an INDEX.
 *  If the CURR_LAYER is the output layer, then the result of guess_number is returned.
 *  Otherwise, */
int Network::forward_propagation(Layer* curr_layer, int index) {
    if (curr_layer == &Layers.at(Layers.size()-1)) {
        return Network::guess_number(curr_layer);
    }
    vector<double> activations;
    matrix_vector_mult(curr_layer, activations);
     // cout << "ACTIVATIONS" << endl;
     // cout << "before sig  " << "after sig" << endl;
     for (unsigned i = 0; i < activations.size(); ++i) { //add biases to activations
         activations.at(i) += sigmoid(curr_layer->Neurons.at(i).bias);
         // cout << activations.at(i) << "    ";
         Layers.at(index+1).Neurons.at(i).z = activations.at(i);
         activations.at(i) = sigmoid(activations.at(i));
         Layers.at(index+1).Neurons.at(i).activation = activations.at(i);
         // cout << activations.at(i) << endl;
     }
     // cout << endl << endl;
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

int Network::guess_number() {
    return guess_number(&(Layers.at(Layers.size()-1)));
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
double sigmoid(double x) {
    const double e = 2.71828;
    return 1.0 / (1.0 + pow(e,-x));
}

/** Takes derivative of a function F with an input X. Returns the output of f'(x). */
double derivation(double (*f)(double), double x) {
    double h = 1e-8;
    return (f(x + h) - f(x)) / h;
}

/*
double Network::ReLU(double x) {
    if (x < 0) {
        return 0;
    }
    else {
        return x;
    }
}
*/

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

void Network::train(vector<vector<unsigned>> image, int label) {

    unsigned stepper = 0;
    for (unsigned i = 0; i < image.size(); ++i) { //initialize acitvations of the input layer
        for (unsigned j = 0; j < image.at(i).size(); ++j) {
            double new_activation = (image.at(i).at(j)/255.0);
            Layers.at(0).Neurons.at(stepper).activation = new_activation;
            // cout << Layers.at(0).Neurons.at(stepper).activation << ' ';
            ++stepper;
        }
        // cout << endl;
    }

    forward_propagation();

    //assign the output layer's neurons' adjustment_activation
    compute_adjustments(&(Layers.at(Layers.size()-1)), label);
    back_propagation();
}

/** FIXME: add method header */
void Network::compute_adjustments(Layer* curr_layer, int label) {
    for (unsigned i = 0; i < curr_layer->Neurons.size(); ++i) {
        if (i == label) { // activation needs to be 1 at the correct neuron
            curr_layer->Neurons.at(i).adjustment_activation = curr_layer->Neurons.at(i).activation -1;
        }
        else { //activation needs to be 0 at the incorrect neurons
            curr_layer->Neurons.at(i).adjustment_activation = curr_layer->Neurons.at(i).activation -0;
        }
    }
}

/** FIXME: add method header */
void Network::back_propagation() {
    // back prop starts on last hidden layer, so the biases of the output layer need to be adjusted sooner
    adjust_bias(&(Layers.at(Layers.size()-1)));
    back_propagation(&(Layers.at(Layers.size()-2)), Layers.size()-2);
}

/** FIXME: add method header and complete back propagation helper functions
input: one of the network
back_propagation changes the weights and biases relative to the
*/
void Network::back_propagation(Layer* curr_layer, int index) {
    adjust_activation(curr_layer, index);

    adjust_weight(curr_layer, index);

    adjust_bias(curr_layer);

    if (index > 0) {
        back_propagation(&(Layers.at(index-1)), index - 1);
    }
}

/**
a(l-1) * sigmoid'(z(l)) * 2(adjustment_activation)
*/
void Network::adjust_weight(Layer* curr_layer, int index) {
    for (unsigned i = 0; i < curr_layer->adjacency_rows; ++i) {
        for (unsigned j = 0; j < curr_layer->adjacency_cols; ++j) {
            Layer* next_over = &(Layers.at(index+1));
            Neuron* right_neuron = &(next_over->Neurons.at(i));
            Neuron* left_neuron = &(curr_layer->Neurons.at(j));

            double dzdw = left_neuron->activation;
            double dadz = derivation(sigmoid, right_neuron->z);
            double dCda = 2*(right_neuron->adjustment_activation);
            curr_layer->adjacencyMatrix[i][j] -= dzdw * dadz * dCda;
            // cout << curr_layer->adjacencyMatrix[i][j] << ' ';
        }
        // cout << endl;
    }

}

/** Changes adjustment bias in each neuron in L. */
void Network::adjust_bias(Layer* l) {
    for (Neuron &n : l->Neurons) {
        n.bias -= derivation(sigmoid, n.z) * (2 * (n.adjustment_activation));
    }
}

void Network::adjust_activation(Layer* curr_layer, int index) {
    Layer *next_over = &(Layers.at(index + 1));
    double sum = 0;

    for (unsigned i = 0; i < curr_layer->Neurons.size(); ++i) { //for each neuron in curr_layer
        for (unsigned j = 0; j < next_over->Neurons.size(); ++j) { //for each neuron's connection
            Neuron *right_neuron = &(next_over->Neurons.at(j));
            Neuron *left_neuron = &(curr_layer->Neurons.at(i));

            double dzda = curr_layer->adjacencyMatrix[j][i]; //dzda = correspoding weight to each connection
            double dadz = derivation(sigmoid, right_neuron->z);
            double dCda = 2 * (right_neuron->adjustment_activation);
            sum += dzda * dadz * dCda;
        }
        sum /= next_over->Neurons.size();
        curr_layer->Neurons.at(i).adjustment_activation = sum;
        sum = 0;
    }
}

void Network::print_output_activations() {
    Layer* output_layer = &(Layers.at(Layers.size()-1));

    cout << "OUTPUT ACTIVATIONS" << endl;
    for (Neuron & n : output_layer->Neurons) {
        cout << n.activation << ' ';
    }
    cout << endl;
    cout << endl;
}

/** Serializes network to file with name NAME. */
void Network::serialize(string name) {
    ofstream f (name);
    for (Layer &l : Layers) {
        if (l.adjacencyMatrix != nullptr) {
            for (int i = 0; i < sizeof(l.adjacencyMatrix); i++) {
                for (int j = 0; j < sizeof(l.adjacencyMatrix[i]); j++) {
                    f << l.adjacencyMatrix[i][j] << " ";
                }
            }
        }
    }
    f << endl;
    for (Layer &l : Layers) {
        for (Neuron &n : l.Neurons) {
            f << n.bias << " ";
        }
    }
    f.close();
}

/** Deserializes network from file with name NAME. */
void Network::deserialize(string name) {
    ifstream f (name);
    string line;
    queue<double> weights;
    queue<double> biases;
    if (f.is_open()) {
        getline(f, line); // Get weights
        double weight;
        stringstream weightIss (line);
        while (weightIss >> weight) {
            weights.push(weight);
        }

        getline(f, line); // Get biases
        double bias;
        stringstream biasIss (line);
        while (biasIss >> bias) {
            biases.push(bias);
        }
    }

    for (Layer l : Layers) {
        if (l.adjacencyMatrix != nullptr) {
            for (int i = 0; i < sizeof(l.adjacencyMatrix); i++) {
                for (int j = 0; j < sizeof(l.adjacencyMatrix[i]); j++) {
                    l.adjacencyMatrix[i][j] = weights.front();
                    weights.pop();
                }
            }
        }
    }

    for (Layer &l : Layers) {
        for (Neuron &n : l.Neurons) {
            n.bias = biases.front();
            biases.pop();
        }
    }
}

unsigned Network::layer_size() {
    return Layers.size();
}
