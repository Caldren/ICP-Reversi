#ifndef __AI_HPP_INCLUDED
#define __AI_HPP_INCLUDED

#include <vector>
#include "Player.hpp"

class AI : public Player {
public:
    AI(const std::string &name, int color);
    Coordinate makeTurn(const Board *b);

private:
    Coordinate algorithm1(const Board *b);

private:
    std::vector<Coordinate (AI::*)(const Board *b)> m_algorithms;
    int m_curr_algo = 0;
};

#endif
