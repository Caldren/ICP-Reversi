/**
 * @file History.hpp
 * @class History
 * @see HistoryItem
 * @brief An entity for keeping track of made game turns.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#ifndef __HISTORY_HPP_INCLUDED
#define __HISTORY_HPP_INCLUDED

#include <vector>
#include <cstdlib>
#include <string>
#include "Coordinate.hpp"
#include "HistoryItem.hpp"

class History {
public:
    /**
     * @brief Create an History object
     */
    History() : m_curr_idx(-1) {}

    /**
     * @brief Add a turn into game history
     * @see Coordinate
     * @see Color::ColorTypes
     * @param x x coordination of placed stone
     * @param y y coordination of placed stone
     * @param color Color of Player of given turn
     * @param stones Vector of coordinations to stones changed by this turn
     */
    void add(int x, int y, int color, const std::vector<Coordinate> &stones);
    /**
     * @brief Move back in history by one turn.
     * @see HistoryItem
     * @return Constant pointer to HistoryItem if a previous turn is available,
     *         nullptr otherwise
     */
    const HistoryItem *moveBack();
    /**
     * @brief Move forward in history by one turn.
     * @see HistoryItem
     * @return Constant pointer to HistoryItem if a next turn is available,
     *         nullptr otherwise
     */
    const HistoryItem *moveForward();
    /**
     * @brief Get an entire (or part of) history vector.
     * @see HistoryItem
     * @param only_current If set to true, method returns history from the
     *                     beginning to the currently selected turn.
     * @return COPY of the history vector.
     */
    std::vector<HistoryItem> getData(bool only_current = false);

private:
    int m_curr_idx;                      /**< Index of current HistoryItem */
    std::vector<HistoryItem> m_history;  /**< Vector of HistoryItems */
};

#endif
