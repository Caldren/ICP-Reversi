#ifndef __HISTORYITEM_INCLUDED_HPP
#define __HISTORYITEM_INCLUDED_HPP

#include <vector>
#include "Coordinate.hpp"

class HistoryItem {
public:
    HistoryItem(int px, int py, int pcolor, 
        const std::vector<Coordinate> &pstones) :
        x(px), y(py), color(pcolor), stones(pstones.begin(), pstones.end()) {}

    int x;
    int y;
    int color;
    std::vector<Coordinate> stones;
};

#endif
