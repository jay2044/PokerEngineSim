//
// Created by jayaa on 1/1/2024.
//

#ifndef POKER_COMPUTER_H
#define POKER_COMPUTER_H

#include "Player.h"
#include "Card.h"
#include <vector>
#include <string>

class Computer : public Player {
public:
    // Constructors
    Computer();
    explicit Computer(float aggressiveness, float riskAversion, float predictability);
    bool isComputer() const override { return true; }

    // Getters and Setters for personality traits
    float getAggressiveness() const;
    void setAggressiveness(float aggressiveness);

    float getRiskAversion() const;
    void setRiskAversion(float riskAversion);

    float getPredictability() const;
    void setPredictability(float predictability);

    std::string& makeDecision(const std::vector<Card>& communityCards);

private:
    // Personality traits
    float aggressiveness; // How likely to make bold moves
    float riskAversion;   // Preference for safe plays over potential high-reward plays
    float predictability; // Consistency in playing style
};


#endif //POKER_COMPUTER_H
