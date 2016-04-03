#include <iostream>
#include <stdexcept>
#include "Board.hpp"

using namespace std;

void Board::setSize(int size)
{
    if(SIZES.find(size) == SIZES.end())
        throw invalid_argument("Size must be 6, 8, 10 or 12");

    this->size = size;
}

const std::set<int> Board::SIZES {6, 8, 10, 12};
