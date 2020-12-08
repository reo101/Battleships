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
    Ship(int _size) : size(_size) {}
    Ship(int _size, Coordinates _coords) : size(_size), coords(_coords) {}
};

class Player {
  public:
    Player();
    Player(std::string);

    void initBoard();
    void initPlayer();
    void drawBoard();

    void addShip();
    void addShipAtLocation(int);
    bool tryPlacingShip(int, int, int, char);
    void editShip();
    void resetBoard();
    void commitBoard();

    void clearScreen();

  private:
    // 0 -> water, 1-> ship, 2 -> hit water, 3 -> sunken ship
    unsigned short board[BOARD_SIZE][BOARD_SIZE] = {};
    std::vector<std::vector<Ship>> remainingShips = {
        std::vector<Ship>(4, Ship(2)), std::vector<Ship>(3, Ship(3)),
        std::vector<Ship>(2, Ship(4)), std::vector<Ship>(1, Ship(6))};
    std::vector<std::vector<Ship>> ships = {
        std::vector<Ship>(), std::vector<Ship>(), std::vector<Ship>(),
        std::vector<Ship>()};
    std::string playerName;
};

// 4 x OO
// 3 x OOO
// 2 x OOOO
// 1 x OOOOOO

int main() {

    Player test;

    test.initBoard();

    return 0;
}

Player::Player() {
    // Blank constructor
    // board[4][4] = 1;
    // board[4][5] = 3;
    // board[4][6] = 3;
    // board[4][7] = 1;
    // board[2][3] = 2;
    // board[1][2] = 1;
    // board[2][2] = 1;
    // board[3][2] = 1;
}

Player::Player(std::string path) {
    // Import data from file
}

void Player::initBoard() {
    // initPlayer(); //FIXME
    char option;
    bool wasInvalid = false;
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
        if (wasInvalid) {
            std::cout << "Invalid option \"" << option << "\" selected"
                      << std::endl
                      << std::endl;
        }
        wasInvalid = false;
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
            break;
        default:
            wasInvalid = true;
        }
    } while (option != '4');
}

void Player::initPlayer() {
    clearScreen();
    std::cout << std::endl << "Choose player name:" << std::endl;
    std::cin >> playerName;
}

// ╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝
// ╔═══╗
// ║   ║
// ╚═══╝
// ╔═╦═╗
// ╠═╬═╣
// ╚═╩═╝
// ╔═══╦═══╗
// ║   ║   ║
// ╠═══╬═══╣
// ║   ║   ║
// ╚═══╩═══╝
// ╔═════╦═════╗
// ║     ║     ║
// ║     ║     ║
// ╠═════╬═════╣
// ║     ║     ║
// ║     ║     ║
// ╚═════╩═════╝
void Player::drawBoard() {
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
        std::cout << "║ " << digits[row] << " ";
        for (int col = 0; col < BOARD_SIZE; ++col) {
            std::cout << "║" << rowBuffer[col];
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
    std::string errorMessage;
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
        if (wasInvalid) {
            std::cout << "Invalid option \"" << option << "\" selected "
                      << errorMessage << std::endl
                      << std::endl;
        }
        wasInvalid = false;
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
                    errorMessage = "No more ships of that kind";
                    continue;
                }
                addShipAtLocation(i);
                continue;
            }
        }
    } while (true);
}

void Player::addShipAtLocation(int index) {
    char option[3];
    int row, col;
    char direction;
    bool wasInvalid = false;
    std::string errorMessage;
    bool success;
    do {
        clearScreen();
        drawBoard();
        std::cout << std::endl
                  << "Select where to add a ship with length "
                  << remainingShips[index][0].size
                  << " (in format A1R [Column A-J, Row 1-X, Direction "
                     "Right/Left]) or 0 to go back:"
                  << std::endl
                  << std::endl;

        if (wasInvalid) {
            std::cout << "Invalid option \"" << option << "\" selected "
                      << errorMessage << std::endl
                      << std::endl;
        }
        wasInvalid = false;

        std::cin >> option;
        std::cin.clear();

        if (option[1] == '\0' && option[0] == '0') {
            return;
        }

        col = option[0] - 'A';
        if ((col < 0) || (col >= BOARD_SIZE)) {
            errorMessage = "Invalid column selected";
            wasInvalid = true;
            continue;
        }

        row = option[1] == 'X' ? BOARD_SIZE - 1 : option[1] - '1';
        if ((row < 0) || (row >= BOARD_SIZE)) {
            errorMessage = "Invalid row selected";
            wasInvalid = true;
            continue;
        }

        direction = option[2];
        if (direction != 'R' && direction != 'D') {
            errorMessage = "Invalid direction selected";
            wasInvalid = true;
            continue;
        }

        success = tryPlacingShip(index, col, row, direction);

        if (success) {
            std::cout << "Successfully added a ship" << std::endl;
            return;
        } else {
            wasInvalid = true;
            errorMessage = "Cant place a ship at these coordinates";
            continue;
        }

    } while (true);
}

bool Player::tryPlacingShip(int index, int col, int row, char direction) {

    int size = remainingShips[index][0].size;

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

    for (int i = 0; i < size; ++i) {
        board[row + rowOffset * i][col + colOffset * i] = 1;
    }

    remainingShips[index].pop_back();
    ships[index].push_back(Ship(size, Coordinates(row, col)));

    return true;
}

void Player::editShip() {
    // edit ship
}

void Player::resetBoard() {
    // reset board
}

void Player::commitBoard() {
    // commit board
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
