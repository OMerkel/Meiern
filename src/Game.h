#pragma once
#include <random>
#include <string>

#include "Announcement.h"
#include "CyclicList.h"
#include "Greeting.h"
#include "Interaction.h"
#include "Logger.h"
#include "Player.h"

class Game {
private:
    Logger& logger;
    // Get class name using RTTI
    const std::string className = typeid(*this).name();

    bool isRunning;
    CyclicList<Player> playerList;
    CyclicList<Player>::iterator currentPlayer;
    Announcement previousAnnouncement;

public:
    Game();
    void displayCurrentPlayers();
    void handoverDiceCup( CyclicList<Player>::iterator nextPlayer);
    std::string runLoop();
    void setup(std::string playerName = "");
};
