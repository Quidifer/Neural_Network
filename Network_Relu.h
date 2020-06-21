#ifndef _NETWORK_RELU_H_
#define _NETWORK_RELU_H_

#include <vector>
#include "Layer.h"
#include <string>

class Network_ReLU: public Network {
public:
    static void print_output_activations();
private:
    static int forward_propagation(Layer*, int);
    static void adjust_weight(Layer*, int);
    static void adjust_bias(Layer*);
    static void adjust_activation(Layer*, int);
    static int get_max(Layer *);
};

#endif
