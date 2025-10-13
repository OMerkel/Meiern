/**
 * @file test_player.cpp
 * @brief Unit tests for the Player class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the Player class,
 * including constructor, getters, and other player-related methods.
 *
 * @author Oliver Merkel
 * 
 */
#include <gtest/gtest.h>
#include "Announcement.h"
#include "Player.h"

TEST(PlayerTest, ConstructorAndGetters) {
    Player p("TestPlayer", 5);
    EXPECT_EQ(p.getName(), "TestPlayer");
    EXPECT_EQ(p.getLives(), 5);
    EXPECT_EQ(p.getLivesAsString(), "5 lives");
}

TEST(PlayerTest, IncreaseLives) {
    Player p("TestPlayer", 1);
    p.increaseLives();
    EXPECT_EQ(p.getLives(), 2);
    p.increaseLives(3);
    EXPECT_EQ(p.getLives(), 5);
}

TEST(PlayerTest, DecreaseLives) {
    Player p("TestPlayer", 4);
    p.decreaseLives();
    EXPECT_EQ(p.getLives(), 3);
    p.decreaseLives(2);
    EXPECT_EQ(p.getLives(), 1);
    p.decreaseLives(2); // Should not go below 0
    EXPECT_EQ(p.getLives(), 0);
}

TEST(PlayerTest, GetLivesAsStringSingularPlural) {
    Player p("TestPlayer", 1);
    EXPECT_EQ(p.getLivesAsString(), "1 life");
    p.increaseLives();
    EXPECT_EQ(p.getLivesAsString(), "2 lives");
}

TEST(PlayerTest, AnnounceValueOutputsCorrectly) {
    Player p("TestPlayer", 3);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    p.announceValue(42);
    std::cout.rdbuf(old);
    EXPECT_NE(buffer.str().find("TestPlayer announces value: 42\n"), std::string::npos);
}

TEST(PlayerTest, TrustPreviousAnnouncementOutputsCorrectly) {
    Player p("TestPlayer", 3);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    bool result = p.trustPreviousAnnouncement();
    std::cout.rdbuf(old);
    EXPECT_TRUE(result);
    EXPECT_NE(buffer.str().find("TestPlayer trusts the previous announcement.\n"), std::string::npos);
}

TEST(PlayerTest, DoubtPreviousAnnouncementOutputsCorrectly) {
    Player p("TestPlayer", 3);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    bool result = p.doubtPreviousAnnouncement();
    std::cout.rdbuf(old);
    EXPECT_TRUE(result);
    EXPECT_NE(buffer.str().find("TestPlayer doubts the previous announcement!\n"), std::string::npos);
}

TEST(PlayerTest, PerformTurnWithDiceCupReturnsAnnouncedValue) {
    Player player("TestPlayer", 3);
    MeiernDiceCup cup;
    player.setDiceCup(&cup);
    Announcement result = player.performTurn(Announcement(0, 0));
    // The result should be the value announced (which is the combined dice value)
    EXPECT_GE(result.getEncodedValue(), 0); // Minimum possible sum for two dice
    EXPECT_LE(result.getEncodedValue(), 20); // Maximum possible sum for two dice
}

TEST(PlayerTest, PerformTurnWithoutDiceCupReturnsZero) {
    Player player("TestPlayer", 3);
    Announcement result = player.performTurn(Announcement(0, 0));
    EXPECT_EQ(result, Announcement( 0, 0));
}

TEST(PlayerTest, GetDiceCupReturnsAssignedPointer) {
    Player player("TestPlayer", 3);
    MeiernDiceCup diceCup;
    player.setDiceCup(&diceCup);
    EXPECT_EQ(player.getDiceCup(), &diceCup);
}

TEST(PlayerTest, GetDiceCupReturnsNullIfNotAssigned) {
    Player player("TestPlayer", 3);
    EXPECT_EQ(player.getDiceCup(), nullptr);
}
