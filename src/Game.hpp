#ifndef __GAME_HPP_INCLUDED
#define __GAME_HPP_INCLUDED

#include <vector>
#include "Board.hpp"
#include "Player.hpp"
#include "Coordinate.hpp"

// TODO: Copy & move constructors
// TODO: skipTurn()
//  * player must do a turn if he can
//
// TODO: Copy & move constructors

class Game {
public:
    Game(int size = 8);
    ~Game();

    void addPlayer(const std::string &name, int score = 0, int color = -1);
    bool playerTurn(int row, int col);
    bool skipTurn();

    const Player *getP1();
    const Player *getP2();
    const Player *getCurrentPlayer();
    const Player *getCurrentOpponent();
    void switchPlayers();

    // TODO: Remove
    void loadMap(int map[][8], int size) {
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                m_board->setField(i, j, map[i][j]);
            }
        }

        std::cout << *m_board << std::endl;
    }

private:
    bool checkTurn(int row, int col, std::vector<Coordinate> &coords);

public:

private:
    Player *m_p1;
    Player *m_p2;
    Player *m_curr_p;
    Player *m_curr_op;
    Board *m_board = nullptr;
    int m_size;
};

#endif
