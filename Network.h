#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <vector>
#include "Layer.h"

const static int num_pixels = 784;

//const int num_layers = 4;

//const int num_hidden_layers = 2;
//const int hidden_layer_size = 16;


class Network {
public:
    static int guessImage(vector<vector<unsigned int>>);
    static int forward_propagation();
    static void train(int label, unsigned image[28][28]);
    static void setup(int num_layers=4, int hidden_layer_size=16);
    static double fRand(double, double);
private:
    static int forward_propagation(Layer*, int);
    static void matrix_vector_mult(Layer*, vector <double> &);
    static double sigmoid(double);
    static int guess_number(Layer*);
    static double Cost(Layer*);
    static void compute_adjustments(Layer*, int);
    static void back_propagation();
    static void back_propagation(Layer* curr_layer, int index);
};

#endif
