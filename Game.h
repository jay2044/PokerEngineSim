//
// Created by jayaa on 1/1/2024.
//

#ifndef POKER_GAME_H
#define POKER_GAME_H

#include "Player.h"
#include "Deck.h"
#include "Computer.h"
#include <vector>
#include <memory>

enum class ActionType { Fold, Check, Bet, Invalid };
struct Decision {
    ActionType action;
    int amount;
};

class Game {
public:
    Game();
    void play();
    bool gameOver = false;
    bool continueBetting = true;

private:
    Deck deck;
    static std::vector<std::shared_ptr<Player>> players;
    static std::vector<std::shared_ptr<Player>> queue;
    std::vector<Card> communityCards;
    int highestBet = 0;
    int previousHighestBet = 0;
    int smallBlind = 10;
    int bigBlind = 20;

    std::shared_ptr<Player> highestBettor;

    void displayCommunityCards();
    Decision getDecision(const std::shared_ptr<Player>& player);
    void handleDecision(const Decision &decision, const std::shared_ptr<Player> &player);
    Decision getUserDecision();
    Decision determineInput(const std::string& input);
    void resetForNewRound();
    static bool checkEndGameConditions();
    void determineWinner(const std::vector<Card>& communityCards);
    void startBetting();
    static void bet(const std::shared_ptr<Player>& player, int amount);
    static int getIndex(const std::shared_ptr<Player> &player);

    float evaluateHand(const std::shared_ptr<Player>& player, const std::vector<Card>& communityCards);
    bool isPairRank(const Card& card1, const Card& card2);
    bool isPairSuit(const Card& card1, const Card& card2);
};


#endif //POKER_GAME_H
