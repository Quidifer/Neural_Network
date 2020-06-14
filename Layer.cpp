#include "Layer.h"

using namespace std;

Layer::~Layer() {
    while (Neurons.size() > 0) {
        Neurons.pop_back();
    }
}
