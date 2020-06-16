#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <vector>
#include "Layer.h"

const static int num_pixels = 784;

//const int num_layers = 4;

//const int num_hidden_layers = 2;
//const int hidden_layer_size = 16;


class Network {
private:
    //size 4
    //input layer
    //2 hidden layers
    //output layer
public:
    static int guessImage(vector<vector<unsigned int>>);
    static int forward_propagation();
    static void train(int label, unsigned image[28][28]);
    static void setup(int num_layers=4, int hidden_layer_size=16);
private:
    static double fRand(double, double);
    static int forward_propagation(Layer*, int);
    static void matrix_vector_mult(Layer*, vector <double> &);
    static double sigmoid(double);
};

#endif
