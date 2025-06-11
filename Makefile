# C++ SFML Ball Game Makefile
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -I/opt/homebrew/opt/sfml@2/include
LIBS = -L/opt/homebrew/opt/sfml@2/lib -lsfml-graphics -lsfml-window -lsfml-system
TARGET = ball_game
SOURCE = main.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean debug
