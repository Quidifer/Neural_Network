#include <iostream>
#include <fstream>
#include <vector>
#include "Neuron.h"
#include "Network.h"
#include "Layer.h"
#include "Network_ReLU.h"
#include <string>

using namespace std;

const int MAXN = 6e4 + 7;
unsigned int num, magic, rows, cols;

/** Takes in a stream ICIN and a SIZE and returns the decimal number present at the given position in
    the stream. */
unsigned int in(ifstream& icin, unsigned int size) {
    unsigned int ans = 0;
    for (int i = 0; i < size; i++) {
        unsigned char x;
        icin.read((char*)&x, 1);
        unsigned int temp = x;
        ans <<= 8;
        ans += temp;
    }
    return ans;
}

/** Main Function to parse through training information from MNIST data. */
int main() {
    cout << "This file trains and test networks using the ReLU activation function" << endl;
    char input;
    while (input != 'y' && input != 'n') {
        cout << "Would you like to continue? y/n: " << endl;
        cin >> input;
        cout << endl;
        if (input == 'n') {
            return 1;
        }
    }
    cout << endl;

    string output_file = "training_sets_ReLU/";
    if (output_file == "training_sets_ReLU/") {
        cout << "Waiting for output file name. Type existing file or name of new file: ";
        string input;
        cin >> input;
        output_file += input;
    }
    cout << endl;

    ifstream serializedFile (output_file);
    bool train = true;
    if (serializedFile) {
        while (input != 't' && input != 's' && input != 'q') {
            cout << output_file << " already exists. Type 't' to continue training or 's' to test the serialized network.\n"
            << "Type 'q' to quit: ";
            cin >> input;
            if (input == 'q') {
                return 1;
            }
            else if (input == 's') {
                train = false;
            }
        }

    }
    else {
        cout << output_file << " is a new file" << endl;
    }

    if (train) {
        cout << "training network..." << endl;
    }
    else {
        cout << "testing serialized network..." << endl;
    }

    ifstream imagein;
    ifstream labelin;
    imagein.open("train/train-images.idx3-ubyte", ios::binary);
    labelin.open("train/train-labels.idx1-ubyte", ios::binary);
    magic = in(imagein, 4);
    num = in(imagein, 4);
    rows = in(imagein, 4);
    cols = in(imagein, 4);

    if (serializedFile) {
        Network_ReLU::deserialize(output_file);
    }
    else {
        int num_layers;
        int hidden_layer_size;
        cout << "input number of layers including hidden and output layers: ";
        cin >> num_layers;
        cout << endl;
        cout << "input number of neurons in each hidden layer (due to slow computations, 50 or more neurons will have slow run times): ";
        cin >> hidden_layer_size;
        cout << endl;
        Network_ReLU::setup(num_layers, hidden_layer_size);
    }

    vector<vector<unsigned>> images;
    unsigned label;
    images.resize(28);
    for (unsigned i = 0; i < images.size(); ++i) { //setup image size
        images.at(i).resize(28);
    }

    magic = in(labelin, 4);
    num = in(labelin, 4);

    double num_guesses = 0;
    double num_correct = 0;

    double num_training_guesses = 0;
    double num_training_correct = 0;
    for (unsigned i = 0; i < 60000; ++i) { //for 60,000 images
        for (vector<unsigned> &i : images) { //input an image
            for (unsigned &j : i) {
                j = in(imagein, 1);
            }
        }
        label = in(labelin, 1); // input a corresponding label

        if (i < 60000 - 1000 && train) {
            Network_ReLU::train(images, label);
            int guess = Network_ReLU::guess_number();
            ++num_training_guesses;
            if (guess == label) {
                ++num_training_correct;
            }

            if (i % 100 == 0) {

                cout << i << " iterations!! ";
                cout << "percentange correct: " << num_training_correct/num_training_guesses << endl;
                if (i % 1000 == 0) {
                    num_training_correct = 0;
                    num_training_guesses = 0;
                    cout << "\t \t Resetting percentage..." << endl;
                }
            }
        }

        else {
            ++num_guesses;
            double answer = Network_ReLU::guessImage(images);
//            cout << answer
//            << "  Correct label: " << label << endl;
//            Network::print_output_activations();
//            cout << endl << endl;

            if (answer == label) {
                ++num_correct;
            }
        }
    }

    cout << "Accuracy of network: " << num_correct / num_guesses << endl;
    cout << endl;

    input = 'z';
    while (input != 'y' && input != 'n') {
        cout << "Would you like to save this training set? y/n: ";
        cin >> input;
        cout << endl;
        if (input == 'y') {
            Network_ReLU::serialize(output_file);
        }
    }

   return 0;
}
