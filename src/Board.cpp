#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Board.hpp"

using namespace std;

Board::Board()
{
    initBoard(DEFAULT_SIZE);
}

Board::Board(int size)
{
    initBoard(size);
}

Board::~Board()
{
    for(int i = 0; i < size; i++)
        delete [] board[i];

    delete [] board;
    board = nullptr;
}

int Board::getSize()
{
    return size;
}

int Board::getField(int x, int y)
{
    if(x < 0 || x >= size || y < 0 || y >= size)
        throw std::range_error("Field coordinates are out of range");

    return board[x][y];
}

void Board::setField(int x, int y, int val)
{
    if(x < 0 || x >= size || y < 0 || y >= size)
        throw std::range_error("Field coordinates are out of range");

    if(val != BLACK && val != EMPTY && val != WHITE)
        throw std::invalid_argument("Invalid field value - must be: "
                                    "BLACK, EMPTY or WHITE");

    board[x][y] = val;
}

ostream& operator<<(ostream &out, const Board &b)
{
    if(b.board != nullptr) {
        for(int row = 0; row < b.size; row++) {
            for(int col = 0; col < b.size; col++) {
                out << setw(2) << (char)b.board[row][col] << " ";
            }

            out << endl;
        }
    }

    return out;
}

/* PRIVATE METHODS */
void Board::setSize(int size)
{
    if(SIZES.find(size) == SIZES.end())
        throw std::range_error("Size must be 6, 8, 10 or 12");

    this->size = size;
}

void Board::initBoard(int size)
{
    setSize(size);
    initBoardArray();
}

void Board::initBoardArray()
{
    board = new int*[size];

    for(int i = 0; i < size; i++) {
        board[i] = new int[size];
        std::fill_n(board[i], size, EMPTY);
    }
}

const std::set<int> Board::SIZES {6, 8, 10, 12};
