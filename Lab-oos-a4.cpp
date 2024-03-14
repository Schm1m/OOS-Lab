
#include <iostream>
using namespace std;
int function(int i_1) {
    cout << "Funktion  1: i_1=" << i_1 << endl;
    return 0;
}
//void function(int i_1) { cout << "Funktion  2: i_1=" << i_1 << endl; }

// only difference is return value

/*
char function(int i_1) {
    cout << "Funktion  3: i_1=" << i_1 << endl;
    return 'a';
}
*/
/*
// same as function 1
int function(int& i_1) {
    cout << "Funktion  4: i_1=" << i_1 << endl;
    return 1;
}
*/
int function(int i_1, int i_2) {
    cout << "Funktion  5: i_1=" << i_1 << " i_2=" << i_2 << endl;
    return 1;
}
int function(char c_1, int i_1) {
    cout << "Funktion  6: c_1=" << c_1 << " i_1=" << i_1 << endl;
    return 1;
}
/*
// same as with function 2/3
int function(int i_1, int i_2 = 0) {
    cout << "Funktion  7: i_1=" << i_1 << " i_2=" << i_2 << endl;
    return 1;
}
*/
int function(double d_1, int i_1, char c_1 = 'a') {
    cout << "Funktion  8: d_1=" << d_1 << " i_1=" << i_1 << " c_1=" << c_1
         << endl;
    return 1;
}
int function(double d_1, double d_2 = 1.1, int i_1 = 0) {
    cout << "Funktion  9: d_1=" << d_1 << " d_2=" << d_2 << " i_1=" << i_1
         << endl;
    return 1;
}
/*
// char c_1 has no default value but d_2 has?
int function(double d_1, double d_2 = 1.1, char c_1) {
    cout << "Funktion 10: d_1=" << d_1 << " d_2=" << d_2 << " c_1=" << c_1
         << endl;
    return 1;
}
*/
int function(char c_1, char c_2, int i_1 = 2, char c_3 = 'c') {
    cout << "Funktion 11: c_1=" << c_1 << " c_2=" << c_2 << " i_1=" << i_1
         << " c_3=" << c_3 << endl;
    return 1;
}
int main(int argc, char* argv[]) {
    // comment behind line corresponds to function called
    int i = 1;
    char c = 'a';
    function(1); // 1
    function(c); // 1
    function(i); // 1
    c = function('a'); // 1
    c = 'a';
    function(1, 2); // 5
    function(c, i); // 6
    function(1.0, 2.0); // 9
    function(1.0, 2.0, 1); // 9
    function(1.0, 1, 'a');  // 8
    function(1.0, 1); // 8
    function(1.0, static_cast<double>(i)); // 9
    function(c, c, i); // 11
    function(c, i); // 6
    return 0;
}