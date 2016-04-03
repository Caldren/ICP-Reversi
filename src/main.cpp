#include <iostream>
#include <exception>
#include "Board.hpp"
#include "Game.hpp"

using namespace std;

void board_tests();

int main(void)
{
    board_tests();

    Game g(2);

    return 0;
}

void board_tests()
{
    try {
        Board a(5);
        cerr << "[TEST FAIL] Exception expected" << endl;
        exit(100);
    } catch(exception &e) {
        cout << "[TEST PASS] " << e.what() << endl;
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

    cout << c;
}
