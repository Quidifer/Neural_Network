#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 6e4 + 7;
unsigned int image[MAXN][30][30];
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


int main() {
    ifstream icin;
    icin.open("train/t10k-images.idx3-ubyte", ios::binary);
    magic = in(icin, 4);
    num = in(icin, 4);
    rows = in(icin, 4);
    cols = in(icin, 4);

    unsigned image[rows][cols];

    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j=0; j < cols; ++j) {
            image[i][j] = in(icin, 1);
            cout << image[i][j] << ' ';
        }
        cout << endl;
    }

    cout << magic << endl;
    cout << num << endl;
    cout << rows << endl;
    cout << cols << endl;
    icin.close();

    icin.open("train/t10k-labels.idx1-ubyte", ios::binary);
    magic = in(icin, 4);
    num = in(icin, 4);
    unsigned first;
    first = in(icin, 1);

    cout << magic << endl;
    cout << first << endl;
    icin.close();

    return 0;
}
