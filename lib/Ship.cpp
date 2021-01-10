/**
 *
 * Solution to course project # 5
 * Introduction to programming course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2020/2021
 *
 * @author Pavel Atanasov
 * @idnumber 62555
 * @compiler GCC
 *
 * Ship class implementation
 *
 */
#include "Ship.hpp"

Ship::Ship(const Ship &ship)
    : size(ship.size), coords(ship.coords.x, ship.coords.y),
      direction(ship.direction) {}
Ship::Ship(int size) : size(size), direction() {}
Ship::Ship(int size, int x, int y, char direction)
    : size(size), coords(x, y), direction(direction) {}
