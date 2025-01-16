#include <iostream>
#include <utility>
#include <sstream>
#include "include/Game.h"

int main() {
    // Get player names
    std::string playerOneName{}, playerTwoName{};
    std::cout << "Enter player one name: ";
    std::cin >> playerOneName;
    std::cout << "Enter player two name: ";
    std::cin >> playerTwoName;
    std::cout << std::endl;

    // Create game
    Game game(playerOneName, playerTwoName);

    // Initiate game Loop
    while (game.getState() == GameEnums::INCOMPLETE) {
        Player nextPlayer = game.getNextPlayer(); // get next player
        std::cout << std::endl << "Board Spots:\n" << game.getBoardSpots() << std::endl; // print board options
        std::cout << nextPlayer.getName() << " (" << nextPlayer.getSymbol() << "), it's your turn!" << std::endl; // print next player
        int spot{};
        while (true) {
            try {
                std::cout << "Enter spot number: ";
                std::cin >> spot;
                game.move(spot); // make move
                break;
            } catch (std::invalid_argument& e) {
                std::cout << e.what() << ", please try again." << std::endl;
            }
        }
    }

    // Game over
    std::cout << "Game over.. ";
    if (game.getState() == GameEnums::WON) {
        Player p = game.getNextPlayer();
        std::cout << p.getName() << " (" << p.getSymbol() << ") has won!" << std::endl;
    } else
        std::cout << "It's a tie!";

    return 0;
}
