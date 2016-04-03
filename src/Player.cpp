#include <stdexcept>
#include "Player.hpp"
#include "Color.hpp"

Player::Player(const std::string &name, int color, int type)
{
    setName(name);
    setColor(color);
    setType(type);
    m_score = 0;
}

void Player::setName(const std::string &name)
{
    if(name.size() == 0)
        m_name = "Unnamed";
    else
        m_name = name;
}

void Player::setColor(int color)
{
    if(color == Color::EMPTY)
        throw std::invalid_argument("EMPTY is not a valid color for a player");

    m_color.setColor(color);
}

void Player::setType(int type)
{
    switch(type) {
    case HUMAN:
    case AI:
        break;
    default:
        throw std::invalid_argument("Player type must be HUMAN or AI");
    }

    m_type = type;
}

void Player::setScore(int score)
{
    if(score < 0)
        m_score = 0;
    else
        m_score = score;
}

const std::string &Player::getName()
{
    return m_name;
}

int Player::getColor()
{
    return m_color;
}

int Player::getType()
{
    return m_type;
}

int Player::getScore()
{
    return m_score;
}

int Player::operator+(int x)
{
    setScore(m_score + x);
    return m_score;
}

int Player::operator-(int x)
{
    setScore(m_score - x);
    return m_score;
}

int Player::operator+=(int x)
{
    setScore(m_score + x);
    return m_score;
}

int Player::operator-=(int x)
{
    setScore(m_score - x);
    return m_score;
}

int Player::operator++(int)
{
    setScore(m_score + 1);
    return m_score;
}

int Player::operator--(int)
{
    setScore(m_score - 1);
    return m_score;
}

int Player::operator++()
{
    setScore(m_score + 1);
    return m_score;
}

int Player::operator--()
{
    setScore(m_score - 1);
    return m_score;
}
