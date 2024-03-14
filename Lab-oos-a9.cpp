#include <iostream>
using namespace std;

class Date {
    int _day, _month, _year;

   public:
    Date(int _d = 0, int _m = 0, int _y = 0) {  // initiate date
        this->_day = _d;
        this->_month = _m;
        this->_year = _y;
    }
    Date operator+(int days) {
        Date _return_date;    // create a temporary date to for returning later
        int _add_days = 0;    // initiate vars for later
        int _add_months = 0;  //
        int _add_years = 0;   //
        for (int i = days; i >= 360;
             i -= 360) {  // count number of years to add to the date
            _add_years++;
        }
        for (int i = (days % 360); i >= 30;
             i -= 30) {  // count number of days to add to the date
            // "(days % 360)" means, we first subrtract all the days we already
            // used to count years to add
            _add_months++;
        }
        // add "remaining" days to add to the date
        _add_days = ((days % 360) % 30);

        _return_date._day = this->_day + _add_days;  // add days to return date
        if (_return_date._day >=
            31) {  // check if day digit exeeds 30 ( there is no 31st day of a
                   // month in this lab )
            _return_date._day -= 30;
            _add_months++;
        }
        _return_date._month =
            this->_month + _add_months;  // add months to return date
        if (_return_date._month >=
            13) {  // check if month digit exeeds 12 ( there is no 13th month )
            _return_date._month -= 12;
            _add_years++;
        }
        _return_date._year =
            this->_year + _add_years;  // add years to return date

        return _return_date;
    }
    friend ostream &operator<<(ostream &, const Date &);
};

ostream &operator<<(ostream &s, const Date &_date) {
    return s << _date._day << "." << _date._month << "."
             << _date._year;  // formating to print a date inside of cout
}

int main(int argc, char *argv[]) {
    Date begin_task = Date(26, 10, 2023);
    cout << "Die Aufgabe beginnt am " << begin_task << endl;
    Date end_task = begin_task + 6;
    cout << "Die Aufgabe endet am " << end_task << endl;
    Date one_year_and_one_month_later = begin_task + 390;
    cout << "Ein Jahr und ein Monat nach Aufgabenbeginn ist der "
         << one_year_and_one_month_later << endl;
    Date three_years_and_eleven_months_later = begin_task + 1410;
    cout << "Drei Jahre und 11 Monate nach Aufgabenbeginn ist der "
         << three_years_and_eleven_months_later << endl;
}
