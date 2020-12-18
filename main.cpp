#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h> //temp for clearing screen
#include <string>
#include <vector>

const int BOARD_SIZE = 10;

void printLine(int, std::string, std::string, std::string, std::string);
void printChar(int, char);
void invertColours();
void revertColours();

class Coordinates {
  private:
    bool coordsSet = false;

  public:
    unsigned short x, y;

    Coordinates() : x(), y() {}
    Coordinates(unsigned short _x, unsigned short _y) { // : x(_x), y(_y) {}
        set(_x, _y);
    }

    void set(unsigned short _x, unsigned short _y) {
        if (x >= BOARD_SIZE || y >= BOARD_SIZE) {
            return;
        }
        x = _x;
        y = _y;
        coordsSet = true;
    }

    bool areSet() { return coordsSet; }
};

struct Ship {
    const int size;
    Coordinates coords;
    char direction;
    Ship(const Ship &ship)
        : size(ship.size), coords(ship.coords.x, ship.coords.y) {}
    Ship(int _size) : size(_size) {}
    Ship(int _size, int _x, int _y, char _direction)
        : size(_size), coords(_x, _y), direction(_direction) {}
};

class Player {
  public:
    Player();
    Player(std::string);

    void initBoard();
    void initPlayer();
    void drawBoard(bool = false);

    void addShip();
    void selectCoordinatesForShip(int, bool = true);
    bool tryPlacingShip(int, int, int, char, bool = true);
    void editShip();
    void tryChaningCoordinatesForShip(int);
    void hideShip(int);
    void showShip(int);
    void resetBoard();
    bool commitBoard();

    void clearScreen();

  private:
    // 0 -> water, 1-> ship, 2 -> hit water, 3 -> sunken ship
    unsigned short board[BOARD_SIZE][BOARD_SIZE] = {};
    std::vector<std::vector<Ship>> remainingShips = {
        std::vector<Ship>(4, Ship(2)), std::vector<Ship>(3, Ship(3)),
        std::vector<Ship>(2, Ship(4)), std::vector<Ship>(1, Ship(6))};
    std::vector<Ship *> ships;
    std::string playerName;
};

int main() {

    Player test;

    test.initBoard();

    return 0;
}

Player::Player() {
    // Blank constructor
    ships.reserve(10); // FIXME magic number
}

Player::Player(std::string path) {
    // Import data from file
    std::ifstream preset(path, std::ios::in);

    char cellBuffer;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            preset >> cellBuffer;

            switch (cellBuffer) {
            case '1':
                board[i][j] = 1;
            default:
            case '0':
                board[i][j] = 0;
                break;
            }
        }
    }
}

void Player::initBoard() {
    // initPlayer(); //FIXME
    char option;
    bool wasInvalid = false;
    std::string message;
    do {
        clearScreen();
        drawBoard();
        std::cout << std::endl
                  << "Please select an option:\n\n"
                     "1. Add ship\n"
                     "2. Edit ship\n"
                     "3. Reset board\n"
                     "4. Commit board\n"
                  << std::endl;
        if (message.length() > 0) {
            if (wasInvalid) {
                std::cout << "Error!" << std::endl;
                wasInvalid = false;
            }
            std::cout << message << std::endl << std::endl;
            message = "";
        }
        std::cin >> option;
        std::cin.clear();
        switch (option) {
        case '1':
            addShip();
            break;
        case '2':
            editShip();
            break;
        case '3':
            resetBoard();
            break;
        case '4':
            commitBoard();
            if (!commitBoard()) {
                wasInvalid = true;
                message = "Please first place all ships before committing";
            }
            break;
        default:
            wasInvalid = true;
        }
    } while (true);
}

void Player::initPlayer() {
    clearScreen();
    std::cout << std::endl << "Choose player name:" << std::endl;
    std::cin >> playerName;
}

void Player::drawBoard(bool drawLabels) { // Default value set in prototype
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                      'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};
    char digits[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'X'};
    // First line - above LETTERS
    printLine(BOARD_SIZE + 1, "═══", "╔", "╦", "╗");

    // Second line - LETTERS
    std::cout << "║ \\ ";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::cout << "║ " << letters[i] << " ";
    }
    std::cout << "║" << std::endl;

    // Third line - below LETTERS
    printLine(BOARD_SIZE + 1, "═══", "╠", "╬", "╣");

    // Main lines - with DIGITS
    std::string rowBuffer[BOARD_SIZE];
    for (int row = 0; row < BOARD_SIZE; ++row) { // For each row...
        // Make a 1-line rowBuffer
        for (int col = 0; col < BOARD_SIZE; ++col) {
            switch (board[row][col]) {
            case 0: // water
                rowBuffer[col] = " \033[m \033[0m ";
                // rowBuffer[col] = "   ";
                break;
            case 1: // hit water
                rowBuffer[col] = "\033[7;1m   \033[0m";
                // rowBuffer[col] = " ◯ ";
                break;
            case 2: // ship
                rowBuffer[col] = " \033[1mX\033[0m ";
                // rowBuffer[col] = " X ";
                break;
            case 3: // sunken ship
                rowBuffer[col] = "\033[7;1m X \033[0m";
                // rowBuffer[col] = " ∅ ";
                break;
            }
        }
        // And print that buffer togheter with the line separator
        bool shipHeadFound;
        std::cout << "║ " << digits[row] << " ";
        for (int col = 0; col < BOARD_SIZE; ++col) {
            std::cout << "║";
            if (drawLabels) {
                for (size_t i = 0; i < ships.size(); ++i) {
                    // std::cout << "Checking if col/row " << col << "/" << row
                    //<< " is a ship at x/y " << ships[i]->coords.x
                    //<< "/" << ships[i]->coords.y << std::endl;
                    if (ships[i]->coords.x == col &&
                        ships[i]->coords.y == row) {

                        invertColours();
                        std::cout << " " << letters[i] << " ";
                        revertColours();

                        shipHeadFound = true;
                        break;
                    }
                }
            }
            if (shipHeadFound) {
                shipHeadFound = false;
                continue;
            } else {
                std::cout << rowBuffer[col];
            }
        }
        std::cout << "║" << std::endl;
        bool inMiddle = row < BOARD_SIZE - 1;
        printLine(BOARD_SIZE + 1, "═══", (inMiddle ? "╠" : "╚"),
                  (inMiddle ? "╬" : "╩"), (inMiddle ? "╣" : "╝"));
    }
}

void Player::addShip() {
    // add ship
    char option;
    bool wasInvalid = false;
    std::string message;
    do {
        clearScreen();
        drawBoard();
        std::cout << std::endl
                  << "Select which ship to add:" << std::endl
                  << std::endl;
        for (size_t i = 0, count; i < remainingShips.size(); ++i) {
            count = remainingShips[i].size();
            if (count == 0) {
                invertColours();
            }

            std::cout << (i + 1) << ". ";
            printChar(remainingShips[i][0].size, 'X');

            std::cout << std::setw(15 - remainingShips[i][0].size) << count
                      << " left" << std::endl;

            if (count == 0) {
                revertColours();
            }
        }

        std::cout << "0. Go back to main menu" << std::endl << std::endl;
        if (message.length() > 0) {
            if (wasInvalid) {
                std::cout << "Error!" << std::endl;
                wasInvalid = false;
            }
            std::cout << message << std::endl << std::endl;
            message = "";
        }
        std::cin >> option;
        std::cin.clear();

        if (option == '0') {
            return;
        }

        if (option - '1' < 0 || option - '1' > (int)remainingShips.size()) {
            std::cout << "Invalid option selected" << std::endl;
            wasInvalid = true;
            continue;
        }

        for (int i = 0; i < (int)remainingShips.size(); ++i) {
            if (i == option - '1') {
                if (remainingShips[i].size() == 0) {
                    wasInvalid = true;
                    message = "No more ships of that kind";
                    continue;
                }
                selectCoordinatesForShip(i);
                continue;
            }
        }
    } while (true);
}

void Player::selectCoordinatesForShip(int index, bool isNew) {
    char option[3];
    int row, col;
    char direction;
    bool wasInvalid = false;
    std::string message;
    bool success;
    do {
        clearScreen();
        drawBoard();
        std::cout << std::endl
                  << "Select where to add a ship with length "
                  << (isNew ? remainingShips[index][0].size
                            : ships[index]->size)
                  << " (in format A1R [Column A-J, Row 1-X, Direction "
                     "Right/Left]) or 0 to go back:"
                  << std::endl
                  << std::endl;

        if (message.length() > 0) {
            if (wasInvalid) {
                std::cout << "Error!" << std::endl;
                wasInvalid = false;
            }
            std::cout << message << std::endl << std::endl;
            message = "";
        }

        std::cin >> option;
        std::cin.clear();

        if (option[1] == '\0' && option[0] == '0') {
            return;
        }

        col = option[0] - 'A';
        if ((col < 0) || (col >= BOARD_SIZE)) {
            message = "Invalid column selected";
            wasInvalid = true;
            continue;
        }

        row = option[1] == 'X' ? BOARD_SIZE - 1 : option[1] - '1';
        if ((row < 0) || (row >= BOARD_SIZE)) {
            message = "Invalid row selected";
            wasInvalid = true;
            continue;
        }

        direction = option[2];
        if (direction != 'R' && direction != 'D') {
            message = "Invalid direction selected";
            wasInvalid = true;
            continue;
        }

        success = tryPlacingShip(index, col, row, direction, isNew);

        if (success) {
            // message = "Successfully added a ship";
            return;
        } else {
            message = "Cant place a ship at these coordinates";
            wasInvalid = true;
            continue;
        }
    } while (true);
}

bool Player::tryPlacingShip(int index, int col, int row, char direction,
                            bool isNew) {

    int size = (isNew ? remainingShips[index][0].size : ships[index]->size);

    int rowOffset = 0, colOffset = 0;

    switch (direction) {
    case 'D':
        rowOffset = 1;
        break;
    case 'R':
        colOffset = 1;
        break;
    }

    if (row + size * rowOffset > BOARD_SIZE ||
        col + size * colOffset > BOARD_SIZE) {
        return false;
    }

    for (int i = 0; i < size; ++i) {
        if (board[row + rowOffset * i][col + colOffset * i] != 0) {
            return false;
        }
    }

    for (int i = row - 1; i <= row + 1 + rowOffset * size; ++i) {
        if ((i < 0) || (i >= BOARD_SIZE)) {
            continue;
        }
        for (int j = col - 1; j <= col + 1 + colOffset * size; ++j) {
            if ((j < 0) || (j >= BOARD_SIZE)) {
                continue;
            }

            if (board[i][j] != 0) {
                return false;
            }
        }
    }

    if (isNew) {
        // Add new ship with set data
        ships.push_back(new Ship(size, col, row, direction));
        remainingShips[index].pop_back();

        showShip(ships.size() - 1);
    } else {
        // Edit exisiting ship data
        ships[index]->coords.x = col;
        ships[index]->coords.y = row;
        ships[index]->direction = direction;

        showShip(index);
    }

    return true;
}

void Player::editShip() {
    // edit ship
    char option;
    bool wasInvalid = false;
    std::string message;
    do {
        clearScreen();
        drawBoard(true);
        std::cout << std::endl
                  << "Select which ship to add or 0 to go back to main menu:"
                  << std::endl
                  << std::endl;

        if (message.length() > 0) {
            if (wasInvalid) {
                std::cout << "Error!" << std::endl;
                wasInvalid = false;
            }
            std::cout << message << std::endl << std::endl;
            message = "";
        }
        std::cin >> option;
        std::cin.clear();

        if (option == '0') {
            return;
        }

        std::cout << (option - 'A') << std::endl;
        std::cout << ((int)ships.size()) << std::endl;
        std::cin.get();
        if (option - 'A' < 0 || option - 'A' > (int)ships.size()) {
            std::cout << "Invalid option selected" << std::endl;
            wasInvalid = true;
            continue;
        }

        tryChaningCoordinatesForShip(option - 'A');
    } while (true);
}

void Player::tryChaningCoordinatesForShip(int index) {
    hideShip(index);
    selectCoordinatesForShip(index, false);
    // showShip(index);
}

void Player::hideShip(int index) {
    int xOffset = 0, yOffset = 0;

    (ships[index]->direction == 'R' ? xOffset : yOffset) = 1;

    for (int i = 0; i < ships[index]->size; ++i) {
        board[ships[index]->coords.y + yOffset * i]
             [ships[index]->coords.x + xOffset * i] = 0;
    }
}

void Player::showShip(int index) {
    int xOffset = 0, yOffset = 0;

    (ships[index]->direction == 'R' ? xOffset : yOffset) = 1;

    for (int i = 0; i < ships[index]->size; ++i) {
        board[ships[index]->coords.y + yOffset * i]
             [ships[index]->coords.x + xOffset * i] = 1;
    }
}

void Player::resetBoard() {
    // reset board
    char option;
    do {
        clearScreen();
        drawBoard();
        std::cout
            << std::endl
            << std::endl
            << "Are you sure you want to reset the board (unreversable) (y/n)"
            << std::endl;
        std::cin >> option;
        if (option == 'n') {
            return;
        }
    } while (option != 'y');

    remainingShips[0] = std::vector<Ship>(4, Ship(2));
    remainingShips[1] = std::vector<Ship>(3, Ship(3));
    remainingShips[2] = std::vector<Ship>(2, Ship(4));
    remainingShips[3] = std::vector<Ship>(1, Ship(6));

    ships.clear();

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j] = 0;
        }
    }
}

bool Player::commitBoard() {
    // commit board
    return ships.size() == 10; // FIXME magic number
}

void Player::clearScreen() {
    system("clear"); // temp
    // print ~50 emptylines
}

void printLine(int count, std::string str, std::string before = "",
               std::string between = "", std::string after = "") {
    std::cout << before;
    for (int i = 0; i < count; ++i) {
        std::cout << str;
        if (i < count - 1) {
            std::cout << between;
        }
    }
    std::cout << after << std::endl;
}

void printChar(int count, char ch) {
    for (int i = 0; i < count; ++i) {
        std::cout << ch;
    }
}

void invertColours() { std::cout << "\033[7;1m"; }
void revertColours() { std::cout << "\033[0m"; }
