#ifndef __PLAYER_HPP_INCLUDED
#define __PLAYER_HPP_INCLUDED

#include <string>
#include "Board.hpp"
#include "Color.hpp"
#include "Coordinate.hpp"

class Player {
public:
    Player(const std::string &name, int color);
    virtual ~Player() {}

    void setName(const std::string &name);
    void setColor(int color);
    void setType(int type);
    void setScore(int score);

    const std::string &getName() const;
    int getColor() const;
    int getType() const;
    int getScore() const;
    void addToScore(int x);
    void subFromScore(int x);

    virtual Coordinate makeTurn(const Board *b) {
        throw std::runtime_error("makeTurn() not implemented");
    };

    enum PlayerType {
        HUMAN,
        AI
    };

protected:
    std::string m_name;
    Color m_color;
    int m_score;
    int m_type;
};

#endif
