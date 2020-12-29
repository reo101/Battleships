#ifndef SHIP_H_
#define SHIP_H_

#include "Coordinates.hpp"

struct Ship {
    const int size;
    Coordinates coords;
    char direction;

    Ship(const Ship &);
    Ship(int);
    Ship(int, int, int, char);
};
#endif // SHIP_H_
