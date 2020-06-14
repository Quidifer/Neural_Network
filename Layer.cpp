#include "Layer.h"
#include <climits>
#include <ctime>
#include <cstdlib>

using namespace std;

Layer::~Layer() {
    while (Neurons.size() > 0) {
        Neurons.pop_back();
    }
}

void Layer::construct(int num_neurons) {
    for (int i = 0; i < num_neurons; ++i) {
        Neuron new_neuron;
        new_neuron.bias = fRand(-10,10);
    }
}

double Layer::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
