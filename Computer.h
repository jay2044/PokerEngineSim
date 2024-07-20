#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include <vector>
#include <string>

class Computer : public Player {
public:
    // Default constructor
    Computer();

    // Constructor with personality traits
    Computer(float aggressiveness, float riskAversion, float predictability);

    // Constructor with name and personality traits
    Computer(const std::string& name, float aggressiveness, float riskAversion, float predictability);

    // Constructor with name
    Computer(const std::string& name);

    // Method to make a decision
    std::string& makeDecision(const std::vector<Card>& communityCards);

    // Getters for personality traits
    float getAggressiveness() const;
    float getRiskAversion() const;
    float getPredictability() const;

    // Setters for personality traits
    void setAggressiveness(float aggressiveness);
    void setRiskAversion(float riskAversion);
    void setPredictability(float predictability);

private:
    float aggressiveness;
    float riskAversion;
    float predictability;
};

#endif // COMPUTER_H
