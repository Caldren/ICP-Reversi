#include <iostream>
#include <exception>
#include "Board.hpp"

using namespace std;

int main(void)
{
    try {
        Board a(5);
    } catch(exception &e) {
        cout << "[EXCEPTION] (a)" << e.what() << endl;
    }

    Board b;
    cout << "(b) Board size: " << b.getSize() << endl;

    Board c(12);
    cout << "(c) Board size: " << c.getSize() << endl;

    return 0;
}
