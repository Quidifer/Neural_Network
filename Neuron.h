#ifndef _NEURON_H_
#define _NEURON_H_

using namespace std;

struct Neuron {
    double activation;
    double bias;
    double adjustment_activation;
    double adjustment_bias;
    Neuron(): activation(0) {}
};

#endif
