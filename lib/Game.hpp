#ifndef GAME_H_
#define GAME_H_

#include "Player.hpp"
#include <iostream>

class Game {
  public:
    Game(int, std::string);
    ~Game();

  private:
    void start();
    std::vector<Player *> players;
};

bool fileExists(std::string);
#endif // GAME_H_
