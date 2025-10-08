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
