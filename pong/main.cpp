// main.cpp
// Creates the Game object and plays the game
// Patrick Zwierzynski

#include "GameObjects/Pong.hpp"

int main(int argc, const char * argv[]) {
    Pong game (2000,1000,0);
    game.play();
    return 0;
}
