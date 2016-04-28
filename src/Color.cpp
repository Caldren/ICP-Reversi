/**
 * @file Color.cpp
 * @brief Implementation file of Color class.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#include <stdexcept>
#include "Color.hpp"

Color::Color(int color)
{
    setColor(color);
    m_color = color;
}

void Color::setColor(int color)
{
    if(!isValid(color))
        throw std::invalid_argument("Invalid color - must be: "
                                    "BLACK, EMPTY or WHITE");

    m_color = color;
}

int Color::getColor()
{
    return m_color;
}

bool Color::isValid(int color)
{
    switch(color) {
    case BLACK:
    case EMPTY:
    case WHITE:
        return true;
    }

    return false;
}

Color::operator int() const
{
    return (int)m_color;
}

Color::operator char() const
{
    return (char)m_color;
}
