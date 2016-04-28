/**
 * @file History.cpp
 * @brief Implementation file of History class.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#include <string>
#include <fstream>
#include <stdexcept>
#include "History.hpp"

void History::add(int x, int y, int color,
        const std::vector<Coordinate> &stones)
{
    if(m_curr_idx < (int)(m_history.size() - 1))
        m_history.erase(m_history.begin() + m_curr_idx + 1, m_history.end());

    m_history.push_back(HistoryItem(x, y, color, stones));
    m_curr_idx++;
}

const HistoryItem *History::moveBack()
{
    if(m_curr_idx < 0)
        return nullptr;

    return &m_history[m_curr_idx--];
}

const HistoryItem *History::moveForward()
{
    if(m_curr_idx >= (int)(m_history.size() - 1))
        return nullptr;

    return &m_history[++m_curr_idx];
}

std::vector<HistoryItem> History::getData(bool only_current)
{
    if(only_current)
        return std::vector<HistoryItem>(m_history.begin(),
                                        m_history.begin() + m_curr_idx + 1);

    return m_history;
}
