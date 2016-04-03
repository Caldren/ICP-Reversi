#ifndef __PLAYER_HPP_INCLUDED
#define __PLAYER_HPP_INCLUDED

#include <string>
#include "Board.hpp"
#include "Color.hpp"

class Player {
public:
    Player(const std::string &name, int color);

    void setName(const std::string &name);
    void setColor(int color);
    void setScore(int score);

    const std::string &getName();
    int getColor();
    int getScore();

    int operator+(int x);
    int operator-(int x);
    int operator+=(int x);
    int operator-=(int x);
    int operator++(int);
    int operator--(int);
    int operator++();
    int operator--();

private:
    std::string m_name;
    Color m_color;
    int m_score;
};

#endif
