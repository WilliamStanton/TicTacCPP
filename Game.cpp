//
// Created by Billy on 1/15/2025.
//

#include "include/Game.h"

#include <stdexcept>

GameEnums::GameState state; // game state

// Initialize Players, board, and game state
Game::Game(std::string playerOneName, std::string playerTwoName) : p1(std::move(playerOneName), true, 'X'), p2(std::move(playerTwoName), false, 'O') {
    this->board = Board();
    this->state = GameEnums::INCOMPLETE;
}

/**
 * Sets the next player up as long as game isn't over
 */
void Game::setNextPlayer() {
    if (getNextPlayer().getName() == p1.getName() && state == GameEnums::INCOMPLETE) {
        p1.setTurn(false);
        p2.setTurn(true);
    } else if (state == GameEnums::INCOMPLETE){
        p1.setTurn(true);
        p2.setTurn(false);
    } else {
        throw std::logic_error("game has already ended, cannot set next player");
    }
}

/**
 * Makes the next move for the game given that spot is valid
 * @param spot board spot
 */
void Game::move(const int spot) {
    if (spot < 1 || spot > 9)
        throw std::invalid_argument("Invalid board spot");
    BoardSpot* s = board.getBoardSpot(spot); // get spot pointer
    if (s->isTaken())
        throw std::invalid_argument("Board spot is already taken");
    s->setPlayer(getNextPlayer()); // set spot to player
    state = board.checkState(); // update game state

    // update next player if game is still continuous
    if (state == GameEnums::INCOMPLETE)
        setNextPlayer();
}

Player Game::getNextPlayer() {
    return p1.isTurn() ? p1 : p2;
}

Player Game::getP1() const {
    return p1;
}

Player Game::getP2() const {
    return p2;
}

/**
 * Gets all board spots as a string
 * @return all board spots
 */
std::string Game::getBoardSpots() {
    return board.toString();
}

GameEnums::GameState Game::getState() const {
    return state;
}