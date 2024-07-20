A command-line based poker game implemented in C++.
## Features
- Texas Hold'em poker gameplay
- Support for multiple players (human and computer)
- Command-line interface
- Betting system
- Hand evaluation
## How to Play

1. The game will prompt you for the number of players.
2. Each player starts with a set amount of chips.
3. The game follows standard Texas Hold'em rules:
  - Two cards are dealt to each player
  - Betting round
  - Three community cards are dealt (the flop)
  - Betting round
  - One more community card is dealt (the turn)
  - Betting round
  - Final community card is dealt (the river)
  - Final betting round
  - Showdown (if more than one player remains)

4. Type your actions when prompted (fold, check, call, or bet).
5. The game continues until only one player has chips remaining.

## Project Structure
### Card Class:
- Holds Data related to cards.
- Has a constructor that creates a card with a suit and rank from a predetermined list.
### Deck Class:
- Manages a deck of 52 cards.
- Shuffles and deals cards to each player.
### Player Class:
- Handles logic related to player hand (hole cards) and betting.
- Keeps track of player bet value and total chips of each player.
### Computer Class:
- Derived from the Player Class, imitates decision-making of a player.
### Game Class:
- Holds logic related to the game loop and coordinates player decisions.
- Handles:
    - Betting
    - Folds
    - Checks/Calls
    - initiates hand evaluation
    - determines winner
### Main.cpp:
- Creates an instance of the game.
- Starts the game loop (`Game::play()`).
## License

:/
## Acknowledgments

- [CPP Reference](https://en.cppreference.com/) for C++ documentation
- [Poker Hand Rankings](https://www.cardplayer.com/rules-of-poker/hand-rankings) for hand evaluation rules