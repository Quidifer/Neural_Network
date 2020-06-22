#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <vector>
#include "Layer.h"
#include <string>

const static int num_pixels = 784;

//const int num_layers = 4;
//const int num_hidden_layers = 2;
//const int hidden_layer_size = 16;


class Network {
public:
    static int guessImage(vector<vector<unsigned int>>);
    static int forward_propagation();
    static void train(vector<vector<unsigned>>, int);
    static void setup(int num_layers=6, int hidden_layer_size=10);
    static double fRand(double, double);
    static void print_output_activations();
    static int guess_number();
    static void serialize(string name);
    static void deserialize(string name);
private:
    static int forward_propagation(Layer*, int);
    static void matrix_vector_mult(Layer*, vector <double> &);
    static int guess_number(Layer*);
    static double Cost(Layer*);
    static void compute_adjustments(Layer*, int);
    static void back_propagation();
    static void back_propagation(Layer*, int);
    static void adjust_weight(Layer*, int);
    static void adjust_bias(Layer*);
    static void adjust_activation(Layer*, int);
};

#endif
