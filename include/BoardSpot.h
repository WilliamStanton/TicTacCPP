//
// Created by Billy on 1/15/2025.
//

#pragma once
#include "player.h"

/**
 * Board Spot Class
 */
class BoardSpot {
private:
    int id; // spot id
    Player player; // spot player

public:
    // Constructor
    explicit BoardSpot(int id);

    // Getters
    int getId() const;
    Player getPlayer() const;
    bool isTaken() const;

    // Setters
    void setPlayer(Player player);
    void setTaken(const Player &player);
};
