//
// Created by Billy on 1/15/2025.
//

#include "include/Board.h"
#include "include/GameEnums.h"

#include <sstream>
#include <stdexcept>

// Initialize board spots
Board::Board() : boardSpots {
    {BoardSpot(1, '1'), BoardSpot(2, '2'), BoardSpot(3, '3')},
    {BoardSpot(4, '4'), BoardSpot(5, '5'), BoardSpot(6, '6')},
    {BoardSpot(7, '7'), BoardSpot(8, '8'), BoardSpot(9, '9')}
} {}

/**
 * Returns pointer to board spot
 * @param id board spot id
 * @return board spot pointer
 */
BoardSpot* Board::getBoardSpot(int id) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (boardSpots[i][j].getId() == id)
                return &boardSpots[i][j];
        }
    }
    // spot does not exist
    throw std::invalid_argument("Board Spot does not exist");
}

/**
 * Checks the state of the game
 * @return current state
 */
GameEnums::GameState Board::checkState() const {
    using GameEnums::GameState;
    // horizontal
    if (boardSpots[0][0].getPlayer().getSymbol() == boardSpots[0][1].getPlayer().getSymbol() && boardSpots[0][0].getPlayer().getSymbol() == boardSpots[0][2].getPlayer().getSymbol() ||
        boardSpots[1][0].getPlayer().getSymbol() == boardSpots[1][1].getPlayer().getSymbol() && boardSpots[1][0].getPlayer().getSymbol() == boardSpots[1][2].getPlayer().getSymbol() ||
        boardSpots[2][0].getPlayer().getSymbol() == boardSpots[2][1].getPlayer().getSymbol() && boardSpots[2][0].getPlayer().getSymbol() == boardSpots[2][2].getPlayer().getSymbol()) {

        return GameState::WON;
    }

    // vertical
    else if (boardSpots[0][0].getPlayer().getSymbol() == boardSpots[1][0].getPlayer().getSymbol() && boardSpots[0][0].getPlayer().getSymbol() == boardSpots[0][2].getPlayer().getSymbol() ||
        boardSpots[1][0].getPlayer().getSymbol() == boardSpots[1][1].getPlayer().getSymbol() && boardSpots[1][0].getPlayer().getSymbol() == boardSpots[1][2].getPlayer().getSymbol() ||
        boardSpots[2][0].getPlayer().getSymbol() == boardSpots[2][1].getPlayer().getSymbol() && boardSpots[2][0].getPlayer().getSymbol() == boardSpots[2][2].getPlayer().getSymbol()) {
        return GameState::WON;
    }

    // diagonals
    else if (boardSpots[0][0].getPlayer().getSymbol() == boardSpots[1][1].getPlayer().getSymbol() && boardSpots[0][0].getPlayer().getSymbol() == boardSpots[2][2].getPlayer().getSymbol() ||
        boardSpots[2][0].getPlayer().getSymbol() == boardSpots[1][1].getPlayer().getSymbol() && boardSpots[2][0].getPlayer().getSymbol() == boardSpots[0][2].getPlayer().getSymbol()) {
        return GameState::WON;
    }

    // check for incomplete game
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (boardSpots[i][j].getPlayer().getName().length() == 0) {
                return GameState::INCOMPLETE;
            }
        }
    }

    // else, game tied
    return GameState::TIED;
}


// Prints entire board to stream
std::string Board::toString() {
    std::ostringstream strOut;
    for (int i{0}; i < 3; i++) {
        for (int j{0}; j < 3; j++) {
            if (boardSpots[i][j].isTaken())
                strOut << boardSpots[i][j].getPlayer().getSymbol();
            else
                strOut << boardSpots[i][j].getId();
        }
        strOut << "\n";
    }
    return strOut.str();
}