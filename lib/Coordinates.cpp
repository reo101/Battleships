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
 * Coordinates class implementation
 *
 */
#include "Coordinates.hpp"

Coordinates::Coordinates() : x(), y(), areSet(false) {}
Coordinates::Coordinates(const Coordinates &obj)
    : x(obj.x), y(obj.y), areSet(obj.areSet) {}
Coordinates::Coordinates(unsigned short x,
                         unsigned short y) { // : x(_x), y(_y) {}
    set(x, y);
}

void Coordinates::set(unsigned short x, unsigned short y) {
    if (x >= BOARD_SIZE || y >= BOARD_SIZE) {
        return;
    }
    this->x = x;
    this->y = y;
    areSet = true;
}
