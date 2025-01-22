#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.h"

class Player {
public:
    Player();
    explicit Player(std::string  name);
    virtual ~Player() = default;

    virtual bool isComputer() const { return false; }

    void addChips(int amount);
    bool betChips(int amount);
    void setHoleCards(const Card& card1, const Card& card2);
    void clearCards();
    std::string showHoleCards() const;
    const std::vector<Card>& getHoleCards() const;
    int getChips() const;
    int getCurrentBet() const { return currentBet; }
    bool isStillPlaying() const { return isPlaying; }
    void setPlaying(bool val) {isPlaying = val;}
    const std::string& getName() const { return name; }

    void fold() { isPlaying = false; }
    bool check() const { return currentBet == 0; }
    bool call(int amount);
    bool raise(int amount);
    void reset();
    void resetCurrentBet();

protected:
    std::string name;
    std::vector<Card> holeCards;
    int chips = 0;
    int currentBet = 0;
    bool isPlaying = true;
};

#endif // PLAYER_H
