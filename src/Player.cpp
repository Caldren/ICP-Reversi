/**
 * @file Player.cpp
 * @brief Implementation file of Player class.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#include <stdexcept>
#include <algorithm>
#include "Player.hpp"
#include "Color.hpp"

Player::Player(const std::string &name, int color)
{
    setName(name);
    setColor(color);
    setType(Player::HUMAN);
    m_score = 0;
}

void Player::setName(const std::string &name)
{
    if(name.size() == 0) {
        m_name = "Unnamed";
    } else {
        m_name = name;
        // Replace all tabs with spaces
        // (we'll use tab as a value separator in saves)
        std::replace(m_name.begin(), m_name.end(), '\t', ' ');
    }
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

const std::string &Player::getName() const
{
    return m_name;
}

int Player::getColor() const
{
    return m_color;
}

int Player::getType() const
{
    return m_type;
}

int Player::getScore() const
{
    return m_score;
}

void Player::addToScore(int x)
{
    setScore(m_score + x);
}

void Player::subFromScore(int x)
{
    setScore(m_score - x);
}
