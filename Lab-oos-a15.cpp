
#include <array>
#include <iostream>
using namespace std;

const unsigned int length = 10;
// even though the length of each array is predefined here i choose to make an
// array-size unrelated sort function as the implementation ist not really
// different from a sort function with predefined length

// hier die Funktion 'sort' implementieren
template <typename sortinput>
// define a template type to fit any type of array
sortinput sort(sortinput &sort_array) {
    for (int i = 0; i < (int)sort_array.size() - 1; i++) {
        // the maximum amount of cyles is the arrays size - 1. as we sort i.e.
        // the first 9 elements of an array, the last only has one spot to go.
        //
        // (int)array.size() is required, as Array::size() does not return a
        // integer so we cant compare it to i
        for (int j = 0; j < (int)sort_array.size() - 1; j++) {
            // move through the whole array. there are (array.size() - 1) moves
            // to make, as we move along as a "2 objects sized iterator"
            if (sort_array[j] > sort_array[j + 1]) {
                // if the first element is bigger than the second one, swap the
                // two elements
                swap(sort_array[j], sort_array[j + 1]);
            }
        }
    }
    return sort_array;
}

int main(int argc, char *argv[]) {
    array<int, length> int_container = {10, 2, 7, 5, 8, 3, 4, 1, 9, 6};
    array<int, length> sorted_int_container = sort(int_container);

    for (size_t i = 0; i < sorted_int_container.size(); i++) {
        cout << i << ": " << sorted_int_container[i] << endl;
    }

    array<char, length> char_container = {'j', 'm', 'e', 't', 'k',
                                          'o', 'p', 's', 'a', 'f'};
    array<char, length> sorted_char_container = sort(char_container);

    for (size_t i = 0; i < sorted_char_container.size(); i++) {
        cout << i << ": " << sorted_char_container[i] << endl;
    }

    array<string, length> string_container = {"Im",       "Sommer", "ist", "es",
                                              "meistens", "heiß",   "und", "es",
                                              "regnet",   "wenig."};
    array<string, length> sorted_string_container = sort(string_container);

    for (size_t i = 0; i < sorted_string_container.size(); i++) {
        cout << i << ": " << sorted_string_container[i] << endl;
    }
}
