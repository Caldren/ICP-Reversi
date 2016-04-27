#include <stdexcept>
#include "AI.hpp"

AI::AI(const std::string &name, int color) : Player(name, color)
{
    setType(Player::AI);
}

Coordinate AI::makeTurn(const Board *b)
{
    if(m_algorithms.empty())
        throw std::runtime_error("No AI algorithms available");

    return (this->*m_algorithms[m_curr_algo])(b);
}

int AI::getAlgorithmCount()
{
    return m_algorithms.size();
}

int AI::getAlgorithm()
{
    return m_curr_algo;
}

void AI::setAlgorithm(int id)
{
    if(id < 0 || id > (int)(m_algorithms.size() - 1))
        throw std::range_error("Algorithm index is out of range");

    m_curr_algo = id;
}

Coordinate AI::algorithm1(const Board *b)
{
    // Primitive algorithm 1: pick move with the highest score
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

Coordinate AI::algorithm2(const Board *b)
{
    // Primitive algorithm 2: pick a move with the lowest score
    std::vector<Coordinate> coords;
    // Arbitrary maximum
    int score = b->getSize() * b->getSize();
    int x = -1, y = -1;

    for(int i = 0; i < b->getSize(); i++) {
        for(int j = 0; j < b->getSize(); j++) {
            if(b->getField(i, j) == Color::EMPTY) {
                // Check for possible moves on current coords
                if(b->checkTurn(i, j, coords, m_color)) {
                    if((int)coords.size() < score &&
                       (int)coords.size() >= 1) {
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

std::vector<Coordinate (AI::*)(const Board *b)> AI::m_algorithms = {
    &AI::algorithm1,
    &AI::algorithm2
};
