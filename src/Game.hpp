#ifndef __GAME_HPP_INCLUDED
#define __GAME_HPP_INCLUDED

#include <vector>
#include "Board.hpp"
#include "Player.hpp"

// TODO: Copy & move constructors

class Game {
public:
    Game(int size = 8);
    ~Game();

    void addPlayer(const std::string &name, int score = 0, int color = -1);

    const Player *getP1();
    const Player *getP2();

private:

public:

private:
    Player *m_p1;
    Player *m_p2;
    Board *m_board = nullptr;
    int m_size;
};

#endif
