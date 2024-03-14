using namespace std;
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Meal {
    // declare meal name and vector for toppings
    const string name;
    vector<string> _toppings;

   public:
    // constructor for meal. sets the meals name
    Meal(string s) : name(s) {}
    // add a topping to the meal
    void add_topping(string s) { _toppings.push_back(s); }
    // add a meal, cloning a Pizza or Burger to use their functions later
    void add_meal(Meal &m) { m.clone(); }
    // get name of meal
    string get_name() { return name; }
    // print all toppings of the meal
    virtual void prepare() {
        stringstream out;
        for (string topping : _toppings) {
            out << "- " << topping << endl;
        }
        cout << out.str();
    }
    virtual Meal *clone() const = 0;
};

class Pizza : public Meal {
   public:
    // constructor for pizza, making a meal through its own constructor
    Pizza(string s) : Meal(s) { Meal::add_meal(*this); }
    // print the Pizza´s name and use Meal::prepare() to print its toppings
    void prepare() override {
        stringstream out;
        out << "Pizza ";
        out << this->get_name();
        out << ". Pizzaboden, belegt mit:" << endl;
        cout << out.str();
        Meal::prepare();
    }
    // clone this object to use pizzas functions on this Meal object
    Meal *clone() const override { return new Pizza(*this); }
};

class Burger : public Meal {
   public:
    // constructor for Burger, making a meal through its own constructor
    // ( same as in Pizza )
    Burger(string s) : Meal(s) { Meal::add_meal(*this); }
    // print the burger´s name and use Meal::prepare() to print its toppings
    // ( same as in Pizza )
    void prepare() override {
        stringstream out;
        out << this->get_name();
        out << ". Brötchen mit:" << endl;
        cout << out.str();
        Meal::prepare();
    }
    // clone this object to user burgers functions on this Meal object
    //( same as in Pizza )
    Meal *clone() const override { return new Burger(*this); }
};

int main(void) {
    Pizza *mista = new Pizza("Mista");
    mista->add_topping("Salami");
    mista->add_topping("Pilzen");
    Meal *hawaii = new Pizza("Hawaii");
    hawaii->add_topping("Schinken");
    hawaii->add_topping("Ananas");
    Burger *hamburger = new Burger("Hamburger");
    hamburger->add_topping("Hackfleisch");
    Meal *cheesburger = new Burger("Cheesburger");
    cheesburger->add_topping("Hackfleisch");
    cheesburger->add_topping("Käse");
    array<Meal *, 4> menu = {mista, hawaii, hamburger, cheesburger};
    for (Meal *g : menu) {
        g->prepare();  //*[1]
    }
    return 0;
}
