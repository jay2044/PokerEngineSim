//
// Created by jayaa on 12/12/2023.
//

#include "Deck.h"
#include <algorithm> // For std::shuffle
#include <random>    // For std::default_random_engine
#include <chrono>    // For std::chrono::system_clock
#include <stdexcept>
#include <cstdint>


Deck::Deck() {
    // Initialize the deck with 52 cards

    for (int suit = static_cast<int>(Suit::Hearts); suit <= static_cast<int>(Suit::Spades); ++suit) {
        for (int rank = static_cast<int>(Rank::Two); rank <= static_cast<int>(Rank::Ace); ++rank) {
            cards.emplace_back(static_cast<Suit>(suit), static_cast<Rank>(rank));
        }
    }
    currentCardIndex = 0;
}

void Deck::shuffle() {
    // Use the current time as a seed for the random number generator
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
    currentCardIndex = 0;
}

Card Deck::dealCard() {
    if (cards.empty()) {
        throw std::runtime_error("No more cards in the deck.");
    }

    Card dealtCard = cards.front(); // Get the first card
    cards.erase(cards.begin());     // Remove the first card from the deck

    return dealtCard;               // Return the dealt card
}