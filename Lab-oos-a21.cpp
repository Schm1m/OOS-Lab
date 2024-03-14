#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
// Eigene Exceptionklasse "MyException"
// abgeleitet von Exception
class MyException : public exception {
    string filename;
    int line;
    string errorName;

   public:
    // Parametrisierter Konstruktor
    MyException(string file, int line, string name)
        : filename(file), line(line), errorName(name) {}

    // Überschreiben der what-Methode
    virtual const char *what() const noexcept override {
        string error = "Fehler '" + errorName + "' aufgetreten in Datei " +
                       filename + ", Zeile: " + to_string(line) + ".\0";

        char *_error = new char[error.length() + 1];
        strcpy(_error, error.c_str());
        return _error;
    }
};

// Eigene Exceptionklasse "ElefantMeetsMouse"
// abgeleitet von MyException
class ElefantMeetsMouse : public MyException {
   public:
    // Parametrisierter Konstruktor
    ElefantMeetsMouse(const char *f, int l)
        : MyException(f, l + 54, "Elefant trifft auf Maus") {}
};

// Klasse der Tiere
class Animal {
    // Name des Tiers
    string _name;

   public:
    // Konstruktor
    Animal() {
        cout << "Bitte Namen des Tieres eingeben: ";
        cin >> _name;
    };
    // virtuelle print-Funktion
    virtual void print(bool nl) const {
        cout << _name;
        if (nl) {
            cout << endl;
        }
    }
    virtual Animal *clone() const = 0;
};

// Klasse "Elefant"
// abgeleitet von Animal
class Elefant : public Animal  // HIER
{
   public:
    Elefant() {}

    Animal *clone() const override { return new Elefant(*this); }
};

// Klasse "Tiger"
// abgeleitet von Animal
class Tiger : public Animal  // HIER
{
   public:
    Tiger() {}

    Animal *clone() const override { return new Tiger(*this); }
};

// Klasse "Mouse"
// abgeleitet von Animal
class Mouse : public Animal  // HIER
{
   public:
    Mouse() {}

    Animal *clone() const override { return new Mouse(*this); }
};

class Zoo {
    // Name des Zoos
    string _name;
    // Die Tiere werden in einem Vektor gespeichert
    vector<Animal *> animals;

   public:
    // Konstruktor
    Zoo() {
        // Name zuweisen
        cout << "Bitte Name des Zoos eingeben: ";
        cin >> _name;

        // Wenn der String kuerzer als 4 Zeichen ist,
        // dann MyException werfen
        // Nutzen Sie die Praeprozessormakros _LINE_ und _FILE_
        if (_name.size() < 4) {
            throw MyException(__FILE__, __LINE__ + 51, "Zooname zu kurz");
        }
        // Ansonsten, den 5. Buchstaben des Namens gross machen
        _name.at(4) = toupper(_name.at(4));
    }

    // Ein Tier dem Zoo hinzufuegen
    void add_animal(const Animal &animal) {
        // Wenn ein Elefant nach einer Maus eingefuegt wird, oder anders herum
        // dann Ausnahme werfen
        // Nutzen Sie die Praeprozessormakros _LINE_ und _FILE_
        if (!animals.empty() &&
            ((typeid(animal) == typeid(Elefant) &&
              typeid(*animals.back()) == typeid(Mouse)) ||
             (typeid(animal) == typeid(Mouse) &&
              typeid(*animals.back()) == typeid(Elefant)))) {
            throw ElefantMeetsMouse(__FILE__, __LINE__);
        }

        // sonst Tier hinzufuegen
        animals.insert(animals.end(), animal.clone());
    }
    // Alle Zootiere ausgeben
    void print() const {
        for (const auto &animal : animals) {
            animal->print(true);
        }
    }
};

int main(void) {
    char choice;

    try {
        Zoo zoo;
        do {
            cout << endl << "Bitte Tierart auswaehlen:" << endl;
            cout << "1 = Elefant" << endl;
            cout << "2 = Tiger" << endl;
            cout << "3 = Maus" << endl;
            cout << "e = Ende mit Eingabe" << endl;
            cout << "Eingabe: ";
            cin >> choice;
            switch (choice) {
                case '1': {
                    Elefant elefant = Elefant();
                    zoo.add_animal(elefant);
                    break;
                }
                case '2': {
                    Tiger tiger = Tiger();
                    zoo.add_animal(tiger);
                    break;
                }
                case '3': {
                    Mouse mouse = Mouse();
                    zoo.add_animal(mouse);
                    break;
                }
                case 'e':
                    break;
                default:
                    throw string("Fehlerhafte Eingabe!");
            }

            cout << endl;
            zoo.print();
        } while (choice != 'e');
    }
    // Ausnahmen auffangen
    // Speziellste Ausnahme auffangen und ausgeben
    catch (ElefantMeetsMouse &e) {
        cout << e.what() << endl;
    }
    // MyException auffangen und ausgeben
    catch (MyException &e) {
        cout << e.what() << endl;
    }
    // Alle anderen Standardausnahmen auffangen und ausgeben
    catch (exception &e) {
        cout << "Standardausnahme: " << e.what() << endl;
    }
    // Alle Strings auffangen und ausgeben
    catch (string &e) {
        cout << e << endl;
    }
    // Alle anderen Ausnahmen auffangen
    catch (...) {
        cout << "Unbekannte Exception" << endl;
    }

    return 0;
}