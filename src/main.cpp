#include <iostream>
#include <exception>
#include "Board.hpp"
#include "Game.hpp"
#include "Player.hpp"

using namespace std;

void board_tests();
void player_tests();

int main(void)
{
    board_tests();
    player_tests();

    Game g(8);
    g.addPlayer("Test1");
    g.addPlayer("test2");

    cout << g.getP1()->getName() << endl;
    cout << g.getP2()->getName() << endl;

    int m[8][8] = {
        { 'E', 'E', 'E', 'E', 'B', 'B', 'B', 'E' },
        { 'E', 'E', 'E', 'W', 'W', 'W', 'B', 'E' },
        { 'E', 'E', 'E', 'W', 'E', 'W', 'B', 'E' },
        { 'E', 'E', 'E', 'W', 'W', 'W', 'E', 'E' },
        { 'E', 'E', 'B', 'B', 'W', 'E', 'E', 'E' },
        { 'E', 'W', 'B', 'B', 'W', 'E', 'E', 'E' },
        { 'B', 'E', 'E', 'E', 'B', 'E', 'E', 'E' },
        { 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' }
    };

    g.loadMap(m, 8);

    if(!g.playerTurn(2, 4))
        cout << "Invalid turn" << endl;
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

void player_tests()
{
    Player p("Test", Color::WHITE, Player::HUMAN);
    cout << p.getName() 
          << ": " << p.getScore() << endl;
    p += 1;
    cout << p.getName() << ": " << p.getScore() << endl;
    p--;
    p--;
    cout << p.getName() << ": " << p.getScore() << endl;
}
