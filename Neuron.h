#ifndef _NEURON_H_
#define _NEURON_H_

using namespace std;

struct Neuron {
    double activation; // input
    double z; // activation prior to sigmoid function
    double bias; // better fit data
    double adjustment_activation; // change by for BP
    double adjustment_bias;
    Neuron(): activation(0) {}
};

#endif
