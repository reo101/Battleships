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
