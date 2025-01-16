//
// Created by Billy on 1/15/2025.
//

#include "include/BoardSpot.h"

#include <utility>

BoardSpot::BoardSpot(int id, char symbol) : player(std::string(""), false, symbol) {
    this->id = id;
}

int BoardSpot::getId() const {
    return this->id;
}

Player BoardSpot::getPlayer() const {
    return this->player;
}

void BoardSpot::setPlayer(Player player) {
   this->player = std::move(player);
}

bool BoardSpot::isTaken() const {
    return player.getName().length() != 0;
}

void BoardSpot::setTaken(const Player &player) {
   setPlayer(player);
}