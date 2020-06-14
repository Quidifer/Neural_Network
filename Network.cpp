#include "Network.h"
#include <climits>
#include <ctime>
#include <cstdlib>

using namespace std;

Network::Network() {
    for (unsigned i = 0; i < num_layers; ++i) {
        Layer new_Layer;
        if (i == 0) {
            new_Layer.construct(num_pixels);
        }
        else if (i == num_layers - 1) {
            new_Layer.construct(10);
        }
        else {
            new_Layer.construct(hidden_layer_size);
        }

        Layers.push_back(new_Layer);
    }
}

double Network::fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
