#ifndef __BOARD_HPP_INCLUDED
#define __BOARD_HPP_INCLUDED

#include <iostream>
#include <set>

class Board {
public:
    Board();
    Board(int size);
    ~Board();

    int getSize();
    int getField(int x, int y);

    void setField(int x, int y, int val);

    friend std::ostream &operator<<(std::ostream &out, const Board &b);
    enum FieldState {
        BLACK = 'B',
        EMPTY = 'E',
        WHITE = 'W',
    };
private:
    void setSize(int size);
    void initBoard(int size);
    void initBoardArray();

private:
    static const int DEFAULT_SIZE = 8;
    static const std::set<int> SIZES;
    int size;
    int **board = nullptr;
};

#endif
