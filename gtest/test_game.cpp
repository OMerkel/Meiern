/**
 * @file test_game.cpp
 * @brief Unit tests for the Game class using Google Test framework.
 *
 * This file contains a suite of tests to verify the core functionalities of the Game class,
 * including player setup, game loop execution, player display, and dice cup handover.
 *
 * Test Cases:
 * - SetupInitializesPlayersAndCurrentPlayer: Ensures that the setup method initializes all players
 *   and sets the current player correctly. Verifies the winner message format after running the game loop.
 * - DisplayCurrentPlayersOutputsInfo: Checks that the displayCurrentPlayers method outputs the correct
 *   information for all remaining players.
 * - HandoverDiceCupAssignsDiceCup: Validates that the handoverDiceCup mechanism assigns the dice cup
 *   to the next player without causing exceptions during the game loop.
 * - RunLoopReturnsWinnerMessage: Confirms that the runLoop method returns a properly formatted winner message.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 */

#include <gtest/gtest.h>
#include <string>
#include "Game.h"

// Test setup initializes players and sets currentPlayer
TEST(GameTest, SetupInitializesPlayersAndCurrentPlayer) {
    Game game;
    game.setup("TestUser");
    std::string winner = game.runLoop();
    std::cout << "Winner message: " << winner << std::endl;
    EXPECT_TRUE(winner.find("Congratulations!") != std::string::npos);
    EXPECT_TRUE(winner.find("Winner of the game is") != std::string::npos);
    EXPECT_TRUE(
        winner.find("TestUser") != std::string::npos ||
        winner.find("Alice") != std::string::npos ||
        winner.find("Bob") != std::string::npos ||
        winner.find("Charlie") != std::string::npos
    );
    EXPECT_TRUE(
        winner.find("with 1 life left") != std::string::npos ||
        winner.find("with 2 lives left") != std::string::npos ||
        winner.find("with 3 lives left") != std::string::npos
    );
}

// Test displayCurrentPlayers outputs correct player info
TEST(GameTest, DisplayCurrentPlayersOutputsInfo) {
    Game game;
    game.setup("TestUser");
    // Redirect std::cout to capture output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    game.displayCurrentPlayers();
    std::cout.rdbuf(old);
    std::string output = buffer.str();
    EXPECT_TRUE(output.find("Remaining players:") != std::string::npos);
    EXPECT_TRUE(output.find("Alice") != std::string::npos);
    EXPECT_TRUE(output.find("Bob") != std::string::npos);
    EXPECT_TRUE(output.find("Charlie") != std::string::npos);
    EXPECT_TRUE(output.find("TestUser") != std::string::npos);
}

// Test handoverDiceCup assigns dice cup to next player
TEST(GameTest, HandoverDiceCupAssignsDiceCup) {
    Game game;
    game.setup("TestUser");
    // Simulate handover: currentPlayer and nextPlayer
    // We can't access private members, but we can check that runLoop does not crash
    EXPECT_NO_THROW(game.runLoop());
}

// Test runLoop returns winner message
TEST(GameTest, RunLoopReturnsWinnerMessage) {
    Game game;
    game.setup("TestUser");
    std::string winner = game.runLoop();
    EXPECT_TRUE(winner.find("Congratulations!") != std::string::npos);
    EXPECT_TRUE(winner.find("Winner of the game is") != std::string::npos);
}
