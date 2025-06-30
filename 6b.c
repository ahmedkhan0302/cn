#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Check if a number is a power of 2
bool isPowerOfTwo(int x) {
    return x && (!(x & (x - 1)));
}

// Function to generate Hamming Code (even parity)
vector<int> generateHammingCode(const vector<int>& data) {
    int m = data.size();
    int r = 0;

    // Calculate number of parity bits
    while (pow(2, r) < (m + r + 1))
        r++;

    int totalBits = m + r;
    vector<int> code(totalBits + 1); // 1-based indexing

    // Fill data bits
    for (int i = 1, j = 0; i <= totalBits; i++) {
        if (isPowerOfTwo(i))
            code[i] = 0; // placeholder for parity
        else
            code[i] = data[j++];
    }

    // Calculate parity bits
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;
        for (int j = 1; j <= totalBits; j++) {
            if (j & pos)
                parity ^= code[j];
        }
        code[pos] = parity;
    }

    return code;
}

int main() {
    int n;
    cout << "Enter number of data bits: ";
    cin >> n;

    vector<int> data(n);
    cout << "Enter the data bits (LSB to MSB):\n";
    for (int i = n - 1; i >= 0; i--) {
        cout << "Bit " << i + 1 << ": ";
        cin >> data[i];
    }

    vector<int> hamming = generateHammingCode(data);

    cout << "\nGenerated Hamming Code (position 1 to " << hamming.size() - 1 << "):\n";
    for (int i = hamming.size() - 1; i >= 1; i--) {
        cout << hamming[i] << " ";
    }
    cout << "\n";

    return 0;
}
