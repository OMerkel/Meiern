/**
 * @file Game.h
 * @brief Declaration of the Game class.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 */
#pragma once
#include <random>
#include <string>

#include "AbstractPlayer.h"
#include "AIPlayerSimple.h"
#include "Announcement.h"
#include "CyclicList.h"
#include "Greeting.h"
#include "Interaction.h"
#include "Logger.h"

class Game {
private:
    Logger& logger;
    const std::string className = typeid(*this).name();

    bool isRunning;
    CyclicList<std::unique_ptr<AbstractPlayer>> playerList;
    CyclicList<std::unique_ptr<AbstractPlayer>>::iterator currentPlayer;
    Announcement previousAnnouncement;

public:
    Game();
    void displayCurrentPlayers();
    void handoverDiceCup( CyclicList<std::unique_ptr<AbstractPlayer>>::iterator nextPlayer);
    std::string runLoop();
    void setup(std::string playerName = "");
};
