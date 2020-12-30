#include "Game.hpp"

Game::Game(int playerCount, std::string fileName) {
    std::string path, playerName;
    for (int i = 0; i < playerCount; ++i) {
        path = "res/" + fileName + std::to_string(i + 1) + ".txt";
        // res/ + presetBoard + 1 + .txt = res/presetBoard1.txt

        clearScreen();
        if (fileExists(path)) {
            players.push_back(new Player(path));
            if (!players.back()->isBoardSet()) {
                std::cout << "Player " << (i + 1)
                          << " has an invalid preset board file. You'll now "
                             "enter the manual board builder."
                          << std::endl;
                players.back()->initBoard();
            } else {
                // players.back()->drawBoard(drawType::LABELS);
                std::cout << "Player " << (i + 1)
                          << " has a valid preset board file!" << std::endl;
            }
        } else {
            std::cout << "Player " << (i + 1)
                      << " has no preset board file.  You'll now "
                         "enter the manual board builder."
                      << std::endl;
            players.push_back(new Player());
            players.back()->initBoard();
        }
        std::cout << "Enter Player " << (i + 1) << " name: ";
        std::cin >> playerName;
        // Set the selected player name
        players.back()->setPlayerName(playerName);
        // Stall to let user see the status messages
        std::cin.get();
    }

    // All players are now fully init-ed
    start();
}

Game::~Game() {
    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}

void Game::start() {
    // Game Loop
}

bool fileExists(std::string fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}
