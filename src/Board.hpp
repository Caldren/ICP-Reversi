#ifndef __BOARD_HPP_INCLUDED
#define __BOARD_HPP_INCLUDED

#include <iostream>
#include <set>
#include <vector>
#include "Color.hpp"
#include "Coordinate.hpp"

class Board {
public:
    Board(int size);
    ~Board();

    int getSize() const;
    int getField(int x, int y) const;

    void setField(int x, int y, int val);
    bool checkTurn(int row, int col, std::vector<Coordinate> &coords,
                   int c) const;

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
private:
    void setSize(int size);
    void initBoard(int size);
    void initBoardArray();

public:
    static const std::set<int> SIZES;

private:
    int m_size;
    Color **m_board = nullptr;
};

#endif
