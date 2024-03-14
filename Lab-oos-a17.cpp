
#include <iostream>
#include <string>
using namespace std;

void p(string s, bool nl = true) {
    cout << s << " ";
    if (nl) {
        cout << endl;
    }
}

class A {  // make 2 overridable
   public:
    void method_1() { p("A::method_1()"); }
    virtual void method_2() { p("A::method_2()"); }
    void method_3() { p("A::method_3()"); }
    void method_4() {
        p("A::method_4()", false);
        method_2();
    }
};

class B : public A {  // make 2, 4 overridable
   public:
    void method_1() { p("B::method_1()"); }
    virtual void method_2() { p("B::method_2()"); }
    void method_3() { p("B::method_3()"); }
    virtual void method_4() {
        p("B::method_4()", false);
        method_2();
    }
};

class C : public B {  // make 2, 3 overridable. override 4
   public:
    void method_1() { p("C::method_1()"); }
    virtual void method_2() { p("C::method_2()"); }
    virtual void method_3() { p("C::method_3()"); }
    void method_4() override {
        p("C::method_4()", false);
        method_2();
    }
};

class D : public C {  // override 2, 3
   public:
    void method_1() { p("D::method_1()"); }
    void method_2() override { p("D::method_2()"); }
    void method_3() override { p("D::method_3()"); }
};

int main(int argc, char *argv[]) {
    D d;
    A *p_a = &d;
    B *p_b = &d;
    C *p_c = &d;
    p_a->method_1();
    p_b->method_1();
    p_c->method_1();
    p_a->method_2();
    p_b->method_2();
    p_c->method_2();
    p_a->method_3();
    p_b->method_3();
    p_c->method_3();
    p_a->method_4();
    p_b->method_4();
    p_c->method_4();
}

/*
// output without virtualization and overrides:

A::method_1()
B::method_1()
C::method_1()
A::method_2() + override to D::2
B::method_2() + override to D::2
C::method_2() + override to D::2
A::method_3()
B::method_3()
C::method_3() + override to D::3
A::method_4() A::method_2() + override second output to D::2
B::method_4() B::method_2() + override to C::4 and D::2
C::method_4() C::method_2() + override second output to D::2

*/