#include <iostream>
#include <fstream>
#include <vector>
#include "Neuron.h"
#include "Network.h"
#include "Layer.h"
#include <string>

using namespace std;

const int MAXN = 6e4 + 7;
unsigned int num, magic, rows, cols;
// unsigned int label[MAXN];

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
    string output_file = "training_sets/network_4_25";
    ifstream serializedFile (output_file);
    ifstream imagein;
    ifstream labelin;
    imagein.open("train/train-images.idx3-ubyte", ios::binary);
    labelin.open("train/train-labels.idx1-ubyte", ios::binary);
    magic = in(imagein, 4);
    num = in(imagein, 4);
    rows = in(imagein, 4);
    cols = in(imagein, 4);

    if (serializedFile) {
        Network::deserialize(output_file);
    }
    else {
        Network::setup();
    }

    vector<vector<unsigned>> images;
    unsigned label;
    images.resize(28);
    for (unsigned i = 0; i < images.size(); ++i) {
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
                // cout << j << ' ';
            }
            // cout << endl;
        }

        label = in(labelin, 1); // input a corresponding label
        // cout << "Label: " << label << endl << endl;
        if (i < 60000 - 1000 && !serializedFile) {
            Network::train(images, label);
            int guess = Network::guess_number();
            ++num_training_guesses;
            if (guess == label) {
                ++num_training_correct;
            }

            if (i % 100 == 0) {

                cout << i << " iterations!! ";
                cout << "percentange correct: " << num_training_correct/num_training_guesses << endl;
                // cout << "layer_size: " << Network::layer_size() << endl;
                if (i % 1000 == 0) {
                    num_training_correct = 0;
                    num_training_guesses = 0;
                    cout << "\t \t Resetting correct percentage." << endl;
                }
            }
        }

        else {
            ++num_guesses;
            double answer = Network::guessImage(images);
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
    Network::serialize(output_file);
   return 0;
}
