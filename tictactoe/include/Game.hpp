#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Player.hpp"
#include "AI.hpp"
#include <memory>

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

class Game {
public:
    // Constructor
    Game();

    // Start a new game with player choosing X or O
    void startNewGame(Cell humanSymbol);

    // Reset the current game (keep scores)
    void resetGame();

    // Make a move at the specified position
    bool makeMove(int position);

    // Process AI turn
    void processAITurn();

    // Check if it's the AI's turn
    bool isAITurn() const;

    // Getters
    const Board& getBoard() const { return board; }
    Board& getBoard() { return board; }
    const Player& getHumanPlayer() const { return *humanPlayer; }
    const Player& getAIPlayer() const { return *aiPlayer; }
    const Player& getCurrentPlayer() const;
    GameState getState() const { return state; }
    Cell getWinner() const;
    bool isGameOver() const;

    // State management
    void setState(GameState newState) { state = newState; }
    void updateGameState();

private:
    Board board;
    std::unique_ptr<Player> humanPlayer;
    std::unique_ptr<Player> aiPlayer;
    Player* currentPlayer;
    GameState state;

    // Switch to the next player
    void switchPlayer();

    // Update scores based on game result
    void updateScores();
};

#endif // GAME_HPP
