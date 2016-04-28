/**
 * @file AI.hpp
 * @class AI
 * @see Player
 * @brief %AI player entity.
 * @details Implementation of AI player algorithms.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#ifndef __AI_HPP_INCLUDED
#define __AI_HPP_INCLUDED

#include <vector>
#include "Player.hpp"

class AI : public Player {
public:
    /**
     * @brief Create AI player.
     * @param name AI name.
     * @param color AI color.
     */
    AI(const std::string &name, int color);
    /**
     * @brief Calculate next turn on given board according to selected AI
     *        algorithm.
     * @details If the next turn is impossible, function returns coordinates
     *          -1;-1 (x, y).
     *          Throws std::runtime_error when there's no available algorithm
     *          to apply.
     * @see Board
     * @see Coordinate
     * @param b Current game Board
     * @return Coordinates of the calculated turn.
     */
    Coordinate makeTurn(const Board *b);

    /**
     * @brief Get number of available AI algorithms.
     * @return Number of available AI algorithms.
     */
    static int getAlgorithmCount();
    /**
     * @brief Get currently selected algorithm.
     * @details Algorithms are indexed from zero.
     * @see getAlgorithmCount()
     * @return Algorithm id
     */
    int getAlgorithm();
    /**
     * @brief Set AI algorithm.
     * @details Algorithms are indexed from zero. Throws std::range_error when
     *          algorithm id is out of range of currently available algorithms.
     * @see getAlgorithmCount()
     * @param id Algorithm id
     */
    void setAlgorithm(int id);

private:
    /**
     * @brief Pick a turn with the highest score.
     */
    Coordinate algorithm1(const Board *b);
    /**
     * @brief Pick a turn with the lowest score.
     */
    Coordinate algorithm2(const Board *b);

private:
    /**
     * @brief Vector of pointers to available algorithm methods.
     */
    static std::vector<Coordinate (AI::*)(const Board *b)> m_algorithms;
    int m_curr_algo = 0; /**< Currently selected algorithm */
};

#endif
