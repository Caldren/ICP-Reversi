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

    const std::string &getName() const;
    int getColor() const;
    int getType() const;
    int getScore() const;
    void addToScore(int x);
    void subFromScore(int x);

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
