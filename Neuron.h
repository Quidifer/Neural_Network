#ifndef _NEURON_H_
#define _NEURON_H_

using namespace std;

struct Neuron {
    double activation; // input
    double z; // activation prior to sigmoid function/ ReLU function
    double bias; // better fit data

    double adjustment_activation; // change by for Back prop
    /*   The adjustment_activation variable refers to the derivative of the Cost function,
    *   with respect to activation.
    *
    *   For example: Given any given neuron from the network.
    *   That neuron's activation -= adjustment_activation should give the desired activation for
    *   that neuron. */

    Neuron(): activation(0) {}
};

#endif
