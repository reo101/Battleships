#include "Coordinates.hpp"

struct Ship {
    const int size;
    Coordinates coords;
    char direction;
    Ship(const Ship &ship)
        : size(ship.size), coords(ship.coords.x, ship.coords.y),
          direction(ship.direction) {}
    Ship(int size) : size(size), direction() {}
    Ship(int size, int x, int y, char direction)
        : size(size), coords(x, y), direction(direction) {}
};
