//
// Created by jayaa on 12/12/2023.
//
#include <string>
#ifndef POKER_CARD_H
#define POKER_CARD_H


enum class Suit {
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

enum class Rank {
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

class Card {
public:
    Card(Suit suit, Rank rank);
    Suit getSuit() const;
    Rank getRank() const;
    std::string toString() const;

private:
    Suit suit;
    Rank rank;
};


#endif //POKER_CARD_H
