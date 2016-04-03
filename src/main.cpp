#include <iostream>
#include <exception>
#include "Board.hpp"

using namespace std;

int main(void)
{
    try {
        Board a(5);
        cerr << "[TEST FAIL] Exception expected" << endl;
        exit(100);
    } catch(exception &e) {
        cout << "[TEST PASS] " << e.what() << endl;
    }

    Board b;
    if(b.getSize() != 8) {
        cerr << "[TEST FAIL] Board size should be 8 (is "
             << b.getSize() << ")" << endl;
        exit(100);
    } else {
        cout << "[TEST PASS] Default board size is 8" << endl;
    }

    Board c(12);
    if(c.getSize() != 12) {
        cerr << "[TEST FAIL] Board size should be 12 (is "
             << c.getSize() << ")" << endl;
        exit(100);
    } else {
        cout << "[TEST PASS] Board size equals to value passed to constructor"
             << endl;
    }

    try {
        c.setField(12, 1, 0);
        cerr << "[TEST FAIL] Buffer overflow in setField" << endl;
        exit(100);
    } catch(exception &e) {
        cout << "[TEST PASS] " << e.what() << endl;
    }

    try {
        c.getField(-1, 0);
        cerr << "[TEST FAIL] Buffer underflow in getField" << endl;
        exit(100);
    } catch(exception &e) {
        cout << "[TEST PASS] " << e.what() << endl;
    }

    try {
        c.setField(0, 0, 0);
        cerr << "[TEST FAIL] Invalid value in setField" << endl;
        exit(100);
    } catch(exception &e) {
        cout << "[TEST PASS] " << e.what() << endl;
    }

    return 0;
}
