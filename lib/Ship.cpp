#include "Ship.hpp"

Ship::Ship(const Ship &ship)
    : size(ship.size), coords(ship.coords.x, ship.coords.y),
      direction(ship.direction) {}
Ship::Ship(int size) : size(size), direction() {}
Ship::Ship(int size, int x, int y, char direction)
    : size(size), coords(x, y), direction(direction) {}
