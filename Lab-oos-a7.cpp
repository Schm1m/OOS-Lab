#include <iostream>
#include <string>

using namespace std;

// Klasse Customer definieren

class Customer {
    static int _s_count; // number of customers
    static int _s_id_generator; // id counter
    string _name; // name of customer
    string _location; // location of customer
    int _age; // age of customer
    double _business_done; // cutomers sales volume
    int _transaction_count; // count of transactions of customer
    int _id; // customers id

    public:
    // using default parameters in this case does not make any sense but
    // its demanded by a) 
    Customer(string _c_name = " ", int _c_age = 0, string _c_location = " ") {
        this->_name = _c_name; // assert name
        this->_age = _c_age; // assert age
        this->_location = _c_location; // assert location
        this->_id = ++_s_id_generator; // count up ids and assert next
        _s_count++; // count up total number of customers
        this->_business_done = 0.0; // initiate customers sales volume
        this->_transaction_count = 0; // initiate customers transaction count
    }

    ~Customer() {
        _s_count--; // reduce number of total customers
    }

    void do_business(double amount) {
        this->_business_done += amount; // increase customers sales volume
        this->_transaction_count++; // increase customers transaction count
    }

    static int get_s_count() {
        return _s_count; // return total number of customers
    }

    void print() {
        // print customers data
        cout << "Kunde " << this->_name << " aus " << this->_location << " (ID = " << this->_id << ", " << this->_age << " Jahre) hatte " << this->_transaction_count << " Transaktion(en) und " << this->_business_done << " Euro Umsatz" << endl;
    }
};

int Customer::_s_count = 0;
int Customer::_s_id_generator = 0;

int main(int argc, char *argv[]) {
    Customer peter = Customer("Peter", 17, "Stuttgart");
    Customer simon = Customer("Simon", 23, "Heilbronn");
    peter.~Customer();
    Customer micheal = Customer("Michael", 21, "Karlsruhe");
    Customer claudia = Customer("Claudia", 30, "Nagold");
    std::cout << "Anzahl Kunden: " << Customer::get_s_count() << std::endl;
    simon.do_business(230);
    simon.do_business(400);
    claudia.do_business(1000);
    micheal.do_business(199);
    simon.do_business(3.99);
    simon.print();
    micheal.print();
    claudia.print();
    claudia.~Customer();
    std::cout << "Anzahl Kunden: " << Customer::get_s_count() << std::endl;
    return 0;
}
