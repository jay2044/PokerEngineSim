//
// Created by jayaa on 12/12/2023.
//

#ifndef POKER_DECK_H
#define POKER_DECK_H

#include <vector>
#include "Card.h"
#include <cstdint>

class Deck {
public:
    Deck();
    void shuffle();
    Card dealCard();

private:
    std::vector<Card> cards;
    int currentCardIndex;
};

#endif //POKER_DECK_H

