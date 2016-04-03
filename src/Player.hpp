#ifndef __PLAYER_HPP_INCLUDED
#define __PLAYER_HPP_INCLUDED

#include <string>
#include "Board.hpp"
#include "Color.hpp"

class Player {
public:
    Player(const std::string &name, int color, int type);

    void setName(const std::string &name);
    void setColor(int color);
    void setType(int type);
    void setScore(int score);

    const std::string &getName();
    int getColor();
    int getType();
    int getScore();

    int operator+(int x);
    int operator-(int x);
    int operator+=(int x);
    int operator-=(int x);
    int operator++(int);
    int operator--(int);
    int operator++();
    int operator--();

    enum PlayerType {
        HUMAN,
        AI
    };

private:
    std::string m_name;
    Color m_color;
    int m_score;
    int m_type;
};

#endif
