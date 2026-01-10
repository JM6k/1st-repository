#include "Board.hpp"

Board::Board() {
    reset();
}

void Board::reset() {
    cells.fill(Cell::EMPTY);
}

bool Board::makeMove(int position, Cell player) {
    if (!isValidMove(position) || player == Cell::EMPTY) {
        return false;
    }
    cells[position] = player;
    return true;
}

void Board::undoMove(int position) {
    if (position >= 0 && position < 9) {
        cells[position] = Cell::EMPTY;
    }
}

bool Board::isValidMove(int position) const {
    return position >= 0 && position < 9 && cells[position] == Cell::EMPTY;
}

std::vector<int> Board::getAvailableMoves() const {
    std::vector<int> moves;
    for (int i = 0; i < 9; ++i) {
        if (cells[i] == Cell::EMPTY) {
            moves.push_back(i);
        }
    }
    return moves;
}

bool Board::isGameOver() const {
    return hasWinner() || isFull();
}

bool Board::hasWinner() const {
    return checkWinner() != Cell::EMPTY;
}

Cell Board::getWinner() const {
    return checkWinner();
}

bool Board::isFull() const {
    for (const auto& cell : cells) {
        if (cell == Cell::EMPTY) {
            return false;
        }
    }
    return true;
}

Cell Board::getCell(int position) const {
    if (position >= 0 && position < 9) {
        return cells[position];
    }
    return Cell::EMPTY;
}

Cell Board::getCell(int row, int col) const {
    return getCell(rowColToPosition(row, col));
}

void Board::positionToRowCol(int position, int& row, int& col) {
    row = position / 3;
    col = position % 3;
}

int Board::rowColToPosition(int row, int col) {
    return row * 3 + col;
}

bool Board::checkLine(int pos1, int pos2, int pos3) const {
    return cells[pos1] != Cell::EMPTY &&
           cells[pos1] == cells[pos2] &&
           cells[pos2] == cells[pos3];
}

Cell Board::checkWinner() const {
    // Check rows
    for (int row = 0; row < 3; ++row) {
        if (checkLine(row * 3, row * 3 + 1, row * 3 + 2)) {
            return cells[row * 3];
        }
    }

    // Check columns
    for (int col = 0; col < 3; ++col) {
        if (checkLine(col, col + 3, col + 6)) {
            return cells[col];
        }
    }

    // Check diagonals
    if (checkLine(0, 4, 8)) {
        return cells[0];
    }
    if (checkLine(2, 4, 6)) {
        return cells[2];
    }

    return Cell::EMPTY;
}
