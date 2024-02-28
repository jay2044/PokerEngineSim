#include "Player.h"

Player::Player() : chips(5000) {}

void Player::addChips(int amount) {
    chips += amount;
}

bool Player::betChips(int amount) {
    if (amount > chips) {
        return false;
    }
    chips -= amount;
    return true;
}

void Player::setHoleCards(const Card& card1, const Card& card2) {
    holeCards.clear();
    holeCards.push_back(card1);
    holeCards.push_back(card2);
}

std::string Player::showHoleCards() const {
    if (holeCards.size() != 2) {
        return "No hole cards set";
    }
    return holeCards[0].toString() + ", " + holeCards[1].toString();
}

void Player::clearCards() {
    holeCards.clear();
}

int Player::getChips() {
    return chips;
}

std::vector<Card> Player::getHoleCards() {
    return holeCards;
}
