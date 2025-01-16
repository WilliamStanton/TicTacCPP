//
// Created by Billy on 1/15/2025.
//

#pragma once
#include "Board.h"
#include "GameEnums.h"

/**
 * Game class
 */
class Game {
    GameEnums::GameState state; // game state
    Board board; // game board
    Player p1; // player 1
    Player p2; // player 2

    // setter
    void setNextPlayer();

public:
    // Initialize Players
    Game(std::string playerOneName, std::string playerTwoName);

    // Setters
    void move(const int spot);

    // Getters
    Player getNextPlayer();
    Player getP1() const;
    Player getP2() const;
    std::string getBoardSpots();
    GameEnums::GameState getState() const;
};
