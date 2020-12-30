#include "../lib/Game.hpp"
#include <iostream>

int main() {

    // Player player1("./presetBoard1.txt"), player2("./presetBoard2.txt");

    // player1.drawBoard(drawType::NORMAL);
    // player1.drawBoard(drawType::LABELS);
    // player1.drawBoard(drawType::ENEMYPOV);

    Game game(2, "presetBoard");

    return 0;
}
