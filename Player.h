#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include "Card.h"
#include <vector>
#include <string>

class Player {
public:
    Player();
    virtual ~Player() {}
    virtual bool isComputer() const { return false; }
    bool isPlaying = true;

    virtual void addChips(int amount);
    virtual bool betChips(int amount);
    virtual void setHoleCards(const Card& card1, const Card& card2);
    virtual void clearCards();
    std::string showHoleCards() const;
    virtual std::vector<Card> getHoleCards();
    int getChips();
    int getCurrentBet() const {
        return currentBet;
    };
    void updateCurrentBet(int bet) {
        currentBet = bet;
    };

protected:
    std::vector<Card> holeCards;
    int chips;
    int currentBet = 0;
};

#endif // POKER_PLAYER_H
