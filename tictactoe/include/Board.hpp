#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <array>

enum class Cell {
    EMPTY,
    X,
    O
};

class Board {
public:
    // Constructor
    Board();

    // Reset the board to empty state
    void reset();

    // Make a move at the specified position (0-8)
    bool makeMove(int position, Cell player);

    // Undo the last move
    void undoMove(int position);

    // Check if a position is valid and empty
    bool isValidMove(int position) const;

    // Get all available moves
    std::vector<int> getAvailableMoves() const;

    // Check if the game is over (win or draw)
    bool isGameOver() const;

    // Check if there's a winner
    bool hasWinner() const;

    // Get the winner (returns EMPTY if no winner)
    Cell getWinner() const;

    // Check if the board is full (draw)
    bool isFull() const;

    // Get cell value at position (0-8)
    Cell getCell(int position) const;

    // Get cell value at row and column (0-2, 0-2)
    Cell getCell(int row, int col) const;

    // Convert position to row and column
    static void positionToRowCol(int position, int& row, int& col);

    // Convert row and column to position
    static int rowColToPosition(int row, int col);

private:
    std::array<Cell, 9> cells;

    // Check for three in a row
    bool checkLine(int pos1, int pos2, int pos3) const;

    // Check all winning conditions
    Cell checkWinner() const;
};

#endif // BOARD_HPP
