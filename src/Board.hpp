/**
 * @file Board.hpp
 * @class Board
 * @brief %Game board entity.
 *
 * This class contains game board an all
 * necessary methods for interaction with it.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#ifndef __BOARD_HPP_INCLUDED
#define __BOARD_HPP_INCLUDED

#include <iostream>
#include <set>
#include <vector>
#include <stdexcept>
#include "Color.hpp"
#include "Coordinate.hpp"

class Board {
public:
    /**
     * @brief Construct game board with specified size.
     * @details Throws std::range_error on invalid size.
     * @see SIZES
     * @param size Board size
     */
    Board(int size);
    Board(const Board &) = delete;
    ~Board();
    void operator=(const Board &) = delete;

    /**
     * @brief Get board size
     */
    int getSize() const;
    /**
     * @brief Get Color of field specified by given coordinations.
     * @details Throws std::range_error on invalid coordinations.
     * @see Color
     * @param x x axis
     * @param y y axis
     * @return Color code on given field
     */
    int getField(int x, int y) const;
    /**
     * @brief Set Color of given field
     * @details Throws std::range_error on invalid coordinations and
     *          std::invalid_argument on invalid Color.
     * @param x x axis
     * @param y y axis
     * @param val Color code
     */
    void setField(int x, int y, int val);
    /**
     * @brief Check if placing stone of given Color on given coords
     *        is a valid move.
     * @details If given turn is valid, coords vector will be populated
     *          with stones which will be taken by player of given color.
     * @see Coordinate
     * @param row x axis
     * @param col y axis
     * @param coords Coordinates of stones which will be changed to Color c
     * @param c Color of a stone
     * @return true if given turn is valid, false otherwise
     */
    bool checkTurn(int row, int col, std::vector<Coordinate> &coords,
                   int c) const;

    /**
     * @brief Helper function which allows printing Board matrix directly
     *        via std::ostream streams.
     */
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
private:
    /**
     * @brief Set Board size.
     * @details Throws std::range_error on invalid size.
     * @see SIZES
     * @param size Size to set
     */
    void setSize(int size);
    /**
     * @brief Initialize Board matrix with given size.
     * @see setSize
     * @see initBoardArray
     * @param size Board size
     */
    void initBoard(int size);
    /**
     * @brief Allocate memory for Board matrix
     */
    void initBoardArray();

public:
    static const std::set<int> SIZES; /**< Valid Board sizes */

private:
    int m_size;
    Color **m_board = nullptr;
};

#endif
