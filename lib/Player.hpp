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
#ifndef PLAYER_H_
#define PLAYER_H_

#include "Ship.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace drawType {
enum drawType { NORMAL = 0, LABELS = 1, ENEMYPOV = 2 };
}

void printLine(int, std::string, std::string, std::string, std::string);
void printChar(int, char);
void invertColours();
void revertColours();
void stall();
void clearScreen();

class Player {
  public:
    Player();
    Player(std::string);

    ~Player();

    std::string getPlayerName();
    void setPlayerName(std::string);

    void initBoard();
    bool isBoardSet();
    void drawBoard(int = drawType::NORMAL);

    bool checkLost();
    bool checkSunken(Coordinates);
    bool isHit(Coordinates);
    bool tryHitting(Coordinates);
    Coordinates selectCoordinatesForHitting(Player *,
                                            Coordinates = Coordinates());

  private:
    void initPlayer();
    void addShip();
    void selectCoordinatesForShip(int, bool = true);
    bool tryPlacingShip(int, int, int, char, bool = true);
    void editShip();
    void tryChaningCoordinatesForShip(int);
    void hideShip(int);
    void showShip(int);
    void resetBoard(bool = false);
    bool commitBoard();

    // 0 -> water, 1-> ship, 2 -> hit water, 3 -> sunken ship
    unsigned short board[BOARD_SIZE][BOARD_SIZE] = {};
    bool boardSet = false;
    std::vector<std::vector<Ship>> remainingShips = {
        std::vector<Ship>(4, Ship(2)), std::vector<Ship>(3, Ship(3)),
        std::vector<Ship>(2, Ship(4)), std::vector<Ship>(1, Ship(6))};
    std::vector<Ship *> ships;
    std::string playerName;
};
#endif // PLAYER_H_
