#include <iostream>
#include <string>

using namespace std;

class Student {
    string _name;
    string _first_name;

   public:
    Student(string _last, string _first) {
        this->_name = _last;
        this->_first_name = _first;
        cout << "Parametrisierter Konstruktor Student: " << this->_first_name
             << " " << this->_name << endl;
    }

    ~Student() {
        cout << "Destruktor Student: " << this->_first_name << " "
             << this->_name << endl;
    }

    string get_name() { return this->_name; }

    string get_first_name() { return this->_first_name; }

    void print() {
        cout << "print() ohne Parameter; Student: " << this->_first_name << " "
             << this->_name << endl;
    }

    void print(bool if_endl) {
        switch (if_endl) {
            case false:
                cout << "print() mit Parameter; Student: " << this->_first_name
                     << " " << this->_name << flush;
                break;

            default:
                cout << "print() mit Parameter; Student: " << this->_first_name
                     << " " << this->_name << endl;
                break;
        }
    }
};

class Employee {
    string _name;
    string _first_name;

   public:
    Employee() : Employee("Mustermann", "Erika") {
        cout << "Standartkonstruktor Employee: " << this->_first_name << " "
             << this->_name << endl;
    }

    Employee(string _last, string _first) : _name(_last), _first_name(_first) {
        cout << "Parametrisierter Konstruktor Employee: " << this->_first_name
             << " " << this->_name << endl;
    }

    Employee(Student& to_convert) {
        this->_name = to_convert.get_name();
        this->_first_name = to_convert.get_first_name();
        cout << "Konvertireungskonstruktor Employee: " << this->_first_name
             << " " << this->_name << endl;
    }

    ~Employee() {
        cout << "Destruktor Employee: " << this->_first_name << " "
             << this->_name << endl;
    }

    void print() {
        cout << "print() ohne Parameter; Student: " << this->_first_name << " "
             << this->_name << endl;
    }

    void print(bool if_endl) {
        switch (if_endl) {
            case false:
                cout << "print() mit Parameter; Employee: " << this->_first_name
                     << " " << this->_name << flush;
                break;

            default:
                cout << "print() mit Parameter; Employee: " << this->_first_name
                     << " " << this->_name << endl;
                break;
        }
    }
};

int main(int argc, char* argv[]) {
    Student stud_mustermann = Student("Mustermann", "Max");
    Employee empl_mustermann = Employee(stud_mustermann);
    Employee mit_default = Employee();
    stud_mustermann.print();
    stud_mustermann.print(true);
    empl_mustermann.print();
    mit_default.print();
    Student* p_stud_mustermann = nullptr;
    cout << "Block wird betreten" << endl;
    {
        p_stud_mustermann = new Student("Mustermann", "Markus");
        p_stud_mustermann->print(true);
    }
    cout << "Block wurde verlassen" << endl;
    delete p_stud_mustermann;
}