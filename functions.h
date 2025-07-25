#ifndef FUNCTIONS_H
#define FUNCTION_H

#include <limits>
#include <iostream>
using namespace std;

int getValidNumber() {
    int input;
    while (true) {
        cout << "Enter a number: ";
        cin >> input;

        if (cin.fail()) {
            cin.clear(); // clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush bad input
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover input
            return input;
        }
    }
}

#endif