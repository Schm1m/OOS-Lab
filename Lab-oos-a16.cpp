
#include <iostream>
#include <vector>
using namespace std;

class Point {
    // same as class Point in Lab-8
    double _x;
    double _y;

   public:
    // Konstruktor mit Parametern
    Point(double x = 0.0, double y = 0.0) {
        this->_x = x;
        this->_y = y;
    }
    // Verschiebt einen Punkt
    void move(double dx, double dy) {
        this->_x += dx;
        this->_y += dy;
    }
    // gibt den Punkt auf der Konsole aus
    void print(bool nl = true) {
        if (nl) {
            cout << "(" << this->_x << ", " << this->_y << ")" << endl;
        } else {
            cout << "(" << this->_x << ", " << this->_y << ")";
        }
    }
};

// Implementierung Konstruktor

// Implementierung Methoden

class Polygonline {
    vector<Point> _points;

   public:
    // Konstruktor
    Polygonline(){};
    // Konstruktor mit Parameter
    Polygonline(Point& p) { this->_points.push_back(p); };
    // gibt die Elemente des Polygons auf der Konsole aus
    void print(bool nl = true);
    // Hängt einen Punkt hinten an
    Polygonline& add_point(Point p) {
        // append a point to the current polygone line and return itself
        this->_points.push_back(p);
        return *this;
    };
    // Hängt einen zusätzlichen Polygon hinten an
    void append_polygonline(Polygonline& pl) {
        vector<Point>::iterator it;
        // iterate through the given polygonline and add each point to the
        // current polygonline
        for (it = pl._points.begin(); it != pl._points.end(); it++) {
            this->_points.push_back(*it);
        }
    };
    // Verschiebt den gesamten Polygon
    void move(double dx, double dy) {
        vector<Point>::iterator it;
        // iterate through all current points of this polygonline an call its
        // respective Point::move() function
        for (it = this->_points.begin(); it != this->_points.end(); it++) {
            it->move(dx, dy);
        }
    };
};

// Implementierung Konstruktor

// Implementierung Methoden

void Polygonline::print(bool nl) {
    cout << "|";

    for (vector<Point>::size_type i = 0; i < _points.size(); ++i) {
        _points[i].print(false);
        if (i < _points.size() - 1) {
            cout << " - ";
        }
    }

    cout << "|";

    if (nl) {
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    Point p1(1, 1), p2(2, 2), p3(3, 3), p4(4, 4), p5(5, 5);
    Polygonline l1;
    Polygonline l2(p3);
    cout << "Ausgabe 1:" << endl;
    l1.print();
    l2.print();
    l1.add_point(p1).add_point(p2);
    l2.add_point(p4).add_point(p5);
    cout << "Ausgabe 2:" << endl;
    l1.print();
    l2.print();
    p2.move(0.5, 0.5);
    cout << "Ausgabe 3:" << endl;
    p2.print();
    l1.print();
    l2.print();
    l1.append_polygonline(l2);
    cout << "Ausgabe 4:" << endl;
    l1.print();
    l2.print();
    l1.move(0, 0.5);
    cout << "Ausgabe 5:" << endl;
    l1.print();
    l2.print();
    return 0;
}
