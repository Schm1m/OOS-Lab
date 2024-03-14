#include <iostream>
using namespace std;

// Klasse Point und Circle implementieren

class Point {
    double _x;
    double _y;

   public:
    Point() {  // set default values for position in constructor
        this->_x = 0.0;
        this->_y = 0.0;
    }
    void print(bool if_endl = true) {
        switch (if_endl) {  // either print a new line or not based on the
                            // boolean input
            case false:
                cout << "(" << this->_x << ", " << this->_y << ")"
                     << flush;  // flush prints no new line
                break;
            default:
                cout << "(" << this->_x << ", " << this->_y << ")"
                     << endl;  // endl prints a new line
                break;
        }
    }

    void set_x(double _value) { this->_x = _value; }

    void set_y(double _value) { this->_y = _value; }

    double get_x() { return this->_x; }

    double get_y() { return this->_y; }

    void move(double _by_x, double _by_y) {  // add ipunt values to the existing
                                             // positions to move the point
        this->_x += _by_x;
        this->_y += _by_y;
    }
};

class Circle {
    Point _centre;
    double _radius;

   public:
    Circle(Point _set_centre) {  // set default values for position and radius
                                 // in constructor
        this->_centre = _set_centre;
        this->_radius = 1.0;
    }

    void print(bool if_endl = true) {  // either print a new line or not based
                                       // on the boolean input
        switch (if_endl) {
            case false:
                cout << "[(" << this->_centre.get_x() << ", "
                     << this->_centre.get_y() << "), " << this->_radius << "]"
                     << flush;  // flush prints no new line
                break;

            default:
                cout << "[(" << this->_centre.get_x() << ", "
                     << this->_centre.get_y() << "), " << this->_radius << "]"
                     << endl;  // endl prints a new line
                break;
        }
    }

    void set_centre(Point _point) { this->_centre = _point; }

    void set_radius(double _value) { this->_radius = _value; }

    void move(double _by_x, double _by_y) {  // add ipunt values to the existing
                                             // positions to move the centre
        this->_centre.set_x(this->_centre.get_x() + _by_x);
        this->_centre.set_y(this->_centre.get_y() + _by_y);
    }
};

// Hauptprogramm
int main(int argc, char *argv[]) {
    Point p;
    Circle c(p);
    cout << "Ausgabe 1:" << endl;
    p.print();
    c.print();
    p.set_x(1.1);
    p.set_y(2.2);
    c.set_centre(p);
    c.set_radius(3.3);
    cout << "Ausgabe 2:" << endl;
    p.print(false);
    cout << " == (" << p.get_x() << ", " << p.get_y() << ")" << endl;
    c.print();
    p.move(1.0, 1.0);
    c.move(2.0, 2.0);
    cout << "Ausgabe 3:" << endl;
    p.print();
    c.print();
    return 0;
}
