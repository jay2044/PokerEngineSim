//
// Created by jayaa on 1/1/2024.
//

#include "Game.h"
#include <iostream>
#include <algorithm>
#include <map>


Game::Game(int numPlayers, int startingChips, int smallBlind, int bigBlind)
        : dealerIndex(0), pot(0), smallBlind(smallBlind), bigBlind(bigBlind) {
    for (int i = 0; i < numPlayers; i++) {
        players.push_back(std::make_shared<Player>());
        players[i]->addChips(startingChips);
    }
    activePlayers = players;
}

void Game::play() {
    std::cout << "Starting the Poker Game!" << std::endl;
    while (!isGameOver()) {
        resetForNewHand();
        dealHoleCards();
        displayGameState();
        conductBettingRound();
        displayGameState();
        if (activePlayers.size() > 1) {
            dealFlop();
            displayGameState();
            conductBettingRound();
            displayGameState();
        }
        if (activePlayers.size() > 1) {
            dealTurn();
            displayGameState();
            conductBettingRound();
            displayGameState();
        }
        if (activePlayers.size() > 1) {
            dealRiver();
            displayGameState();
            conductBettingRound();
            displayGameState();
        }
        determineWinner();
    }
}


void Game::conductBettingRound() {
    int highestBet = 0;
    size_t lastBettor = activePlayers.size();
    size_t currentPlayerIndex = 0;

    while (true) {
        auto &player = activePlayers[currentPlayerIndex];

        if (!player->isStillPlaying() || player->getChips() == 0) {
            currentPlayerIndex = (currentPlayerIndex + 1) % activePlayers.size();
            continue;
        }

        int amountToCall = highestBet - player->getCurrentBet();

        Decision decision = getUserDecision(player, amountToCall);
        handleDecision(decision, player, amountToCall);

        if (decision.action == ActionType::Bet || decision.action == ActionType::Call) {
            highestBet = std::max(highestBet, player->getCurrentBet());
            if (decision.action == ActionType::Bet) {
                lastBettor = currentPlayerIndex;
            }
        }

        currentPlayerIndex = (currentPlayerIndex + 1) % activePlayers.size();

        // Check if the round is complete
        if (currentPlayerIndex == lastBettor ||
            std::count_if(activePlayers.begin(), activePlayers.end(),
                          [](const auto &p) { return p->isStillPlaying(); }) <= 1) {
            break;
        }
    }

    // Collect bets into the pot
    for (auto &player : activePlayers) {
        pot += player->getCurrentBet();
        player->resetCurrentBet();
    }
}

Decision Game::getDecision(const std::shared_ptr<Player> &player, int amountToCall) {
    if (player->isComputer()) {
//        std::string computerDecision = dynamic_cast<Computer *>(player.get())->makeDecision(communityCards);
//        return determineInput(computerDecision, amountToCall);
        printf("cawaev5165\n");
    } else {
        return getUserDecision(player, amountToCall);
    }
}

Decision Game::getUserDecision(const std::shared_ptr<Player> &player, int amountToCall) {
    std::string input;
    Decision decision;
    do {
        std::cout << "Player " << getPlayerIndex(player) << ", your action (fold, check/call, bet): ";
        std::cin >> input;
        decision = determineInput(input, amountToCall);

        if (decision.action == ActionType::Bet) {
            if (decision.amount > player->getChips()) {
                std::cout << "Invalid bet amount. You only have " << player->getChips() << " chips." << std::endl;
                decision.action = ActionType::Invalid;
            }
        }

        if (decision.action == ActionType::Invalid) {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    } while (decision.action == ActionType::Invalid);

    return decision;
}

void Game::handleDecision(const Decision &decision, const std::shared_ptr<Player> &player, int amountToCall) {
    switch (decision.action) {
        case ActionType::Fold:
            player->setPlaying(false);
            std::cout << "Player " << getPlayerIndex(player) << " folds." << std::endl;
            break;
        case ActionType::Check:
            std::cout << "Player " << getPlayerIndex(player) << " checks." << std::endl;
            break;
        case ActionType::Call:
            std::cout << "Player " << getPlayerIndex(player) << " calls " << amountToCall << "." << std::endl;
            player->betChips(amountToCall);
            break;
        case ActionType::Bet:
            std::cout << "Player " << getPlayerIndex(player) << " bets " << decision.amount << "." << std::endl;
            player->betChips(decision.amount);
            break;
        default:
            std::cout << "Invalid action. Player " << getPlayerIndex(player) << " folds." << std::endl;
            player->setPlaying(false);
            break;
    }
}

Decision Game::determineInput(const std::string &input, int amountToCall) {
    if (input == "fold") {
        return {ActionType::Fold, 0};
    } else if (input == "check") {
        return {ActionType::Check, 0};
    } else if (input == "call") {
        return {ActionType::Call, amountToCall};
    } else if (input.substr(0, 3) == "bet") {
        int betAmount = 0;
        std::cout << "Enter bet amount: ";
        std::cin >> betAmount;
        if (betAmount >= amountToCall) {
            return {ActionType::Bet, betAmount};
        }
    }
    return {ActionType::Invalid, 0}; // Invalid input
}


void Game::determineWinner() {
    // Check if there's only one player left (others have folded)
    if (activePlayers.size() == 1) {
        std::cout << "Winner by default: Player" << getPlayerIndex(activePlayers[0]) << std::endl;
        activePlayers.front()->addChips(pot);
        return;
    }

    // If more than one player is active, evaluate hands
    std::shared_ptr<Player> bestPlayer = nullptr;
    float rating;

    for (const auto &player: activePlayers) {
        float playerRating = evaluateHand(player, communityCards);
        if (rating < playerRating) {
            bestPlayer = player;
            rating = playerRating;
        }
    }

    if (bestPlayer) {
        std::cout << "Winner is: Player" << getPlayerIndex(bestPlayer) << std::endl;
        bestPlayer->addChips(pot);
        std::cout << rating;
    } else {
        std::cout << "No winner determined." << std::endl;
    }
}

int Game::getPlayerIndex(const std::shared_ptr<Player> &player) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] == player) {
            return static_cast<int>(i);
        }
    }
    return -1;
}


float Game::evaluateHand(const std::shared_ptr<Player> &player, const std::vector<Card> &communityCards) {
    float rating = 0;

    std::vector<Card> hand = player->getHoleCards();
    hand.insert(hand.end(), communityCards.begin(), communityCards.end());

    std::map<Rank, int> frequency;
    for (const Card &card: hand) {
        frequency[card.getRank()]++;
    }

    for (const auto &pair: frequency) {
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


void Game::resetForNewHand() {
    deck.shuffle();
    communityCards.clear();
    activePlayers.clear();

    // Update dealerIndex for the new round
    dealerIndex = (dealerIndex + 1) % players.size();

    // Start activePlayers from the player next to the dealer
    for (size_t i = 0; i < players.size(); ++i) {
        size_t playerIndex = (dealerIndex + i) % players.size();
        if (players[playerIndex]->getChips() > 0) {
            players[playerIndex]->clearCards();
            players[playerIndex]->setPlaying(true);
            activePlayers.push_back(players[playerIndex]);
        }
    }

    pot = 0;
}

void Game::dealHoleCards() {
    for (auto &player: activePlayers) {
        player->setHoleCards(deck.dealCard(), deck.dealCard());
//        if (!player->isComputer()) {
//            std::cout << "Player" << getPlayerIndex(player) << " cards: " << player->showHoleCards() << std::endl;
//        }
    }
}

void Game::dealFlop() {
    for (int i = 0; i < 3; i++) {
        communityCards.push_back(deck.dealCard());
    }
}

void Game::dealTurn() {
    communityCards.push_back(deck.dealCard());
}

void Game::dealRiver() {
    communityCards.push_back(deck.dealCard());
}


bool Game::isGameOver() const {
    // Count the number of players with chips
    int playersWithChips = 0;
    for (const auto &player: players) {
        if (player->getChips() > 0) {
            playersWithChips++;
        }
    }

    // If only one player has chips, the game is over
    if (playersWithChips <= 1) {
        return true;
    }

    // You can add additional game-ending conditions here
    // For example, you might want to end the game after a certain number of rounds
    // if (gameRound >= MAX_ROUNDS) {
    //     return true;
    // }

    // Or if a player has reached a certain chip count
    // for (const auto& player : players) {
    //     if (player->getChips() >= WINNING_CHIP_COUNT) {
    //         return true;
    //     }
    // }

    // If none of the ending conditions are met, the game continues
    return false;
}


#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void Game::clearTerminal() {
#ifdef _WIN32
    // For Windows
    system("cls");
#else
    // For Unix/Linux
    system("clear");
#endif
}

void Game::displayGameState() {
    clearTerminal();

    std::cout << "\n=== Poker Game State ===" << std::endl << std::endl;

    // Display community cards
    std::cout << "Community Cards: ";
    if (communityCards.empty()) {
        std::cout << "Not dealt yet";
    } else {
        for (const auto& card : communityCards) {
            std::cout << card.toString() << " ";
        }
    }
    std::cout << std::endl << std::endl;

    // Display pot
    std::cout << "Current Pot: $" << pot << std::endl << std::endl;

    // Display player information
    std::cout << std::left << std::setw(15) << "Player"
              << std::setw(35) << "Hole Cards"
              << std::setw(10) << "Chips"
              << std::setw(15) << "Current Bet"
              << "Status" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (const auto& player : players) {
        std::cout << std::left << std::setw(15) << ("Player " + std::to_string(getPlayerIndex(player)));

        // Display hole cards (or [Hidden] for computer players)
        if (player->isComputer()) {
            std::cout << std::setw(35) << "[Hidden]";
        } else {
            std::string cards = player->showHoleCards();
            std::cout << std::setw(35) << (cards.empty() ? "Not dealt" : cards);
        }

        std::cout << std::setw(10) << player->getChips()
                  << std::setw(15) << player->getCurrentBet()
                  << (player->isStillPlaying() ? "Active" : "Folded")
                  << std::endl;
    }

    std::cout << std::endl;
}