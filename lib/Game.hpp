/**
 *
 * Solution to course project # 5
 * Introduction to programming course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2020/2021
 *
 * @author Pavel Atanasov
 * @idnumber 62555
 * @compiler GCC
 *
 * Player class declaration
 *
 */
#ifndef GAME_H_
#define GAME_H_

#include "Player.hpp"
#include <vector>

class Game {
  public:
    Game(int, std::string);
    ~Game();

  private:
    bool chooseAction(Player *, Player *);
    void start();
    std::vector<Player *> players;
};

bool fileExists(std::string);
#endif // GAME_H_
