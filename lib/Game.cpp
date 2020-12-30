#include "Game.hpp"

Game::Game(int playerCount, std::string fileName) {
    std::string path;
    for (int i = 0; i < playerCount; ++i) {
        path = "res/" + fileName + std::to_string(i + 1) + ".txt";
        // res/ + presetBoard + 1 + .txt = res/presetBoard1.txt

        clearScreen();
        if (fileExists(path)) {
            players.push_back(new Player(path));
            if (!players.back()->isBoardSet()) {
                std::cout << "Player " << (i + 1)
                          << " has an invalid preset board file. Press Enter "
                             "to go into manual board builder"
                          << std::endl;
                std::cin.get();
                players.back()->initBoard();
            } else {
                players.back()->drawBoard(drawType::LABELS);
                std::cout
                    << "Player " << (i + 1)
                    << " has a valid preset board file! Press Enter to continue"
                    << std::endl;
                std::cin.get();
            }
        } else {
            std::cout << "Player " << (i + 1)
                      << " has no preset board file. Press Enter to go into "
                         "manual board builder"
                      << std::endl;
            std::cin.get();
            players.push_back(new Player());
            players.back()->initBoard();
        }
    }
}

Game::~Game() {
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}

bool fileExists(std::string fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}
