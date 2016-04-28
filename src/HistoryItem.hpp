/**
 * @file HistoryItem.hpp
 * @class HistoryItem
 * @see History
 * @brief An entity for keeping information about single turn in game history.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#ifndef __HISTORYITEM_INCLUDED_HPP
#define __HISTORYITEM_INCLUDED_HPP

#include <vector>
#include "Coordinate.hpp"

class HistoryItem {
public:
    /**
     * @brief Create HistoryItem object with information about current turn.
     * @see Coordinate
     * @param px x coordinate of the turn
     * @param py y coordinate of the turn
     * @param pcolor Color of a player in the turn
     * @param pstones Vector of stones changed in the turn
     */
    HistoryItem(int px, int py, int pcolor,
        const std::vector<Coordinate> &pstones) :
        x(px), y(py), color(pcolor), stones(pstones.begin(), pstones.end()) {}

    int x;      /**< x coordinate of the turn */
    int y;      /**< y coordinate of the turn */
    int color;  /**< Color of player in the turn */
    std::vector<Coordinate> stones; /**< Vector of stones changed i
                                         in the turn */
};

#endif
