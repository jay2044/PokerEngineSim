//
// Created by jayaa on 12/12/2023.
//

#include "Card.h"

Card::Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}

Suit Card::getSuit() const {
    return suit;
}

Rank Card::getRank() const {
    return rank;
}

std::string Card::toString() const {
    std::string suitNames[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::string rankNames[] = {"", "", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};

    return rankNames[static_cast<int>(rank)] + " of " + suitNames[static_cast<int>(suit)];
}