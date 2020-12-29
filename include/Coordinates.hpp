const int BOARD_SIZE = 10;

class Coordinates {
  public:
    unsigned short x, y;
    bool areSet;

    Coordinates() : x(), y(), areSet(false) {}
    Coordinates(const Coordinates &obj)
        : x(obj.x), y(obj.y), areSet(obj.areSet) {}
    Coordinates(unsigned short x, unsigned short y) { // : x(_x), y(_y) {}
        set(x, y);
    }

    void set(unsigned short x, unsigned short y) {
        if (x >= BOARD_SIZE || y >= BOARD_SIZE) {
            return;
        }
        this->x = x;
        this->y = y;
        areSet = true;
    }
};
