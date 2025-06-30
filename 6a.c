#include <iostream>
using namespace std;

void generateHammingCode(int data[4], int code[7]) {
code[2]=data[0];
code[4]=data[1];
code[5]=data[2];
code[6]=data[3];

code[0]=code[2]^code[4]^code[6];
code[1]=code[2]^code[5]^code[6];
code[3]=code[4]^code[5]^code[6];
}

void checkHammingCode(int received[7]) {
    int p1=received[0]^received[2]^received[4]^received[6];
    int p2=received[1]^received[2]^received[5]^received[6];
    int p4=received[3]^received[4]^received[5]^received[6];

    int error=p1*1+p2*2+4*p4;
    if (error == 0) {
        cout << "No error detected.\n";
    } else {
        cout << "Error detected at position: " << error << "\n";
        received[error-1]^=1;
        cout << "Corrected code: ";
        for (int i = 0; i < 7; i++) {
            cout << received[i];
        }
        cout << "\n";
    }

}


int main() {
    int data[4], code[7], received[7];

    cout << "Enter 4-bit data (space-separated): ";
    for (int i = 0; i < 4; i++) {
        cin >> data[i];
    }

     generateHammingCode(data, code);

    cout << "Encoded Hamming code: ";
    for (int i = 0; i < 7; i++) {
        cout << code[i];
    }
    cout << "\n";

    cout << "Enter received 7-bit code (space-separated): ";
    for (int i = 0; i < 7; i++) {
        cin >> received[i];
    }

   checkHammingCode(received);

    return 0;
}
