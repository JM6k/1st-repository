#include "AI.hpp"
#include <limits>
#include <algorithm>

int AI::getBestMove(Board& board, Cell aiPlayer) {
    int bestMove = -1;
    int bestScore = std::numeric_limits<int>::min();
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();

    std::vector<int> availableMoves = board.getAvailableMoves();

    for (int move : availableMoves) {
        // Make the move
        board.makeMove(move, aiPlayer);

        // Calculate score using minimax
        int score = minimax(board, getOpponent(aiPlayer), aiPlayer, false, alpha, beta, 0);

        // Undo the move
        board.undoMove(move);

        // Update best move if this is better
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }

        alpha = std::max(alpha, bestScore);
    }

    return bestMove;
}

int AI::minimax(Board& board, Cell player, Cell aiPlayer, bool isMaximizing, int alpha, int beta, int depth) {
    // Check if game is over
    if (board.isGameOver()) {
        return evaluate(board, aiPlayer, depth);
    }

    std::vector<int> availableMoves = board.getAvailableMoves();

    if (isMaximizing) {
        int maxScore = std::numeric_limits<int>::min();

        for (int move : availableMoves) {
            board.makeMove(move, player);
            int score = minimax(board, getOpponent(player), aiPlayer, false, alpha, beta, depth + 1);
            board.undoMove(move);

            maxScore = std::max(maxScore, score);
            alpha = std::max(alpha, score);

            // Alpha-beta pruning
            if (beta <= alpha) {
                break;
            }
        }

        return maxScore;
    } else {
        int minScore = std::numeric_limits<int>::max();

        for (int move : availableMoves) {
            board.makeMove(move, player);
            int score = minimax(board, getOpponent(player), aiPlayer, true, alpha, beta, depth + 1);
            board.undoMove(move);

            minScore = std::min(minScore, score);
            beta = std::min(beta, score);

            // Alpha-beta pruning
            if (beta <= alpha) {
                break;
            }
        }

        return minScore;
    }
}

int AI::evaluate(const Board& board, Cell aiPlayer, int depth) {
    Cell winner = board.getWinner();

    // AI wins
    if (winner == aiPlayer) {
        return 10 - depth;  // Prefer faster wins
    }

    // AI loses
    if (winner != Cell::EMPTY) {
        return depth - 10;  // Prefer slower losses
    }

    // Draw
    return 0;
}

Cell AI::getOpponent(Cell player) {
    if (player == Cell::X) {
        return Cell::O;
    } else if (player == Cell::O) {
        return Cell::X;
    }
    return Cell::EMPTY;
}
