//
// Created by jayaa on 1/1/2024.
//

#include "Computer.h"

// Default constructor
Computer::Computer() : Player(),aggressiveness(0.5), riskAversion(0.5), predictability(0.5) {}

// Constructor with personality traits
Computer::Computer(float aggressiveness, float riskAversion, float predictability)
        : aggressiveness(aggressiveness), riskAversion(riskAversion), predictability(predictability) {}

std::string& Computer::makeDecision(const std::vector<Card>& communityCards) {

}

// Getters for personality traits
float Computer::getAggressiveness() const {
    return aggressiveness;
}

float Computer::getRiskAversion() const {
    return riskAversion;
}

float Computer::getPredictability() const {
    return predictability;
}

// Setters for personality traits
void Computer::setAggressiveness(float aggressiveness) {
    this->aggressiveness = aggressiveness;
}

void Computer::setRiskAversion(float riskAversion) {
    this->riskAversion = riskAversion;
}

void Computer::setPredictability(float predictability) {
    this->predictability = predictability;
}