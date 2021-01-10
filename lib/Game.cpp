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
 * Game class implementation
 *
 */
#include "Game.hpp"
#include <fstream>
#include <iostream>

Game::Game(int playerCount, std::string fileName) {
    std::string path, playerName;
    bool hasToInit;
    for (int i = 0; i < playerCount; ++i) {
        path = "res/" + fileName + std::to_string(i + 1) + ".txt";
        // res/ + presetBoard + 1 + .txt = res/presetBoard1.txt
        hasToInit = false;

        clearScreen();
        if (fileExists(path)) {
            players.push_back(new Player(path));
            if (!players.back()->isBoardSet()) {
                std::cout << "Player " << (i + 1)
                          << " has an invalid preset board file. You'll now "
                             "enter the manual board builder."
                          << std::endl;
                hasToInit = true;
                // players.back()->initBoard();
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
            hasToInit = true;
            // players.back()->initBoard();
        }
        std::cout << "Enter Player " << (i + 1) << " name: ";
        std::cin >> playerName;
        // Set the selected player name
        players.back()->setPlayerName(playerName);
        // Stall to let user see the status messages
        // stall();
        if (hasToInit) {
            players.back()->initBoard();
        }
    }

    // All players are now fully init-ed
    start();
}

Game::~Game() {
    for (size_t i = 0, size = players.size(); i < size; ++i) {
        delete players[i];
    }
}

bool Game::chooseAction(Player *currentPlayer, Player *enemy) {
    char option;
    bool wasInvalid = false;
    std::string message;
    do {
        clearScreen();
        std::cout << currentPlayer->getPlayerName()
                  << ", please choose an action:" << std::endl
                  << std::endl
                  << "1. Attack " << enemy->getPlayerName() << std::endl
                  << "2. View your own board" << std::endl
                  << std::endl;

        if (message.length() > 0) {
            if (wasInvalid) {
                std::cout << "Error!" << std::endl;
                wasInvalid = false;
            }
            std::cout << message << std::endl << std::endl;
            message = "";
        }

        std::cin >> option;
        std::cin.clear();

        if (option == '1') {
            return true;
        } else if (option == '2') {
            return false;
        } else {
            message = "Invalid option selected";
            wasInvalid = true;
        }

    } while (true);
}

void Game::start() {
    Player *currentPlayer, *enemy;

    for (int currentIndex = 0, size = players.size();;) {
        currentPlayer = players.at(currentIndex);
        enemy = players.at((currentIndex + 1) % size);

        if (chooseAction(currentPlayer, enemy)) {
            // Attack
            bool hit = false;
            Coordinates lastHit;
            do {
                lastHit =
                    enemy->selectCoordinatesForHitting(currentPlayer, lastHit);
                hit = enemy->tryHitting(lastHit);
                clearScreen();
                if (enemy->checkLost()) {
                    // Win
                    enemy->drawBoard();
                    std::cout << std::endl
                              << currentPlayer->getPlayerName()
                              << ", you won! You've sunk all of "
                              << enemy->getPlayerName()
                              << "'s ships! Press "
                                 "Enter to exit"
                              << std::endl;
                    stall();
                    return;
                }
                enemy->drawBoard(drawType::ENEMYPOV);
                if (hit) {
                    // Successful hit
                    std::cout << std::endl
                              << currentPlayer->getPlayerName() << ", you've "
                              << (currentPlayer->checkSunken(lastHit) ? "sunk"
                                                                      : "hit")
                              << " a ship! It's you turn again. Press "
                                 "Enter to continue"
                              << std::endl;
                    stall();
                } else {
                    // Water hit
                    clearScreen();
                    enemy->drawBoard(drawType::ENEMYPOV);
                    std::cout << std::endl
                              << "Oh noooo... a miss. "
                              << currentPlayer->getPlayerName()
                              << ", you didn't hit a ship. It's now your "
                                 "opponent's turn. Press Enter to continue"
                              << std::endl;
                    stall();
                    currentIndex = (currentIndex + 1) % size;
                    continue;
                }
            } while (hit);
        } else {
            // View board
            clearScreen();
            currentPlayer->drawBoard();
            std::cout << std::endl << "Press Enter to return" << std::endl;
            stall();
        }
    }
}

bool fileExists(std::string fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}
