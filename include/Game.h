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

enum class ActionType {
    Fold, Check, Bet, Invalid, Call
};
struct Decision {
    ActionType action;
    int amount;
};

class Game {
public:
    Game(int numPlayers, int startingChips, int smallBlind, int bigBlind);

    void play();

private:
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Player>> activePlayers;
    Deck deck;
    std::vector<Card> communityCards;
    int pot = 0;
    int dealerIndex = 0;
    int smallBlind = 0;
    int bigBlind = 0;

    void dealHoleCards();

    void dealFlop();

    void dealTurn();

    void dealRiver();

    void conductBettingRound();

    void determineWinner();

    void resetForNewHand();

    bool isGameOver() const;


    int getPlayerIndex(const std::shared_ptr<Player> &player);

    float evaluateHand(const std::shared_ptr<Player> &player, const std::vector<Card> &communityCards);

    bool isPairRank(const Card &card1, const Card &card2);

    bool isPairSuit(const Card &card1, const Card &card2);

    Decision getDecision(const std::shared_ptr<Player> &player, int amountToCall);

    void handleDecision(const Decision &decision, const std::shared_ptr<Player> &player, int amountToCall);

    Decision getUserDecision(const std::shared_ptr<Player> &player, int amountToCall);

    Decision determineInput(const std::string &input, int amountToCall);

    static void clearTerminal() ;
    void displayGameState();
};


#endif //POKER_GAME_H
