
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

int main(void) {
    double d = 1.234;
    cout << " Nr Oct  Hex String  Fixed     Scientific " << endl;
    for (int k = 1; k < 11; k++) {
        cout << setfill(' ') << setw(3) << noshowpos << nouppercase << showbase
             << right << dec << k;
        cout << setw(4) << oct << k;
        cout << setw(5) << hex << k << " ";
        cout << setw(7) << left << setfill('+') << string(k % 5 + 1, '*')
             << " ";
        cout << setw(9) << setfill(' ') << fixed << internal << setprecision(3)
             << showpos << d;
        cout << setw(11) << noshowpos << uppercase << right << scientific << d;
        d = d * -2;

        cout << endl;
    }
    return 0;
}
