#include <iostream>
#include <utility>
#include <vector>
#include <sstream>

enum GameState {
    INCOMPLETE,
    TIED,
    WON
};

/**
 * Player Class
 */
class Player {
    std::string name; // player name
    char symbol; // player symbol ('X', 'O')
    bool turn; // player turn

public:
    Player(std::string name, bool init, char symbol) {
        this->name = name;
        this->turn = init;
        this->symbol = symbol;
    }

    std::string_view getName() {
        return this->name;
    }

    char getSymbol() {
        return this->symbol;
    }

    bool isTurn() {
        return this->turn;
    }

    void setTurn(bool turn) {
        this->turn = turn;
    }
};

/**
 * Board Spot Class
 */
class BoardSpot {
    int id; // spot id
    Player player; // spot player

public:
    BoardSpot(int id, char symbol): player(std::string(""), false, symbol) {
        this -> id = id;
    }

    int getId() const {
        return this->id;
    }

    Player getPlayer() const {
        return this->player;
    }

    void setPlayer(Player player) {
        this->player = std::move(player);
    }

    bool isTaken() {
        return player.getName().length() != 0;
    }

    void setTaken(Player player) {
        setPlayer(player);
    }
};

/**
 * Game Board
 */
class Board {
    // board spot array
    BoardSpot boardSpots[3][3] = {
        {BoardSpot(1, '1'), BoardSpot(2, '2'), BoardSpot(3, '3')},
        {BoardSpot(4, '4'), BoardSpot(5, '5'), BoardSpot(6, '6')},
        {BoardSpot(7, '7'), BoardSpot(8, '8'), BoardSpot(9, '9')}
    };

public:
    /**
     * Returns pointer to board spot
     * @param id board spot id
     * @return board spot pointer
     */
    BoardSpot* getBoardSpot(const int id) {
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
    GameState checkState() {
        // horizontal
        if (boardSpots[0][0].getPlayer().getSymbol() == boardSpots[0][1].getPlayer().getSymbol() && boardSpots[0][0].getPlayer().getSymbol() == boardSpots[0][2].getPlayer().getSymbol() ||
            boardSpots[1][0].getPlayer().getSymbol() == boardSpots[1][1].getPlayer().getSymbol() && boardSpots[1][0].getPlayer().getSymbol() == boardSpots[1][2].getPlayer().getSymbol() ||
            boardSpots[2][0].getPlayer().getSymbol() == boardSpots[2][1].getPlayer().getSymbol() && boardSpots[2][0].getPlayer().getSymbol() == boardSpots[2][2].getPlayer().getSymbol()) {
            return WON;
        }

        // vertical
        else if (boardSpots[0][0].getPlayer().getSymbol() == boardSpots[1][0].getPlayer().getSymbol() && boardSpots[0][0].getPlayer().getSymbol() == boardSpots[0][2].getPlayer().getSymbol() ||
            boardSpots[1][0].getPlayer().getSymbol() == boardSpots[1][1].getPlayer().getSymbol() && boardSpots[1][0].getPlayer().getSymbol() == boardSpots[1][2].getPlayer().getSymbol() ||
            boardSpots[2][0].getPlayer().getSymbol() == boardSpots[2][1].getPlayer().getSymbol() && boardSpots[2][0].getPlayer().getSymbol() == boardSpots[2][2].getPlayer().getSymbol()) {
            return WON;
        }

        // diagonals
        else if (boardSpots[0][0].getPlayer().getSymbol() == boardSpots[1][1].getPlayer().getSymbol() && boardSpots[0][0].getPlayer().getSymbol() == boardSpots[2][2].getPlayer().getSymbol() ||
            boardSpots[2][0].getPlayer().getSymbol() == boardSpots[1][1].getPlayer().getSymbol() && boardSpots[2][0].getPlayer().getSymbol() == boardSpots[0][2].getPlayer().getSymbol()) {
            return WON;
        }

        // check for incomplete game
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (boardSpots[i][j].getPlayer().getName().length() == 0) {
                    return INCOMPLETE;
                }
            }
        }

        // else, game tied
        return TIED;
    }

    // Prints entire board to stream
    std::string toString() {
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
};

/**
 * Game Class
 */
class Game {
    GameState state = INCOMPLETE; // game state
    Board board; // game board
    Player p1; // player 1
    Player p2; // player 2

    /**
     * Sets the next player up as long as game isn't over
     */
    void setNextPlayer() {
        if (getNextPlayer().getName() == p1.getName() && state == INCOMPLETE) {
            p1.setTurn(false);
            p2.setTurn(true);
        } else if (state == INCOMPLETE){
            p1.setTurn(true);
            p2.setTurn(false);
        } else {
            throw std::logic_error("game has already ended, cannot set next player");
        }
    }

public:
    // Initialize Players
    Game(std::string playerOneName, std::string playerTwoName) : p1(std::move(playerOneName), true, 'X'), p2(std::move(playerTwoName), false, 'O') {
        board = Board();
    }

    /**
     * Makes the next move for the game given that spot is valid
     * @param spot board spot
     */
    void move(const int spot) {
        if (spot < 1 || spot > 9)
            throw std::invalid_argument("Invalid board spot");
        BoardSpot* s = board.getBoardSpot(spot); // get spot pointer
        if (s->isTaken())
            throw std::invalid_argument("Board spot is already taken");
        s->setPlayer(getNextPlayer()); // set spot to player
        state = board.checkState(); // update game state

        // update next player if game is still continous
        if (state == INCOMPLETE)
            setNextPlayer();
    }

    Player getNextPlayer() {
        return p1.isTurn() ? p1 : p2;
    }

    Player getP1() const {
        return p1;
    }

    Player getP2() const {
        return p2;
    }

    /**
     * Gets all board spots as a string
     * @return all board spots
     */
    std::string getBoardSpots() {
        return board.toString();
    }

    GameState getState() const {
        return state;
    }
};

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
    while (game.getState() == INCOMPLETE) {
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
    if (game.getState() == WON) {
        Player p = game.getNextPlayer();
        std::cout << p.getName() << " (" << p.getSymbol() << ") has won!" << std::endl;
    } else
        std::cout << "It's a tie!";

    return 0;
}
