#ifndef __COORDINATE_HPP_INCLUDED
#define __COORDINATE_HPP_INCLUDED

class Coordinate {
public:
    Coordinate() : x(0), y(0) {}
    Coordinate(int px, int py) : x(px), y(py) {}

    static bool comp(const Coordinate &c1, const Coordinate &c2) {
        return (c1.x == c2.x && c1.y == c2.y);
    }

    int x;
    int y;
};

#endif
