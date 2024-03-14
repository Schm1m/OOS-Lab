
#include <iostream>
#include <string>
using namespace std;

class Person {
   protected:
    string _name;
    int _check_out_duration;

   public:
    Person(string name, int check_out_duration = 0)
        : _name(name),
          _check_out_duration(check_out_duration){};  // constructor Person
    int get_check_out_duration() const {
        return _check_out_duration;
    };  // return checkout duration
    void print() const {
        cout << "Ausleihdauer: " << _check_out_duration << " Tage(e)"
             << endl;  // print checkout duration
    };
};

// Implmentierung des Konstruktors und der Methoden

class Lecturer : public Person {
    int _examiner_id;

   public:
    Lecturer(string name, int examiner_id)
        : Person(name,
                 90) {  // constructor Lecturer. will call constructor of Person
        this->_examiner_id = examiner_id;
    };
    void print() const {
        cout << this->_name << ", Prüfernummer " << this->_examiner_id
             << endl;  // idk why it works, but by just overloading the print()
                       // function, both this and the inherited function will be
                       // called
    };
};

// Implmentierung des Konstruktors und der Methoden

class Student : public Person {
    int _matriculation_number;

   public:
    Student(string name, int matriculation_number)
        : Person(name, 30) {  // same as in Lecturer
        this->_matriculation_number = matriculation_number;
    };
    void print() const {
        cout << this->_name << ", Matrikelnummer "
             << this->_matriculation_number << endl;  // same as in Lecturer
    };
};

// Implmentierung des Konstruktors und der Methoden

int main(int argc, char *argv[]) {
    Student smith = Student("smith", 12345678);
    Lecturer miller = Lecturer("miller", 98);
    smith.print();
    cout << "Ausleihdauer: " << smith.get_check_out_duration() << " Tage(e)"
         << endl;
    miller.print();
    cout << "Ausleihdauer: " << miller.get_check_out_duration() << " Tage(e)"
         << endl;
}
