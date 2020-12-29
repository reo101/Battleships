#ifndef GAME_H_
#define GAME_H_

#include "Player.hpp"
#include <iostream>

class Game {
  public:
    Game(int);
    ~Game();

  private:
    std::vector<Player *> players;
};

bool fileExists(std::string);
#endif // GAME_H_
