/**
 * @file Player.hpp
 * @class Player
 * @brief %Player entity.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#ifndef __PLAYER_HPP_INCLUDED
#define __PLAYER_HPP_INCLUDED

#include <string>
#include "Board.hpp"
#include "Color.hpp"
#include "Coordinate.hpp"

class Player {
public:
    /**
     * @brief Create Player object with given name an color
     * @details If name is empty, "Unnamed" is used instead.
     *          Function uses setColor() and setType() functions, which throws
     *          exceptions on errors.
     * @see Color::ColorTypes
     * @see setColor()
     * @see setType()
     * @param name %Player name
     * @param color %Player color
     */
    Player(const std::string &name, int color);
    virtual ~Player() {}

    /**
     * @brief Set player's name.
     * @details Defaults to "Unnamed" when given empty string.
     * @param name %Player name
     */
    void setName(const std::string &name);
    /**
     * @brief Set player's color.
     * @details Throws std::invalid_argument on invalid color.
     *          Note: %Player can't have Color::EMPTY color.
     * @see Color::ColorTypes
     * @param color %Player color
     */
    void setColor(int color);
    /**
     * @brief Set player's type.
     * @details Throws std::invalid_argument on invalid type.
     * @see Player::PlayerType
     * @param type Player type
     */
    void setType(int type);
    /**
     * @brief Set player's score.
     * @details If given score is lower than zero, it's automatically set
     *          to zero.
     * @param score Player score
     */
    void setScore(int score);

    /**
     * @brief Get player's name.
     * @return Constant reference to player's name
     */
    const std::string &getName() const;
    /**
     * @brief Get player's color.
     * @see Color::ColorTypes
     * @return %Player's color code
     */
    int getColor() const;
    /**
     * @brief Get player's type.
     * @see Player::PlayerType
     * @return %Player's type
     */
    int getType() const;
    /**
     * @brief Get player's score.
     * @return %Player's score
     */
    int getScore() const;

    /**
     * @brief Add x value to player's score.
     * @see setScore()
     * @param x Value to add to player's score
     */
    void addToScore(int x);
    /**
     * @brief Subtract x value from player's score.
     * @see setScore()
     * @param x Value to subtract from player's score
     */
    void subFromScore(int x);

    /**
     * @brief Placeholder for AI's logic - overriden in AI class.
     * @details Throws std::runtime_error when called on Player class.
     * @see AI::makeTurn()
     */
    virtual Coordinate makeTurn(const Board *b) {
        throw std::runtime_error("makeTurn() not implemented");
    };

    /**
     * @brief %Player type.
     */
    enum PlayerType {
        HUMAN,  /**< %Player is a human */
        AI      /**< %Player is an %AI */
    };

protected:
    std::string m_name; /**< %Player name */
    Color m_color;      /**< %Player color */
    int m_score;        /**< %Player score */
    int m_type;         /**< %Player type */
};

#endif
