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
};

class Player {
  public:
    Player();
    Player(std::string);

    void initBoard();
    void initPlayer();
    void drawBoard();

    void addShip();
    void editShip();
    void resetBoard();
    void commitBoard();

    void clearScreen();

  private:
    // 0 -> water, 1-> hit water, 2 -> ship, 3 -> sunken ship
    int board[BOARD_SIZE][BOARD_SIZE] = {};
    std::vector<std::vector<Ship>> ships = {
        std::vector<Ship>(4, Ship(2)), std::vector<Ship>(3, Ship(3)),
        std::vector<Ship>(2, Ship(4)), std::vector<Ship>(1, Ship(6))};
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
    board[4][4] = 2;
    board[4][5] = 3;
    board[4][6] = 3;
    board[4][7] = 2;
    board[2][3] = 1;
    board[1][2] = 2;
    board[2][2] = 2;
    board[3][2] = 2;
}

Player::Player(std::string path) {
    // Import data from file
}

void Player::initBoard() {
    initPlayer();
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
    std::cin >> playerName; // FIXME
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
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
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
                rowBuffer[col] = " \033[1mX\033[0m ";
                // rowBuffer[col] = " X ";
                break;
            case 2: // ship
                rowBuffer[col] = "\033[7;1m   \033[0m";
                // rowBuffer[col] = " ◯ ";
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
    do {
        clearScreen();
        drawBoard();
        std::cout << std::endl
                  << "Select which ship to add:" << std::endl
                  << std::endl;
        for (size_t i = 0, count; i < ships.size(); ++i) {
            count = 0;
            for (int j = 0; j < ships[i].size(); ++j) {
                if (!ships[i][j].coords.areSet()) {
                    ++count;
                }
            }

            if (count == 0) {
                invertColours();
            }

            std::cout << (i + 1) << ". ";
            printChar(ships[i][0].size, 'X');

            std::cout << std::setw(15 - ships[i][0].size) << count << " left"
                      << std::endl;

            if (count == 0) {
                revertColours();
            }
        }

        std::cout << "0. Go back to main menu" << std::endl << std::endl;
        if (wasInvalid) {
            std::cout << "Invalid option \"" << option << "\" selected"
                      << std::endl
                      << std::endl;
        }
        wasInvalid = false;
        std::cin >> option;
        std::cin.clear();

    } while (true);
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
