#include <iostream>
#include <fstream>
<<<<<<< HEAD
#include <stdio.h>
#include <vector>
#include "Neuron.h"
#include "Network.h"

using namespace std;

const int MAXN = 6e4 + 7;
unsigned int num, magic, rows, cols;
unsigned int label[MAXN];

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

//void writeToFile(unsigned (*images)[rows][cols]) {
//    FILE * f = fopen("out.ppm", "wb");
//    for (unsigned int row = 0; row < sizeof(images[i]); row++) {
//        for (unsigned int col = 0; col < sizeof(images[i][row]); col++) {
//            cout << images[i][row][col];
//                fputc(images[i][row][col], f);
//        }
//    }
//    fclose(f);
//}

int main() {
    ifstream icin;
    icin.open("train/t10k-images.idx3-ubyte", ios::binary);
    magic = in(icin, 4);
    num = in(icin, 4);
    rows = in(icin, 4);
    cols = in(icin, 4);

    vector<vector<vector<unsigned>>> images;

    for (unsigned k = 0; k < 10000; ++k) {
        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j = 0; j < cols; ++j) {
                images = in(icin, 1);
                cout << images[k][i][j] << ' ';
            }
            // cout << endl;
        }
    }
    
    
//    writeToFile(&images[0]);
    
//    cout << images;
//    writeToFile();
    
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

    return 0;
}
