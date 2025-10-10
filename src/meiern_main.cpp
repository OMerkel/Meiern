/**
 * @file meiern_main.cpp
 * @brief Entry point for the Meiern game application.
 *
 * This file contains the main function which initializes the Game object,
 * sets up the game, and starts the main game loop.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 */
#include "Game.h"


/**
 * @brief Main function to start the Meiern game.
 * @return Exit status code.
 */
int main() {
    Game game;
    game.setup();
    game.runLoop();
    return 0;
}
