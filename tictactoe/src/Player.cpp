#include "Player.hpp"

Player::Player(const std::string& name, Cell symbol, bool isAI)
    : name(name), symbol(symbol), isAI(isAI), wins(0), losses(0), draws(0) {
}

void Player::resetScore() {
    wins = 0;
    losses = 0;
    draws = 0;
}
