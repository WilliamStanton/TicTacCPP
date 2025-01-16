//
// Created by Billy on 1/15/2025.
//

#include "include/Player.h"

#include <utility>

// Constructor definition
Player::Player(std::string name, bool init, char symbol) {
    this->name = std::move(name);
    this->turn = init;
    this->symbol = symbol;
}

std::string Player::getName() const {
    return this->name;
}

char Player::getSymbol() const {
    return this->symbol;
}

bool Player::isTurn() const {
    return this->turn;
}

void Player::setTurn(bool turn) {
    this->turn = turn;
}