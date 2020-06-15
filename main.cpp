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

/** Takes in pass-by-reference IMAGES 3D array and plots the images. */
void writeToFile(unsigned ***images) {
    FILE * f = fopen("out.ppm", "wb");
    for (int i = 0; i < sizeof(images); i++) {
        for (unsigned int row = 0; row < sizeof(images[i]); row++) {
            for (unsigned int col = 0; col < sizeof(images[i][row]); col++) {
                cout << images[i][row][col];
                    fputc(images[i][row][col], f);
            }
        }
    }
    fclose(f);
}

/** Main Function to parse through training information from MNIST data. */
int main() {
    ifstream icin;
    icin.open("train/t10k-images.idx3-ubyte", ios::binary);
    magic = in(icin, 4);
    num = in(icin, 4);
    rows = in(icin, 4);
    cols = in(icin, 4);
    unsigned ***images;

    for (unsigned k = 0; k < 2000; ++k) {
        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j=0; j < cols; ++j) {
                images[k][i][j] = in(icin, 1);
                // cout << image[k][i][j] << ' ';
            }
            // cout << endl;
        }
    }

    writeToFile(static_cast<unsigned int ***>(images));
    
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

    cout << endl;
    cout << endl;
    icin.close();

    Network new_network;
    vector<vector<unsigned int> > test_image;
    test_image.resize(rows);
    for (unsigned i = 0; i < rows; ++i) {
        test_image.at(i).resize(cols);
    }
    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            test_image.at(i).at(j) = images[0][i][j];
        }
    }
    new_network.guessImage(test_image);

    return 0;
}
