#include <stdexcept>
#include "AI.hpp"

AI::AI(const std::string &name, int color) : Player(name, color)
{
    setType(Player::AI);
    m_algorithms.push_back(&AI::algorithm1);
}

Coordinate AI::makeTurn(const Board *b)
{
    if(m_algorithms.empty())
        throw std::runtime_error("No AI algorithms available");

    return (this->*m_algorithms[m_curr_algo])(b);
}

Coordinate AI::algorithm1(const Board *b)
{
    std::vector<Coordinate> coords;
    int score = 0;
    int x = -1, y = -1;

    for(int i = 0; i < b->getSize(); i++) {
        for(int j = 0; j < b->getSize(); j++) {
            if(b->getField(i, j) == Color::EMPTY) {
                // Check for possible moves on current coords
                if(b->checkTurn(i, j, coords, m_color)) {
                    if((int)coords.size() > score) {
                        score = coords.size();
                        x = i;
                        y = j;
                    }
                }
            }
        }
    }

    return Coordinate(x, y);
}
