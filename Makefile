CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRCS = main.cpp \
       Card.cpp \
       Deck.cpp \
       Player.cpp \
       Computer.cpp \
       Game.cpp

OBJS = $(SRCS:.cpp=.o)
EXEC = Poker

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
