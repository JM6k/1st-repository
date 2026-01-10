#ifndef AI_HPP
#define AI_HPP

#include "Board.hpp"

class AI {
public:
    // Get the best move for the AI player using Minimax algorithm
    static int getBestMove(Board& board, Cell aiPlayer);

private:
    // Minimax algorithm with alpha-beta pruning
    static int minimax(Board& board, Cell player, Cell aiPlayer, bool isMaximizing, int alpha, int beta, int depth);

    // Evaluate the board state
    static int evaluate(const Board& board, Cell aiPlayer, int depth);

    // Get the opponent of a player
    static Cell getOpponent(Cell player);
};

#endif // AI_HPP
