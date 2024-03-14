
#include<iostream>
using namespace std;

// hier die Klasse Punkt implementieren

class Point {
    private:
    // private vars, so you can only change them with their corresponding functions
    int x, y;

    public:
    // public functions to change values
    void set_x(int _x) {
        x = _x;
    }
    void set_y(int _y) {
        y = _y;
    }
    int get_x() {
        return x;
    }
    int get_y() {
        return y;
    }
    void print() {
        cout << "print-Methode:" << endl;
        cout << "X = " << x << endl;
        cout << "Y = " << y << endl;
    }
};



int main(int argc, char* argv[]) {
    Point p;
    p.set_x(1);
    p.set_y(10);
    p.print();
    p.set_x(5);
    cout << "X ohne print(): " << p.get_x() << endl;
    cout << "Y ohne print(): " << p.get_y() << endl;
    return 0;
}

