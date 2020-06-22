#include "Network_Relu.h"
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

//definitions
double ReLU(double);
double derivation(double (*f)(double), double x);

/** ReLU activation function. Simple, but effective. Adheres different reselts
*   when using this function instead of sigmoid. */
double ReLU(double x) {
    if (x < 0) {
        return 0;
    }
    else {
        return x;
    }
}

/** Takes derivative of a function F with an input X. Returns the output of f'(x). */
double derivation(double (*f)(double), double x) {
    double h = 1e-8;
    return (f(x + h) - f(x)) / h;
}

/** Extra function added for ReLU. When computing activation_adjustment for the output layer, compute_adjustments()
*   needs to find the maximum activation in the output layer. The cost function used for ReLU is as follows:
*
*   C = (activation - get_max(output_layer))^2 <-- for the neuron corresponding to the correct label
*   C = (activation - 0)^2 <-- for the neuron corresponding to an incorrect label
*   *then add all Cs together to get the cost*   */
int Network_ReLU::get_max(Layer* output_layer) {
    int max = 0;
    for (Neuron & n : output_layer->Neurons) {
        if (n.activation > max) {
            max = n.activation;
        }
    }
    return max;
}


//The remainder functions are overloaded functions that require ReLU to be used instead of sigmoid
//method headers for those functions are in Network.cpp

int Network_ReLU::forward_propagation(Layer* curr_layer, int index) {
    if (curr_layer == &Layers.at(Layers.size()-1)) {
        return Network::guess_number(curr_layer);
    }
    vector<double> activations;
    matrix_vector_mult(curr_layer, activations);
     // cout << "ACTIVATIONS" << endl;
     // cout << "before sig  " << "after sig" << endl;
     for (unsigned i = 0; i < activations.size(); ++i) { //add biases to activations
         activations.at(i) += ReLU(curr_layer->Neurons.at(i).bias);
         // cout << activations.at(i) << "    ";
         Layers.at(index+1).Neurons.at(i).z = activations.at(i);
         activations.at(i) = ReLU(activations.at(i));
         Layers.at(index+1).Neurons.at(i).activation = activations.at(i);
         // cout << activations.at(i) << endl;
     }
     // cout << endl << endl;
    return forward_propagation(&(Layers.at(index+1)), index + 1);
}

void Network_ReLU::compute_adjustments(Layer* curr_layer, int label) {
    int max = get_max(curr_layer);
    for (unsigned i = 0; i < curr_layer->Neurons.size(); ++i) {
        if (i == label) { // activation needs to be 1 at the correct neuron
            curr_layer->Neurons.at(i).adjustment_activation = curr_layer->Neurons.at(i).activation -max;
        }
        else { //activation needs to be 0 at the incorrect neurons
            curr_layer->Neurons.at(i).adjustment_activation = curr_layer->Neurons.at(i).activation -0;
        }
    }
}

/** Overloaded functions for adjusting weights and biases using ReLU*/
void Network_ReLU::adjust_weight(Layer* curr_layer, int index) {
    for (unsigned i = 0; i < curr_layer->adjacency_rows; ++i) {
        for (unsigned j = 0; j < curr_layer->adjacency_cols; ++j) {
            Layer* next_over = &(Layers.at(index+1));
            Neuron* right_neuron = &(next_over->Neurons.at(i));
            Neuron* left_neuron = &(curr_layer->Neurons.at(j));

            double dzdw = left_neuron->activation;
            double dadz = derivation(ReLU, right_neuron->z);
            double dCda = 2*(right_neuron->adjustment_activation);
            curr_layer->adjacencyMatrix[i][j] -= dzdw * dadz * dCda;
            // cout << curr_layer->adjacencyMatrix[i][j] << ' ';
        }
        // cout << endl;
    }

}
void Network_ReLU::adjust_bias(Layer* l) {
    for (Neuron &n : l->Neurons) {
        n.bias -= derivation(ReLU, n.z) * (2 * (n.adjustment_activation));
    }
}
void Network_ReLU::adjust_activation(Layer* curr_layer, int index) {
    Layer *next_over = &(Layers.at(index + 1));
    double sum = 0;

    for (unsigned i = 0; i < curr_layer->Neurons.size(); ++i) { //for each neuron in curr_layer
        for (unsigned j = 0; j < next_over->Neurons.size(); ++j) { //for each neuron's connection
            Neuron *right_neuron = &(next_over->Neurons.at(j));
            Neuron *left_neuron = &(curr_layer->Neurons.at(i));

            double dzda = curr_layer->adjacencyMatrix[j][i]; //dzda = corresponding weight to each connection
            double dadz = derivation(ReLU, right_neuron->z);
            double dCda = 2 * (right_neuron->adjustment_activation);
            sum += dzda * dadz * dCda;
        }
        sum /= next_over->Neurons.size();
        curr_layer->Neurons.at(i).adjustment_activation = sum;
        sum = 0;
    }
}
