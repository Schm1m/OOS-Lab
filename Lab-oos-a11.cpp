
#include <iostream>
#include <string>
using namespace std;

class A {
   public:
    void method_1() { cout << "A::method_1()" << endl; }
    void method_2(double d) { cout << "A::method_2(double)" << endl; }
    void method_2(string s) { cout << "A::method_2(string)" << endl; }
    void method_3(char c) { cout << "A::method_3(char)" << endl; }
    void method_3(string s) { cout << "A::method_3(string)" << endl; }
};

class B : public A {
   public:
    void method_2(int i) { cout << "B::method_2(int)" << endl; }
    void method_3(int i) { cout << "B::method_3(int)" << endl; }
    void method_3(string s) { cout << "B::method_3(string)" << endl; }
};

int main(int argc, char *argv[]) {
    A a;
    B b;
    cout << "a.method_1() ";
    a.method_1();
    // a) keine Fehlermeldung;
    // b) Ausgabe: a.method_1(): A::method_1()
    cout << "b.method_1() ";
    b.method_1();
    // a) keine Fehlermeldung;
    // b) Ausgabe: b.method_1(): A::method_1()S
    cout << "a.method_2(1.2) ";
    a.method_2(1.2);
    // a) keine Fehlermeldung;
    // b) Ausgabe: a.method_2(1.2): A::method_2(double)
    cout << "b.method_2(1.2) ";
    b.method_2(1.2);
    // a) keine Fehlermeldung;
    // b) Ausgabe: b.method_2(1.2): B::method_2(int)
    cout << "a.method_2(1) ";
    a.method_2(1);
    // a) keine Fehlermeldung;
    // b) Ausgabe: a.method_2(1): A::method_2(double)
    cout << "b.method_2(1) ";
    b.method_2(1);
    // a) keine Fehlermeldung;
    // b) b.method_2(1): B::method_2(int)
    cout << "a.method_2('c') ";
    a.method_2('c');
    // a) keine Fehlermeldung;
    // b) a.method_2('c'): A::method_2(double)
    cout << "b.method_2('c') ";
    b.method_2('c');
    // a) keine Fehlermeldung;
    // b) b.method_2('c'): B::method_2(int)
    cout << "a.method_2(''string'') ";
    a.method_2("string");
    // a) keine Fehlermeldung;
    // b) a.method_2(''string''): A::method_2(string)

    cout << "b.method_2(''string'') ";  // why are we keeping this one in? the
                                        // function cannot be called without an
                                        // error???
    /* b.method_2("string"); */

    // a) Fehlermeldung, keine passende methode in klasse b. Typkonvertierung
    // nicht möglich b) ...
    cout << "a.method_3(1) ";
    a.method_3(1);
    // a) Keine Fehlermeldung;
    // b) a.method_3(1): A::method_3(char)
    cout << "b.method_3(1) ";
    b.method_3(1);
    // a) Keine Fehlermeldung;
    // b) b.method_3(1): B::method_3(int)
    cout << "a.method_3('c') ";
    a.method_3('c');
    // a) Keine Fehlermeldung;
    // b) a.method_3('c'): A::method_3(char)
    cout << "b.method_3('c') ";
    b.method_3('c');
    // a) Keine Fehlermeldung;
    // b) b.method_3('c'): B::method_3(int)
    cout << "a.method_3(''string'') ";
    a.method_3("string");
    // a) Keine Fehlermeldung;
    // b) a.method_3(''string''): A::method_3(string)
    cout << "b.method_3(''string'') ";
    b.method_3("string");
    // a) Keine Fehlermeldung;
    // b) b.method_3(''string''): B::method_3(string)
    return 0;
}

// Aufgabe c)
// Funktion      | überlädt, verdeckt oder redefiniert.| Funktion
//-------------------------------------------------------------------
// A::method_2(string s)    | überlädt      | A::method_2(double d)
// B::method_2(int i)       | verdeckt      | A::method_2(double d)
// B::method_3(string s)    | redefiniert   | A::method_3(string s)
