

#include <iostream>
#include <string>
using namespace std;

struct ListElement {
    int id;
    ListElement* p_next;
};

ListElement* p_root = nullptr;

void add_new_head_element(int id) {
    ListElement* p_new_element = new ListElement();
    p_new_element->id = id;
    p_new_element->p_next = p_root;
    p_root = p_new_element;
}

void add_new_tail_element(int id) {
    // HIER programmieren:
    // Neues listenElement erzeugen.
    // Ans Ende der Liste navigieren und neues listenElement anhängen.

    if (p_root == nullptr) {
        // create a first Element of the list, if none is present
        ListElement* new_root = new ListElement();
        new_root->id = id;
        p_root = new_root;
    } else {
        // create a new element, cycle through the list to the last element,
        // assign the id to the newly created element, set the new element as
        // the next element of the last element of the list
        ListElement* current = new ListElement();
        current = p_root;
        while (current->p_next != nullptr) {
            current = current->p_next;
        }
        ListElement* new_tail = new ListElement();
        new_tail->id = id;
        current->p_next = new_tail;
    }
}

void delete_element(int id) {
    ListElement* p_tmp = p_root;
    ListElement* p_predecessor = nullptr;

    while (p_tmp != nullptr && p_tmp->id != id) {
        p_predecessor = p_tmp;
        p_tmp = p_tmp->p_next;
    }
    if (p_tmp != nullptr) {
        if (p_tmp == p_root) {
            p_root = p_tmp->p_next;
        } else {
            p_predecessor->p_next = p_tmp->p_next;
        }
    }
    delete p_tmp;
}

void print_list() {
    // Hier programmieren:
    // Die Liste durchlaufen und jeweils die id des listenElements ausgeben.

    // create a new element to move through the list, set root as its value,
    // go through the list and print every elements id until there is no element
    // left
    ListElement* current = new ListElement();
    current = p_root;
    do {
        cout << current->id << endl;
        current = current->p_next;
    } while (current != nullptr);
}

int main(int argc, char* argv[]) {
    add_new_tail_element(9);
    add_new_head_element(2);
    add_new_head_element(1);
    add_new_tail_element(10);
    print_list();
    delete_element(2);
    print_list();

    return 0;
};
