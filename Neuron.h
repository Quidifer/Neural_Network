#ifndef _NEURON_H_
#define _NEURON_H_

using namespace std;

struct Neuron {
    double activation;
    double z; //activation prior to sigmoid function
    double bias;
    double adjustment_activation;
    Neuron(): activation(0) {}
};

#endif
