#include "Network.h"
#include "Layer.h"
#include <climits>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
constructor
creates a neural network with biases of each neuron set to 0
and random weights between -1 and 1.
There are 4 layers in total
    1 input layer of 784 nodes to represent all pixels in the initial image
    2 hidden layers, each with 16 nodes each
    1 output layer with ten nodes representing the answers for 0-9
*/
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

/*
Destructor
destroys all Layers within the network
*/
Network::~Network() {
    while(Layers.size() > 0) {
        Layers.pop_back();
    }
}

/*
input: 2d vector of a 28x28 grayclase image of a handwritten number. Pixels are between 0 and 255
guess the image of the given input. 28x28 grayscale image of a handwritten number
*/
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

    int guess = forward_propagation();
    return guess;
}

void Network::train(vector<vector<unsigned>> image, int label) {
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

    forward_propagation();

    compute_adjustments(&(Layers.at(Layers.size()-1)), label);

    back_propagation();
}

/*
public function for forward propagation
*/
int Network::forward_propagation() {
    Layer* test = &(Layers.at(0));
    return forward_propagation(test, 0);
}

/*
recursive function that calculates all the weights in the Neural Network
*/
int Network::forward_propagation(Layer* curr_layer, int index) {
    if (curr_layer == &Layers.at(Layers.size()-1)) {
        return guess_number(curr_layer);
    }
    vector<double> activations;
     matrix_vector_mult(curr_layer, activations);

     cout << "ACTIVATIONS" << endl;
     cout << "before sig  " << "after sig" << endl;
     for (unsigned i = 0; i < activations.size(); ++i) { //add biases to activations
         activations.at(i) += curr_layer->Neurons.at(i).bias;
         cout << activations.at(i) << "    ";
         activations.at(i) = sigmoid(activations.at(i));
         Layers.at(index+1).Neurons.at(i).activation = activations.at(i);
         cout << activations.at(i) << endl;
     }
     cout << endl << endl;

    return forward_propagation(&(Layers.at(index+1)), index + 1);

}

/*
matrix vector multiplication for calculating the activations based on one adjacency matrix
*/
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

/*
input: pointer to the output layer
output: guess of what the neural network thinks the number is
*/
int Network::guess_number(Layer* output_layer) {
    int max = 0;
    for (unsigned i = 0; i < output_layer->Neurons.size(); ++i) { //get the max activation index
        if (output_layer->Neurons.at(i).activation > output_layer->Neurons.at(max).activation) {
            max = i;
        }
    }
    return max;
}

/*
simple sigmoid function
used for squishing down activations between 0 and -1
*/
double Network::sigmoid(double x) {
    const double e = 2.71828;
    return 1.0 / (1.0 + pow(e,-x));
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

/*
get a random double between a min and max value
*/
double Network::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

/*
input: pointer to the output layer
output: return the cost of the Neural Network
*/
double Network::Cost(Layer* output_layer, int label) {
    double sum = 0;
    for (unsigned i = 0; i < output_layer->Neurons.size(); ++i) {
        double cost = pow(output_layer->Neurons.at(i).adjustment_activation,2);
        sum += cost;
    }
    return sum;
}

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

void Network::back_propagation() {
    back_propagation(&(Layers.at(Layers.size()-1)), Layers.size()-1);
}

void Network::back_propagation(Layer* curr_layer, int index) {}
