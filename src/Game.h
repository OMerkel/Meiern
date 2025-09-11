#pragma once
#include <random>
#include <string>

#include "CyclicList.h"
#include "Greeting.h"
#include "Interaction.h"
#include "Player.h"

class Game {
private:
    bool isRunning;
    CyclicList<Player> playerList;
    CyclicList<Player>::iterator currentPlayer;

public:
	Game();
    void displayCurrentPlayers();
    void runLoop();
    void setup();
};
