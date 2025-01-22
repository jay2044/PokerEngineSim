#include "Player.h"

#include <utility>

Player::Player() : Player("NoName") {
}

Player::Player(std::string  name) : name(std::move(name)) {}

void Player::addChips(int amount) {
    chips += amount;
}

bool Player::betChips(int amount) {
    if (amount > chips) {
        return false;
    }
    chips -= amount;
    currentBet += amount;
    return true;
}

void Player::setHoleCards(const Card& card1, const Card& card2) {
    holeCards.clear();
    holeCards.push_back(card1);
    holeCards.push_back(card2);
}

void Player::clearCards() {
    holeCards.clear();
}

std::string Player::showHoleCards() const {
    // Assuming Card has a method toString() to represent the card as a string
    return  "|" + holeCards[0].toString() + "||" + holeCards[1].toString() + "|";
}

const std::vector<Card>& Player::getHoleCards() const {
    return holeCards;
}

int Player::getChips() const {
    return chips;
}

bool Player::call(int amount) {
    if (amount <= chips) {
        return betChips(amount);
    }
    return false;
}

bool Player::raise(int amount) {
    if (amount > chips) {
        return false;
    }
    return betChips(amount);
}

void Player::reset() {
    clearCards();
    currentBet = 0;
    isPlaying = true;
}

void Player::resetCurrentBet() {
    currentBet = 0;
}


