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