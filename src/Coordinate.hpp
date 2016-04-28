/**
 * @file Coordinate.hpp
 * @class Coordinate
 * @brief Simple entity for keeping 2D coordinations.
 *
 * @author Frantisek Sumsal <xsumsa01@stud.fit.vutbr.cz>
 * @date 28.04.2016
 */
#ifndef __COORDINATE_HPP_INCLUDED
#define __COORDINATE_HPP_INCLUDED

class Coordinate {
public:
    /**
     * @brief Create Coordinate object with default coordinations 0;0.
     */
    Coordinate() : x(0), y(0) {}
    /**
     * @brief Create Coordinate object with given coordinations.
     * @param px x axis
     * @param py y axis
     */
    Coordinate(int px, int py) : x(px), y(py) {}

    /**
     * @brief Compare two Coordinate objects.
     * @details Method compares x and y coordinates of objects.
     * @param c1 First Coordinate object
     * @param c2 Second Coordinate object
     * @return true if x and y coordinates of given objects are equal,
     *         false otherwise
     */
    static bool comp(const Coordinate &c1, const Coordinate &c2) {
        return (c1.x == c2.x && c1.y == c2.y);
    }

    int x; /**< x coordinate */
    int y; /**< y coordinate */
};

#endif
