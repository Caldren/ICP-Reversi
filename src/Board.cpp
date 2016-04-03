#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "Board.hpp"

using namespace std;

Board::Board(int size)
{
    initBoard(size);
}

Board::~Board()
{
    for(int i = 0; i < m_size; i++)
        delete [] m_board[i];

    delete [] m_board;
    m_board = nullptr;
}

int Board::getSize()
{
    return m_size;
}

int Board::getField(int x, int y)
{
    if(x < 0 || x >= m_size || y < 0 || y >= m_size)
        throw std::range_error("Field coordinates are out of range");

    return m_board[x][y];
}

void Board::setField(int x, int y, int val)
{
    if(x < 0 || x >= m_size || y < 0 || y >= m_size)
        throw std::range_error("Field coordinates are out of range");

    if(!Color::isValid(val))
        throw std::invalid_argument("Invalid color");

    m_board[x][y] = val;
}

ostream& operator<<(ostream &out, const Board &b)
{
    if(b.m_board != nullptr) {
        for(int row = 0; row < b.m_size; row++) {
            for(int col = 0; col < b.m_size; col++) {
                out << setw(2) << (char)b.m_board[row][col] << " ";
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

    m_size = size;
}

void Board::initBoard(int size)
{
    setSize(size);
    initBoardArray();
}

void Board::initBoardArray()
{
    m_board = new Color*[m_size];

    for(int i = 0; i < m_size; i++) {
        m_board[i] = new Color[m_size];
    }
}

const std::set<int> Board::SIZES {6, 8, 10, 12};
