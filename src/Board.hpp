#ifndef __BOARD_HPP_INCLUDED
#define __BOARD_HPP_INCLUDED

#include <set>

class Board {
public:
    Board(int size) { setSize(size); }
    Board()         { setSize(8);    }

    void setSize(int size);
    int getSize() { return size; }

private:
    static const std::set<int> SIZES;
    int size;
};

#endif
