//
// Created by Billy on 1/15/2025.
//

#pragma once
#include <string>

/**
 * Player Class
 */
class Player {
private:
    std::string name; // player name
    char symbol; // player symbol ('X', 'O')
    bool turn; // player turn

public:
    // Constructor
    Player(std::string name, bool init, char symbol);

    // Getters
    std::string getName() const;
    char getSymbol() const;
    bool isTurn() const;

    // Setters
    void setTurn(bool turn);
};
