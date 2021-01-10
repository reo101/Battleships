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
 * Coordinates class declaration
 *
 */
#ifndef COORDINATES_H_
#define COORDINATES_H_

const int BOARD_SIZE = 10;

struct Coordinates {
    unsigned short x, y;
    bool areSet;

    Coordinates();
    Coordinates(const Coordinates &);
    Coordinates(unsigned short, unsigned short);

    void set(unsigned short, unsigned short);
};
#endif // COORDINATES_H_
