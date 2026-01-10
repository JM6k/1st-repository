#include "Game.hpp"

Game::Game() : currentPlayer(nullptr), state(GameState::MENU) {
}

void Game::startNewGame(Cell humanSymbol) {
    // Create players
    Cell aiSymbol = (humanSymbol == Cell::X) ? Cell::O : Cell::X;

    humanPlayer = std::make_unique<Player>("Human", humanSymbol, false);
    aiPlayer = std::make_unique<Player>("Computer", aiSymbol, true);

    // Reset board
    board.reset();

    // X always goes first
    if (humanSymbol == Cell::X) {
        currentPlayer = humanPlayer.get();
    } else {
        currentPlayer = aiPlayer.get();
    }

    state = GameState::PLAYING;
}

void Game::resetGame() {
    board.reset();

    // Keep the same players but reset to X going first
    if (humanPlayer && aiPlayer) {
        if (humanPlayer->getSymbol() == Cell::X) {
            currentPlayer = humanPlayer.get();
        } else {
            currentPlayer = aiPlayer.get();
        }
    }

    state = GameState::PLAYING;
}

bool Game::makeMove(int position) {
    if (state != GameState::PLAYING || !currentPlayer) {
        return false;
    }

    if (board.makeMove(position, currentPlayer->getSymbol())) {
        updateGameState();

        if (state == GameState::PLAYING) {
            switchPlayer();
        }

        return true;
    }

    return false;
}

void Game::processAITurn() {
    if (!isAITurn() || state != GameState::PLAYING) {
        return;
    }

    int bestMove = AI::getBestMove(board, aiPlayer->getSymbol());
    if (bestMove != -1) {
        makeMove(bestMove);
    }
}

bool Game::isAITurn() const {
    return currentPlayer && currentPlayer->isAIPlayer() && state == GameState::PLAYING;
}

const Player& Game::getCurrentPlayer() const {
    if (currentPlayer) {
        return *currentPlayer;
    }
    // Fallback (shouldn't happen in normal operation)
    return *humanPlayer;
}

Cell Game::getWinner() const {
    return board.getWinner();
}

bool Game::isGameOver() const {
    return state == GameState::GAME_OVER;
}

void Game::switchPlayer() {
    if (currentPlayer == humanPlayer.get()) {
        currentPlayer = aiPlayer.get();
    } else {
        currentPlayer = humanPlayer.get();
    }
}

void Game::updateGameState() {
    if (board.isGameOver()) {
        state = GameState::GAME_OVER;
        updateScores();
    }
}

void Game::updateScores() {
    Cell winner = board.getWinner();

    if (winner == Cell::EMPTY) {
        // Draw
        if (humanPlayer) humanPlayer->addDraw();
        if (aiPlayer) aiPlayer->addDraw();
    } else if (winner == humanPlayer->getSymbol()) {
        // Human wins
        humanPlayer->addWin();
        aiPlayer->addLoss();
    } else {
        // AI wins
        aiPlayer->addWin();
        humanPlayer->addLoss();
    }
}
