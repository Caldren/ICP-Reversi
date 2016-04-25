#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "Board.hpp"

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

int Board::getSize() const
{
    return m_size;
}

int Board::getField(int x, int y) const
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

bool Board::checkTurn(int row, int col, std::vector<Coordinate> &coords,
                      int c) const
{
    std::vector<Coordinate> temp;
    int player_color = c;
    int opponent_color = (c == Color::BLACK) ? Color::WHITE : Color::BLACK;
    int color;

    // Can't place a stone on a non-empty field
    // getField() also throws an exception on invalid coords
    try {
        if(getField(row, col) != Color::EMPTY)
            return false;
    } catch(...) {
        return false;
    }

    // horizontal, left
    for(int i = col - 1; i >= 0; i--) {
        color = getField(row, i);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(row, i));
    }

    temp.clear();
    // horizontal, right
    for(int i = col + 1; i < getSize(); i++) {
        color = getField(row, i);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(row, i));
    }

    temp.clear();
    // vertical, up
    for(int i = row - 1; i >= 0; i--) {
        color = getField(i, col);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, col));
    }

    temp.clear();
    // vertical, down
    for(int i = row + 1; i < getSize(); i++) {
        color = getField(i, col);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, col));
    }

    temp.clear();
    // left diagonal, up
    for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        color = getField(i, j);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, j));
    }

    temp.clear();
    // left diagonal, down
    for(int i = row + 1, j = col + 1; i < getSize() &&
            j < getSize(); i++, j++) {
        color = getField(i, j);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, j));
    }

    temp.clear();
    // right diagonal, up
    for(int i = row - 1, j = col + 1; i >= 0 && j < getSize(); i--, j++) {
        color = getField(i, j);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, j));
    }

    temp.clear();
    // right diagonal, down
    for(int i = row + 1, j = col - 1; i < getSize() && j >= 0; i++, j--) {
        color = getField(i, j);
        if(color == player_color) {
            coords.insert(coords.end(), temp.begin(), temp.end());
            break;
        }

        if(color != opponent_color)
            break;

        temp.push_back(Coordinate(i, j));
    }

    // Player has to take at least one opponent's stone
    if(coords.size() == 0)
        return false;

    // Sort coords vector and remove duplicates
    std::vector<Coordinate>::iterator it;
    std::sort(coords.begin(), coords.end(), Coordinate::comp);
    it = std::unique(coords.begin(), coords.end(), Coordinate::comp);
    coords.resize(std::distance(coords.begin(), it));

    return true;
}

std::ostream& operator<<(std::ostream &out, const Board &b)
{
    if(b.m_board != nullptr) {
        for(int row = 0; row < b.m_size; row++) {
            for(int col = 0; col < b.m_size; col++) {
                out << std::setw(2) << (char)b.m_board[row][col] << " ";
            }

            out << std::endl;
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
