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
 * Ship class declaration
 *
 */
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
