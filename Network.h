#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <vector>
#include "Layer.h"

const int num_pixels = 784;

const int num_layers = 4;

const int num_hidden_layers = 2;
const int hidden_layer_size = 16;


class Network {
private:
    //size 4
    //input layer
    //2 hidden layers
    //output layer
    vector<Layer> Layers;
public:
    Network();
    ~Network();
    int guessImage(vector<vector<unsigned int>>);
    void train(vector<vector<unsigned>>, int);
private:
    double fRand(double, double);

    int forward_propagation();
    int forward_propagation(Layer*, int);

    void matrix_vector_mult(Layer*, vector <double> &);
    int guess_number(Layer*);
    double sigmoid(double);

    double Cost(Layer*, int);
    void compute_adjustments(Layer*, int);
    void back_propagation();
    void back_propagation(Layer* curr_layer, int index);

};

#endif
