cmake_minimum_required(VERSION 3.27)
project(Poker)

set(CMAKE_CXX_STANDARD 17)

add_executable(Poker main.cpp
        Card.cpp
        Card.h
        Deck.cpp
        Deck.h
        Player.cpp
        Player.h
        Computer.cpp
        Computer.h
        Game.cpp
        Game.h
)
