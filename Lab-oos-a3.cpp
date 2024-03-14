#include <iostream>
using namespace std;
void print_rectangle(int a, int b = 0) {
    if(b == 0) {
        b = a; // if parameter b defaults to 0 (no parameter given), b gets set to a
    }
    for(int i = 0; i < b; i++) { // loop through all "x"´s to print
        for(int j = 0; j < a; j++) {
            cout << "X ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
	cout << "x = 2, y = 5: " << endl;
	print_rectangle(2, 5);

	cout << "x = 3, y = 3: " << endl;
	print_rectangle(3, 3);

	cout << "x = 4: " << endl;
	print_rectangle(4);

	return 0;
};

