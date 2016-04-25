#ifndef __GAME_HPP_INCLUDED
#define __GAME_HPP_INCLUDED

#include <vector>
#include "Board.hpp"
#include "Player.hpp"
#include "Coordinate.hpp"
#include "History.hpp"

// TODO: Copy & move constructors

class Game {
public:
    Game(int size = 8);
    Game(const std::string &filename);
    ~Game();

    void initGame(bool load = false);
    const Player *addPlayer(const std::string &name, int type = Player::HUMAN,
                            int score = 0, int color = -1);
    bool playerTurn(int row, int col, bool load = false);
    bool skipTurn(int color = -1, bool load = false);
    bool prevTurn();
    bool nextTurn();

    const Player *getP1();
    const Player *getP2();
    const Player *getCurrentPlayer();
    const Player *getCurrentOpponent();
    const Player *getWinner();
    void switchPlayers(bool history = false);

    const Board *getBoard();
    bool isGameOver();

    bool save(const std::string &filename, std::string &error);
    bool load(const std::string &filename, std::string &error);

private:
    bool checkGameEnd();
    bool checkPossibleTurn(int color);
    void getAITurn();

public:

private:
    Player *m_p1 = nullptr;
    Player *m_p2 = nullptr;
    Player *m_curr_p = nullptr;
    Player *m_curr_op = nullptr;
    Player *m_winner = nullptr;
    Board *m_board = nullptr;
    History m_history;
    int m_size = 0;
    bool m_game_over = false;
};

#endif
