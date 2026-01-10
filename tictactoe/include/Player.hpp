#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Board.hpp"

class Player {
public:
    // Constructor
    Player(const std::string& name, Cell symbol, bool isAI);

    // Getters
    std::string getName() const { return name; }
    Cell getSymbol() const { return symbol; }
    bool isAIPlayer() const { return isAI; }
    int getWins() const { return wins; }
    int getLosses() const { return losses; }
    int getDraws() const { return draws; }

    // Score tracking
    void addWin() { wins++; }
    void addLoss() { losses++; }
    void addDraw() { draws++; }
    void resetScore();

private:
    std::string name;
    Cell symbol;
    bool isAI;
    int wins;
    int losses;
    int draws;
};

#endif // PLAYER_HPP
