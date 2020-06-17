# Digit Classifier

A 3-layer neural network to analyze handwritten digits. Uses MNIST data for training.
Written entirely in C++.

## Classes
### Neuron
Represents a neuron in the neural net. Each neuron object stores an activation,
bias, adjustment activation, and adjustment bias variable.

### Layer
Represented by a vector of neurons. Contains adjacency matrix with labels of 
neurons in the current layer on one axis, and labels of neurons in the 
following layer on the other axis. The adjacency matrix contains weights of the
edges connecting any two neurons from one layer to the following layer.

### Network
Static-typed class that stores information regarding each layer. Computes
forwards propagation and backwards propagation of the network. Essentially 
manages all the layers from a global perspective.

## Authors
* **Anderson Tsai**  - [Github](https://github.com/anderson-tsai)
* **Brad Byun**  - [Github](https://github.com/bhbyun1)
* **Kevin Tu**  - [Github](https://github.com/kevin20201)
* **Christopher Mouri**  - [Github](https://github.com/quidifer)



