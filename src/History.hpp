#ifndef __HISTORY_HPP_INCLUDED
#define __HISTORY_HPP_INCLUDED

#include <vector>
#include <cstdlib>
#include <string>
#include "Coordinate.hpp"
#include "HistoryItem.hpp"

class History {
public:
    History() : m_curr_idx(-1) {}

    void add(int x, int y, int color, const std::vector<Coordinate> &stones);
    const HistoryItem *moveBack();
    const HistoryItem *moveForward();
    const std::vector<HistoryItem> *getData();

private:
    int m_curr_idx;
    std::vector<HistoryItem> m_history;
};

#endif
