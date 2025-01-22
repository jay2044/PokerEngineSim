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

    [[nodiscard]] Suit getSuit() const;

    [[nodiscard]] Rank getRank() const;

    [[nodiscard]] std::string toString() const;

    bool operator<(const Card &other) const {
        if (rank == other.rank) {
            return suit < other.suit;
        }
        return rank < other.rank;
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        return os << card.toString();
    }

private:
    Suit suit;
    Rank rank;
};


#endif //POKER_CARD_H
