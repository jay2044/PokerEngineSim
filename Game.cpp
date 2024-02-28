//
// Created by jayaa on 1/1/2024.
//

#include "Game.h"
#include "Player.h"
#include "Deck.h"
#include "Computer.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <map>


std::vector<std::shared_ptr<Player>> Game::players;
std::vector<std::shared_ptr<Player>> Game::queue;
int pot = 0;
int round = 0;
int dealerIndex = 0;

Game::Game() {
    players.push_back(std::make_shared<Player>());
    players.push_back(std::make_shared<Player>());
//    players.push_back(std::make_shared<Player>());
};

void Game::play() {
    std::cout << "Starting the Poker Game!" << std::endl;

    while(!gameOver) {
        resetForNewRound();
        if (checkEndGameConditions()){
            gameOver = true;
            break;
        }
        if (queue.size() >= 3) {
            bet(players[1], smallBlind);
            bet(players[2], bigBlind);
        } else {
            bet(players[1], bigBlind);
        }
        round += 1;
        std::cout<<"Round "<<round<<std::endl;

        for (auto& player : queue) {
            player->setHoleCards(deck.dealCard(), deck.dealCard());
            if (!player->isComputer()){
                std::cout << "Player"<<getIndex(player)<<" cards: " << player->showHoleCards() << std::endl;
            }
        }
        // Pre-flop betting
        startBetting();
        if (checkEndGameConditions()){determineWinner(communityCards); continue;}

        // Flop
        for (int i = 0; i < 3; i++) {
            communityCards.push_back(deck.dealCard());
        }
        displayCommunityCards();

        // Post-flop betting
        startBetting();
        if (checkEndGameConditions()){determineWinner(communityCards); continue;}

        // Turn
        communityCards.push_back(deck.dealCard());
        displayCommunityCards();

        // Post-turn betting
        startBetting();
        if (checkEndGameConditions()){determineWinner(communityCards); continue;}

        // River
        communityCards.push_back(deck.dealCard());
        displayCommunityCards();

        // Post-river betting
        startBetting();
        if (checkEndGameConditions()){determineWinner(communityCards); continue;}

        // Declare winner and add chips
        determineWinner(communityCards);

        std::cout << "Game round over!" << std::endl;
    }

}

void Game::startBetting() {
    highestBet = 0;
    previousHighestBet = 0;
    continueBetting = true;
    highestBettor = nullptr;

    while (continueBetting) {
        continueBetting = false;
        std::cout<<"continueBetting set false"<<std::endl;
        for (auto& player : queue) {
            if (player == highestBettor) {
                std::cout<<"highestBettor skipped"<<std::endl;
                continue;
            }
            Decision decision = getDecision(player);
            handleDecision(decision, player);
            std::cout<<"previousHighestBet:"<<previousHighestBet<<std::endl;
            std::cout<<"highestBet:"<<highestBet<<std::endl;

            if (decision.action == ActionType::Bet && decision.amount > previousHighestBet) {
                std::cout<<"player"<<getIndex(player)<<" placed higher bet"<<std::endl;
                highestBettor = player;
                continueBetting = true;
                break;
            } else {
                std::cout<<"player didnt place higher bet"<<std::endl;
            }
        }
        if(!continueBetting) {
            std::cout<<"ending bet round"<<std::endl;
        }
    }
    for (auto& player : queue) {
        bet(player, highestBet);
    }
}




void Game::displayCommunityCards() {
    std::cout<<std::endl << "Community Cards: " << std::endl;
    for (auto& card : communityCards) {
        std::cout << card.toString() << std::endl;
    }
    std::cout<<std::endl;
}

Decision Game::getDecision(const std::shared_ptr<Player>& player) {
    if (player->isComputer()) {
        std::string& decisionValue = dynamic_cast<Computer*>(player.get())->makeDecision(communityCards);
        return determineInput(decisionValue);
    } else {
        return getUserDecision();
    }
}

void Game::handleDecision(const Decision& decision, const std::shared_ptr<Player>& player) {
    switch(decision.action) {
        case ActionType::Fold:
            // Implement folding logic
            player->isPlaying = false;
            std::cout << "player"<<getIndex(player)<<" folds" << std::endl;
            if (checkEndGameConditions()){determineWinner(communityCards);}
            break;
        case ActionType::Check:
            if (highestBet > 0) {
                std::cout << "player"<<getIndex(player)<<" calls" << std::endl;
            } else {
                std::cout << "player"<<getIndex(player)<<" checks" << std::endl;
            }
            break;
        case ActionType::Bet:
//            bet(player, decision.amount);
            pot += decision.amount;
            if (decision.amount >= highestBet || player->getChips() == decision.amount) {
                previousHighestBet = highestBet;
                highestBet = decision.amount;
            }
            break;
        case ActionType::Invalid:
        default:
            std::cout << "bruh wat is u saying??" << std::endl;
            break;
    }
}

Decision Game::getUserDecision() {
    std::string input;
    Decision decision{};
    do {
        std::cout << "Your action (fold, check/call, bet): ";
        std::cin >> input;
        decision = determineInput(input);
        // Repeat until valid input is given
    } while(decision.action == ActionType::Invalid);
    return decision;
}


Decision Game::determineInput(const std::string& input) {
    if (input == "fold") {
        return {ActionType::Fold, 0};
    } else if (input == "check" || input == "call") {
        return {ActionType::Check, highestBet};
    } else if (input == "bet") {
        int betAmount;
        std::cout << "Enter bet amount: ";
        std::cin >> betAmount;
        if (betAmount >= highestBet){ return {ActionType::Bet, static_cast<int>(betAmount)}; }
    }
    return {ActionType::Invalid, 0}; // Invalid input
}

void Game::resetForNewRound() {
    deck.shuffle();
    communityCards.clear();
    queue.clear();

    // Update dealerIndex for the new round
    dealerIndex = (dealerIndex + 1) % players.size();

    // Start queue from the player next to the dealer
    for (size_t i = 0; i < players.size(); ++i) {
        size_t playerIndex = (dealerIndex + i) % players.size();
        if (players[playerIndex]->getChips() > 0) {
            players[playerIndex]->clearCards();
            players[playerIndex]->isPlaying = true;
            queue.push_back(players[playerIndex]);
        }
    }

    pot = 0;
}




bool Game::checkEndGameConditions() {
    for (auto it = queue.begin(); it != queue.end(); ) {
        if (!(*it)->isPlaying) {
            it = queue.erase(it);
        } else {
            ++it;
        }
    }
    if (queue.size() > 1) { return false; }
    return true;
}


void Game::determineWinner(const std::vector<Card>& communityCards) {
    // Check if there's only one player left (others have folded)
    if (queue.size() == 1) {
        std::cout << "Winner by default: Player"<< getIndex(queue[0]) << std::endl;
        queue.front()->addChips(pot);
        return;
    }

    // If more than one player is active, evaluate hands
    std::shared_ptr<Player> bestPlayer = nullptr;
    float rating;

    for (const auto& player : queue) {
        float playerRating = evaluateHand(player, communityCards);
        if (rating < playerRating) {
            bestPlayer = player;
            rating = playerRating;
        }
    }

    if (bestPlayer) {
        std::cout << "Winner is: Player"<< getIndex(bestPlayer) << std::endl;
        bestPlayer->addChips(pot);
        std::cout<<rating;
    } else {
        std::cout << "No winner determined." << std::endl;
    }
}


void Game::bet(const std::shared_ptr<Player>& player, int amount) {
    player->betChips(amount);
    player->updateCurrentBet(amount);
    std::cout << "player"<<getIndex(player)<<" bets: " << amount << std::endl << " player"<<getIndex(player)<<" chips: " << player->getChips() << std::endl;
}

int Game::getIndex(const std::shared_ptr<Player>& player) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] == player) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

float Game::evaluateHand(const std::shared_ptr<Player>& player, const std::vector<Card>& communityCards) {
    float rating = 0;

    std::vector<Card> hand = player->getHoleCards();
    hand.insert(hand.end(), communityCards.begin(), communityCards.end());

    std::map<Rank, int> frequency;
    for (const Card& card : hand) {
        frequency[card.getRank()]++;
    }

    for (const auto& pair : frequency) {
        int n = pair.second;
        rating += (n * (n - 1)) / 2.0f;
    }

//    for (const auto& card : hand) {
//        for (const auto& otherCard : hand) {
//            if (&otherCard != &card) {
//                if (isPairRank(card, otherCard)) {
//                    rating += 1;
//                }
//            }
//        }
//    }

    return rating;
}

bool Game::isPairRank(const Card &card1, const Card &card2) {
    if (card1.getRank() == card2.getRank()) {
        return true;
    }
    return false;
}

bool Game::isPairSuit(const Card &card1, const Card &card2) {
    if (card1.getSuit() == card2.getSuit()) {
        return true;
    }
    return false;
}
