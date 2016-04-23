#ifndef __BOARD_HPP_INCLUDED
#define __BOARD_HPP_INCLUDED

#include <iostream>
#include <set>
#include "Color.hpp"

class Board {
public:
    Board(int size);
    ~Board();

    int getSize() const;
    int getField(int x, int y) const;

    void setField(int x, int y, int val);

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
private:
    void setSize(int size);
    void initBoard(int size);
    void initBoardArray();

private:
    static const std::set<int> SIZES;
    int m_size;
    Color **m_board = nullptr;
};

#endif
