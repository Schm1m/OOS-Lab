#include <iostream>
#include <vector>
using namespace std;

// interface class
class IComponent {
   public:
    virtual void add(IComponent *) = 0;
    virtual int get_price() = 0;
};

// Box class, can contain Products directly or another Boxes
class Box : public IComponent {
    vector<IComponent *> _components;

   public:
    // add component to list
    void add(IComponent *addC) { _components.push_back(addC); }
    // get price of all components. recursively gets all sub-prices
    virtual int get_price() override {
        int sum = 0;
        for (IComponent *comp : _components) {
            sum += comp->get_price();
        }
        return sum;
    }
};

// Product class, has a set price and can return it
class Product : public IComponent {
    const int _price;

   public:
    // needs to be defined here, otherwise there is an error of it not being
    // overridden
    virtual void add(IComponent *) {}
    Product(int p) : _price(p) {}
    // return price of Product
    int get_price() override { return _price; }
};

void calculate_price(IComponent *component) {
    cout << "Preis: " << component->get_price() << endl;
}

int main(void) {
    cout << "Preisermittlung für ein einfaches Produkt: " << endl;
    IComponent *product = new Product(10);
    calculate_price(product);
    cout << endl;

    cout << "Preisermittlung für eine verschachtelte Box: " << endl;
    IComponent *outer_box = new Box;
    IComponent *inner_box_1 = new Box;
    IComponent *product_1 = new Product(10);
    IComponent *product_2 = new Product(5);
    IComponent *product_3 = new Product(4);
    inner_box_1->add(product_1);
    inner_box_1->add(product_2);
    IComponent *inner_box_2 = new Box;
    inner_box_2->add(product_3);
    outer_box->add(inner_box_1);
    outer_box->add(inner_box_2);
    calculate_price(outer_box);
    cout << endl;

    cout << "Preisermittlung für eine erweiterte verschachtelte Box: " << endl;
    IComponent *product_4 = new Product(7);
    inner_box_2->add(product_4);
    calculate_price(outer_box);
    cout << endl;

    return 0;
}
