#include <iostream>
#include <string>
#include <vector>

const int BOARD_SIZE = 10;

void printLine(int count, std::string str, bool newLine = true,
               std::string finally = "") {
    for (int i = 0; i < count; ++i) {
        std::cout << str;
    }
    std::cout << finally;
    if (newLine) {
        std::cout << std::endl;
    }
}

class Board {
  public:
    Board() {
        board[4][5] = 3;
        board[2][3] = 2;
        board[1][2] = 1;
    }

    void drawBoard() {
        printLine(BOARD_SIZE * 4 + 5, "-");
        char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                          'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'};
        char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        printLine(BOARD_SIZE + 1, "|   ", true, "|");
        std::cout << "|   ";
        for (int i = 0; i < BOARD_SIZE; ++i) {
            std::cout << "| " << letters[i] << " ";
        }
        std::cout << "|" << std::endl;
        printLine(BOARD_SIZE + 1, "|   ", true, "|");
        printLine(BOARD_SIZE * 4 + 5, "-");
        std::vector<std::string> rowBuffer[BOARD_SIZE + 1];
        rowBuffer[BOARD_SIZE] = {"   ", " T ", "   "};
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                switch (board[row][col]) {
                case 0: // water
                    rowBuffer[col] = {"   ", "   ", "   "};
                    break;
                case 1: // hit water
                    rowBuffer[col] = {"\\ /", " X ", "/ \\"};
                    break;
                case 2: // ship
                    rowBuffer[col] = {"🚢🚢🚢", "🚢🚢🚢", "🚢🚢🚢"};
                    break;
                case 3: // sunken ship
                    rowBuffer[col] = {"\\🚢/", "🚢X🚢", "/🚢\\"};
                    break;
                }
            }
            for (int i = 0; i < 3; ++i) {
                std::cout << "|" << rowBuffer[BOARD_SIZE][i];
                for (int col = 0; col < BOARD_SIZE; ++col) {
                    std::cout << "|" << rowBuffer[col][i];
                }
                std::cout << "|" << std::endl;
            }
            printLine(BOARD_SIZE * 4 + 5, "-");
        }
    }

  private:
    int board[BOARD_SIZE][BOARD_SIZE] =
        {}; // 0 -> water, 1-> hit water, 2 -> ship, 3 -> sunken ship
    int unsunkenShipsCount;
};

// 4 x OO
// 3 x OOO
// 2 x OOOO
// 1 x OOOOOO

int main() {

    Board test;
    test.drawBoard();

    return 0;
}
