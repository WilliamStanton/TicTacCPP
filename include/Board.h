//
// Created by Billy on 1/15/2025.
//

#pragma once
#include "BoardSpot.h"
#include "GameEnums.h"

/**
 * Board Class
 */
class Board {
    // Board spot array
    BoardSpot boardSpots[3][3];

public:
    Board();
    // Getters
    BoardSpot* getBoardSpot(int id);
    GameEnums::GameState checkState() const;
    std::string toString();
};
