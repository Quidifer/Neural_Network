# Usage

compile the program under the sigmoid activation function.
```bash
make
```

<br>

compile under the ReLU activation function.
```bash
make TYPE=RELU
```

# Digit Classifier

A multilayered neural network to analyze handwritten digits. Uses MNIST data for training.
Written entirely in C++ from scratch.

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
forwards and backwards propagation on the network. Essentially
manages all the layers from a global perspective.

## Notes to Reader
This neural network is very much a rudimentary project that we put together in C++. In our own tests and training,
our best network reads the MNIST training data with a 93% accuracy. That serialized network can be found under
training_sets_sigmoid/network_4_25. (4 meaning 4 layers, including input and output layers. 25 meaning 25 Neurons
in the hidden layers).

We do not use epochs/ mini-batches. For this project, we were not as focused on the runtime of our program.
Instead, we focused on the way a neural network learns through back propagation. Our network adjusts its
weights and biases each time we run backpropagation on an image. We understand that this significantly effects
the runtime, and will attempt using mini batches in our upcoming projects.
 
# Relevent Calculus Behind Back Propogation 
 ![alt text](https://raw.githubusercontent.com/Quidifer/Neural_Network/master/math-page-001.jpg)
 
 
## Authors
* **Anderson Tsai**  - [Github](https://github.com/anderson-tsai)
* **Brad Byun**  - [Github](https://github.com/bhbyun1)
* **Kevin Tu**  - [Github](https://github.com/kevin20201)
* **Christopher Mouri**  - [Github](https://github.com/quidifer)
