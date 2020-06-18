#include <iostream>
#include <fstream>
#include <vector>
#include "Neuron.h"
#include "Network.h"
#include "Layer.h"

using namespace std;

const int MAXN = 6e4 + 7;
unsigned int num, magic, rows, cols;
unsigned int label[MAXN];

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
    ifstream icin;
    icin.open("train/t10k-images.idx3-ubyte", ios::binary);
    magic = in(icin, 4);
    num = in(icin, 4);
    rows = in(icin, 4);
    cols = in(icin, 4);
    unsigned images[2000][28][28];
    for (unsigned k = 0; k < 2000; ++k) {
        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j=0; j < cols; ++j) {
                images[k][i][j] = in(icin, 1);
//                 cout << images[k][i][j] << ' ';
            }
            // cout << endl;
        }
    }

//    writeToFile(images);
    // cout << magic << endl;
    // cout << num << endl;
    // cout << rows << endl;
    // cout << cols << endl;
    icin.close();

    icin.open("train/t10k-labels.idx1-ubyte", ios::binary);
    magic = in(icin, 4);
    num = in(icin, 4);

    for (unsigned i = 0; i < num; ++i) {
        label[i] = in(icin, 1);
        // cout << label[i] << ' ';
    }

//    cout << endl;
//    cout << endl;
    icin.close();

    Network::setup();
    vector<vector<unsigned int>> test_image;
    test_image.resize(rows);
    for (unsigned i = 0; i < rows; ++i) {
        test_image.at(i).resize(cols);
        for (unsigned j = 0; j < )
    }
    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            test_image.at(i).at(j) = images[0][i][j];
        }
    }
    Network::train(test_image, label[0]);
//    Network::serialize("out");
//    Network::deserialize("out");
    return 0;
}
