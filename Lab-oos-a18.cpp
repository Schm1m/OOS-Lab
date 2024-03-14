
#include <string.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// added this function, so i dont have to copy the line everywhere
// and one line of comments more to have 420 lines of code
void print_line(bool add_line) {
    cout << "---------------------------------------" << endl;
    if (add_line) {
        cout << endl;
    }
}

// Klasse für alle Personen, die Medien leihen können aus Aufgabe 10
class Person {
    string _name;
    int _check_out_duration;

   public:
    Person(string name, int check_out_duration = 0);
    int get_check_out_duration() const;
    string get_name() const;
    void print() const;
};

Person::Person(string name, int check_out_duration)
    : _name(name), _check_out_duration(check_out_duration) {}

int Person::get_check_out_duration() const { return _check_out_duration; }

string Person::get_name() const { return _name; }

void Person::print() const { cout << _name; }

class Lecturer : public Person {
    int _examiner_id;

   public:
    Lecturer(string name, int examiner_id);
    void print() const;
};

Lecturer::Lecturer(string name, int examiner_id)
    : Person(name, 90), _examiner_id(examiner_id) {}

void Lecturer::print() const {
    Person::print();
    cout << ", _examiner_id " << _examiner_id << endl;
}

class Student : public Person {
    int _matriculation_number;

   public:
    Student(string name, int matriculation_number);
    void print() const;
};

Student::Student(string name, int matriculation_number)
    : Person(name, 30), _matriculation_number(matriculation_number) {}

void Student::print() const {
    Person::print();
    cout << ", Matrikelnummer " << _matriculation_number << endl;
}

// Klasse Datum aus Aufgabe 9
class Date {
    int _day, _month, _year;

   public:
    Date(int = 0, int = 0, int = 0);
    // ** neu **
    // Konvertierkonstruktor für String neu
    Date(const string &);
    // ** neu **
    // Konvertierkonstruktor für C-String neu
    Date(const char *);
    Date operator+(int days);
    friend ostream &operator<<(ostream &, const Date &);
};

Date::Date(int d, int m, int y) : _day(d), _month(m), _year(y) {}

// hier Konvertierkonstruktor für String
// search positions of dots. get number parts between dots. convert number parts
// into integers and set as Date values
Date::Date(const string &s) {
    size_t first_dot = s.find_first_of(".");
    size_t last_dot = s.find_last_of(".");
    string s_day = s.substr(0, first_dot);
    string s_month = s.substr(first_dot + 1, last_dot - first_dot - 1);
    string s_year = s.substr(last_dot + 1);
    // cout << "Debug creating Date" << endl;
    // cout << "day: " << s_day << ", month: " << s_month << ", year: " <<
    // s_year << endl;
    _day = stoi(s_day);
    _month = stoi(s_month);
    _year = stoi(s_year);
}

// hier Konvertierkonstruktor für C-String
// convert c-string to string and allocate work to constructor for strings
Date::Date(const char *cs) : Date(static_cast<string>(cs)) {}

Date Date::operator+(int days) {
    int abs_date = _day + _month * 30 + _year * 360;
    abs_date += days;
    int y = abs_date / 360;
    abs_date = abs_date % 360;
    int m = abs_date / 30;
    abs_date = abs_date % 30;
    int d = abs_date;

    return Date(d, m, y);
}

ostream &operator<<(ostream &os, const Date &d) {
    os << d._day << "." << d._month << "." << d._year;
    return os;
}

// Klasse für die Medien, die in der Bibliothek ausgeliehen werden
// können
class Medium {
   protected:
    // Titel des Mediums
    const string _title;
    // Verlag, der das Medium herausgibt
    const string _publisher;
    // Jahr, in dem das Medium veröffentlicht wurde
    const int _year_of_publication;
    // ausgeliehen am
    Date _date_of_check_out;
    // ausgeliehen bis
    Date _date_of_return;
    // ausgeliehen von
    Person *_lender;

   public:
    // Konstruktor
    Medium(string title = "", string publisher = "",
           int year_of_publication = 0);
    virtual ~Medium();
    // Titel zurückliefern
    string get_title() const;
    // Ausleiher zurückliefern
    Person *get_lender() const;
    // das Medium "ausleihen", d.h. Person p, date_of_check_out und
    // date_of_return eintragen
    void check_out(Person &p, Date date_of_check_out, Date date_of_return);
    // Medium in der Konsole ausgeben
    virtual void print() const;
    virtual Medium *clone() const = 0;
};

// hier Konstruktor und Methoden
// initiate values
Medium::Medium(string title, string publisher, int year_of_publication)
    : _title(title),
      _publisher(publisher),
      _year_of_publication(year_of_publication) {
    _lender = nullptr;
}

Medium::~Medium() {}

string Medium::get_title() const { return _title; }

Person *Medium::get_lender() const { return _lender; }

// set given values as values of given object
void Medium::check_out(Person &p, Date date_of_check_out, Date date_of_return) {
    _lender = &p;
    _date_of_check_out = date_of_check_out;
    _date_of_return = date_of_return;
}

// print data of medium. title, publisher and year of publication are always
// given. check if a lender is registered -> if so, print the lender and
// corresponding dates, otherwise print a "-"

// note: the moodle code runner does appear to not like tabs (\t) to format the
// output, so i needed to copy the right amount of spaces from the task
void Medium::print() const {
    stringstream media_out;
    media_out << "Titel:         " << _title << endl;
    media_out << "Verlag:        " << _publisher << endl;
    media_out << "Jahr:          " << _year_of_publication << endl;
    string tmp_lender =
        (!_lender) ? "-" : static_cast<string>(_lender->get_name());
    media_out << "Ausleiher:     ";
    if (!_lender) {
        media_out << "-" << endl;
    } else {
        media_out << _lender->get_name() << " von: " << _date_of_check_out
                  << " bis: " << _date_of_return << endl;
    }
    cout << media_out.str();
}

// Klasse für die Bücher als Spezialisierung von Medium
class Book : public Medium {
    // Autor(en) des Buches
    string _author;

   public:
    // Standardkonstruktor
    Book(string author = "", string title = "", string publisher = "",
         int year_of_publication = 0);
    // das Buch auf der Konsole ausgeben
    void print() const override;
    Medium *clone() const override;
};

// hier Konstruktor und Methoden
// first create object of parent class, then add author data to this classes
// object
Book::Book(string author, string title, string publisher,
           int year_of_publication)
    : Medium(title, publisher, year_of_publication), _author(author) {}

// print the author first, then use the Medium::print() function to do the rest.
void Book::print() const {
    cout << "Autor:         " << _author << endl;
    Book::Medium::print();
    cout << endl;
}

// create an copy of the object this function was called on through an "virtual"
// constructor and return it
Medium *Book::clone() const { return new Book(*this); }

// Klasse für die DVDs als Spezialisierung von Medium
class DVD : public Medium {
    // Abspieldauer der DVD
    const int _c_play_time;

   public:
    // Standardkonstruktor
    DVD(string title = "", string publisher = "", int year_of_publication = 0,
        int play_time = 0);

    // die DVD auf der Konsole ausgeben
    void print() const override;
    Medium *clone() const override;
};

// hier Konstruktor und Methoden
// same as Book::Book, but for dvd´s ( instead of an auther, we now get the
// duration of the dvd )
DVD::DVD(string title, string publisher, int year_of_publication, int play_time)
    : Medium(title, publisher, year_of_publication), _c_play_time(play_time) {}

// first use the Medium::print() function to avoid repetetive code, then print
// the additional information, Medium does not have
void DVD::print() const {
    DVD::Medium::print();
    cout << "Dauer:         " << _c_play_time << endl;
    cout << endl;
}

// same as Book::clone() but for dvd´s
Medium *DVD::clone() const { return new DVD(*this); }

// Die Klasse Library verweist auf alle Medien (Bücher und DVDs),
// die von Personen (Studierende und Dozenten) ausgeliehen werden
// können.
class Library {
    // maximale Anzahl der Medien im Katalog
    const unsigned int _c_maximal_number_of_media;
    // Der Medienkatalog
    vector<Medium *> media;

   public:
    // Standardkonstruktor
    Library(int maximal_number_of_media = 1000);

    // Kopie einer DVD oder eines Buches in den Katalog der Bibliothek eintragen
    // Die maximale Anzahl an Medien darf nicht überschritten werden
    void procure_medium(Medium &);

    // alle Medien auf der Konsole ausgeben,
    // die im Titel das Suchwort enthalten
    void search_medium(string search_word);

    // im Medium mit der Nummer number, die Person p als Ausleiher
    // eintragen mit von-Datum d und bis-Datum d+p.ausleihdauer
    void check_out_medium(int number, Person &p, Date d);

    // alle Medien in der Konsole ausgeben
    void print() const;
};

// hier Konstruktor und Methoden
// even though "maximal" is technically not wrong, i would still have named it
// "maximum" as its the better known variant of this word. otherwise its a
// simple constructor, nothing special
Library::Library(int maximal_number_of_media)
    : _c_maximal_number_of_media(maximal_number_of_media) {}

// check if the libary is full. ( this never happens in this task, but its
// mandatory to check. i dont even know what should happen if its full. should
// it just ignore the new input? ) if there is enough space we add a "clone" of
// our media into the libarys list (vector)
void Library::procure_medium(Medium &m) {
    if (media.size() <= _c_maximal_number_of_media) {
        media.push_back(m.clone());
    }
}

// go through all medias in the vector. if the current media´s title does
// include the given search term, print it.
void Library::search_medium(string s_term) {
    cout << endl;
    cout << "Suche nach \"" << s_term << "\" Ergebnis:" << endl;
    print_line(true);

    int counter = 0;
    for (Medium *p_medium : media) {
        string current_title = p_medium->get_title();
        size_t match = current_title.find(s_term);
        if (match != string::npos) {
            cout << "Medium " << counter << ":" << endl;
            p_medium->print();
        }
        counter++;
    }
    print_line(false);
}

// get the information for checking out the media and allocate the work to the
// Media::check_out() function
void Library::check_out_medium(int number, Person &p, Date d) {
    Medium *c_medium = media[number];
    c_medium->check_out(p, d, (d + p.get_check_out_duration()));
}

// same as search, but just print every media in the vector
void Library::print() const {
    cout << endl;
    cout << "Bibliothekskatalog:" << endl;
    print_line(true);
    int counter = 0;
    for (Medium *p_medium : media) {
        cout << "Medium " << counter << ":" << endl;
        p_medium->print();
        counter++;
    }
    print_line(false);
}

int main(void) {
    // Umlaute etc. in der Konsole zulassen
    setlocale(LC_ALL, "");
    // Bibliothek mit 100 Plätzen initialisieren
    Library library(100);

    // Bücher und DVDs erstellen
    Book b1("U. Breymann", "C++ - Eine Einführung", "Hanser", 2016);

    Book b2("U. Breymann", "Der C++ Programmierer", "Hanser", 2017);
    Book b3("Rainer Grimm", "C++20, Get the details", "Leanpub", 2021);
    Book b4("Bartłomiej Filipek", "C++17 in detail", "Leanbub", 2018);
    Book b5("Timothy Gallwey", "The Inner Game of Tennis", "Pan", 2015);
    // idk why, but apparently the "–" character was very important to be used
    // here ( but not in the first book ). a simple minus was just not good
    // enough ( U+2013 is used instead of a simple minus (U+002d) )

    // idk if this is a browser related problem, but i think it the second time
    // happening for me
    Book b6("Brad Gilbert", "Winning Ugly – Mentale Kriegsführung im Tennis",
            "riva", 2021);
    DVD d1("The IT Crowd", "2entertain", 2016, 600);
    DVD d2("Mr. Robot", "Universal Pictures UK", 2020, 2106);
    DVD d3("Chuck", "Warner Bros (Universal Pictures)", 2013, 3774);

    // Ein Buch und eine DVD ausgeben
    b1.print();
    d1.print();

    // Kopien der Bücher und DVDs (Medien) in die Bibliothek
    // einfügen
    library.procure_medium(b1);
    library.procure_medium(b2);
    library.procure_medium(b3);
    library.procure_medium(b4);
    library.procure_medium(b5);
    library.procure_medium(b6);
    library.procure_medium(d1);
    library.procure_medium(d2);
    library.procure_medium(d3);

    // Bestand der Bibliothek ausgeben
    library.print();

    // Personen anlegen
    Student p1("Peter", 12345678);
    Student p2("Lisa", 87654321);
    Lecturer p3("Prof Miller", 4711);

    // Suchen im Bibliotheksbestand durchführen
    library.search_medium("C++");
    library.search_medium("Tennis");
    library.search_medium("The");

    // Medien ausleihen
    library.check_out_medium(1, p1, "4.5.2023");
    library.check_out_medium(7, p2, "25.05.2023");
    library.check_out_medium(4, p3, "12.10.2023");

    // Bestand der Bibliothek ausgeben
    library.print();
}