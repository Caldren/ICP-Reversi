/**
 * @file Color.hpp
 * @class Color
 * @brief Simple entity for keeping information about valid Player and Board
 *        colors.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#ifndef __COLOR_HPP_INCLUDED
#define __COLOR_HPP_INCLUDED

class Color {
public:
    /**
     * @brief Create color object.
     * @see ColorTypes
     * @param color %Color code (default: Color::EMPTY)
     */
    Color(int color = Color::EMPTY);

    /**
     * @brief Set color.
     * @details Throws std::invalid_argument on invalid color code.
     * @see ColorTypes
     * @param color %Color code
     */
    void setColor(int color);
    /**
     * @brief Get currently set color code.
     * @see ColorTypes
     * @returns %Color code
     */
    int getColor();
    /**
     * @brief Check if given color code is valid.
     * @see ColorTypes
     * @param color %Color code
     * @return true if given color code is valid, false otherwise
     */
    static bool isValid(int color);

    /**
     * @brief Convert Color to int
     */
    operator int() const;
    /**
     * @brief Convert color to char
     */
    operator char() const;

    /**
     * @brief Valid color codes.
     */
    enum ColorTypes {
        BLACK = 'B',    /**< Black color */
        EMPTY = 'E',    /**< No color */
        WHITE = 'W',    /**< White color */
    };

private:
    int m_color; /**< Currently selected color code */
};

#endif
