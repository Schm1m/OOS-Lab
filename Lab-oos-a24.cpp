#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

using namespace std;

// Hier Exception implementieren

// OutOfStockExeption extends std exeption. carried a value for the amount that
// was supposed to be sold, the amount that is available and the product type
class OutOfStockExeption : public exception {
    int trying;
    int has;
    string prod_type;

   public:
    OutOfStockExeption(int t, int h, string prod)
        : trying(t), has(h), prod_type(prod) {}
    virtual const char *what() const noexcept override {
        string error = "Es sind " + to_string(has) + " Artikel vom Typ " +
                       prod_type + " verfügbar. Es können nicht " +
                       to_string(trying) + " Artikel verkauft werden" + ".\0";

        char *_error = new char[error.length() + 1];
        strcpy(_error, error.c_str());
        return _error;
    }
};

// Hier Interface implementieren
class ISubscriber {
   public:
    virtual void update(string) = 0;
};

// Hier Klassen Customer und GoldCustomer implementieren

// Customer extends the Interface ISubscriber. has an constant id and id
// generator to create it.
class Customer : public ISubscriber {
    const int _id;
    static int _id_generator;

   public:
    Customer() : _id(++_id_generator) {}
    // updates the customer (the console) if the store sends an update.
    // depending on what the last char of the update string is, it fires the
    // right message to be displayed.
    // could have done it much simpler but the task states the update() function
    // ( only? ) takes a string parameter, so i did it only with one string
    void update(string s) override {
        switch (s.back()) {
            case 'r':
                s.pop_back();
                cout << "Customer " << _id
                     << ": neue Nachricht verfügbar --> Neue Artikel vom Typ "
                     << s << " verfügbar." << endl;
                break;
            case 'e':
                s.pop_back();
                cout << "Customer " << _id
                     << ": neue Nachricht verfügbar --> Artikel vom Typ " << s
                     << " nicht mehr verfügbar" << endl;
                break;
        }
    }
};

// basically the same as Customer, but has a little namechange and its own id
// system
class GoldCustomer : public ISubscriber {
    const int _id;
    static int _id_generator;

   public:
    GoldCustomer() : _id(++_id_generator) {}
    void update(string s) override {
        switch (s.back()) {
            case 'r':
                s.pop_back();
                cout << "GoldCustomer " << _id
                     << ": neue Nachricht verfügbar --> Neue Artikel vom Typ "
                     << s << " verfügbar." << endl;
                break;
            case 'e':
                s.pop_back();
                cout << "GoldCustomer " << _id
                     << ": neue Nachricht verfügbar --> Artikel vom Typ " << s
                     << " nicht mehr verfügbar" << endl;
                break;
        }
    }
};

class Store {
   public:
    // Hier Methoden implementieren

    // add the subscriber to the list
    void subscribe(ISubscriber *sub) { _subscribers.push_back(sub); }

    // remove the subscriber from the list
    void unsubscribe(ISubscriber *unsub) { _subscribers.remove(unsub); }

    // notify the subscriber about a given product and its status
    void notify_subscribers(string prod, string status) {
        for (ISubscriber *curr : _subscribers) {
            curr->update(prod + status);
        }
    }

    // add x new products to the store and output corresponding data. call
    // notify_subscribers() if the given product was unavailable before
    void deliver_products(string prod, uint count) {
        bool replenished = (_product_availability[prod] == 0) ? true : false;
        stringstream output;
        output << "Vorrätige Artikel vom Typ " << prod << ": "
               << _product_availability[prod] << endl;
        output << "Ausgelieferte Artikel vom Typ " << prod << ": " << count
               << endl;
        _product_availability[prod] += count;
        output << "Neuer Bestand: " << _product_availability[prod] << endl;
        cout << output.str();
        if (replenished) this->notify_subscribers(prod, "r");
    }

    // remove x products from the store and output corresponding data. call
    // notify_subscribers() if the given product is now unavailable
    void sell_products(string prod, uint count) {
        if (_product_availability[prod] >= count) {
            stringstream output;
            output << "Vorrätige Artikel vom Typ " << prod << ": "
                   << _product_availability[prod] << endl;
            output << "Verkaufte Artikel vom Typ " << prod << ": " << count
                   << endl;
            _product_availability[prod] -= count;
            output << "Neuer Bestand: " << _product_availability[prod] << endl;
            cout << output.str();
            if (_product_availability[prod] == 0) {
                this->notify_subscribers(prod, "e");
            }
        } else {
            throw OutOfStockExeption(count, _product_availability[prod], prod);
        }
    }

   private:
    list<ISubscriber *> _subscribers;
    map<string, unsigned int> _product_availability{{"iPhone", 0},
                                                    {"Galaxy", 5}};
};

int Customer::_id_generator = 100;
int GoldCustomer::_id_generator = 0;

void manage_store() {
    try {
        Store *store = new Store;
        ISubscriber *customer_1 = new Customer();
        store->subscribe(customer_1);
        ISubscriber *customer_2 = new GoldCustomer();
        store->subscribe(customer_2);
        ISubscriber *customer_3 = new GoldCustomer();
        store->subscribe(customer_3);
        store->deliver_products("iPhone", 5);
        store->unsubscribe(customer_3);
        store->sell_products("iPhone", 3);
        ISubscriber *customer_4 = new Customer();
        store->subscribe(customer_4);
        store->deliver_products("iPhone", 5);
        store->sell_products("iPhone", 7);
        store->unsubscribe(customer_1);
        ISubscriber *customer_5 = new GoldCustomer();
        store->subscribe(customer_5);
        store->deliver_products("iPhone", 15);
        store->sell_products("Galaxy", 8);
    } catch (exception &e) {
        cout << e.what() << endl;
    } catch (...) {
        cout << "Ein unbekannter Fehler ist aufgetreten." << endl;
    }
}

int main(void) {
    manage_store();
    return 0;
}
