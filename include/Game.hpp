#include "Player.hpp"
#include <iostream>

class Game {
  public:
    Game(int);
    ~Game();

  private:
    std::vector<Player *> players;
};

bool fileExists(std::string fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

Game::Game(int playerCount) {
    std::string fileName;
    for (int i = 0; i < playerCount; ++i) {
        fileName = "presetBoard";
        fileName += (i + 1);
        if (fileExists(fileName)) {
            players.push_back(new Player(fileName));
            if (!players.back()->isBoardSet()) {
                std::cout << "Player " << (i + 1)
                          << " has an invalid preset board file. Press Enter "
                             "to go into manual board builder"
                          << std::endl;
                std::cin.get();
                players.back()->initBoard();
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
    for (int i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}
