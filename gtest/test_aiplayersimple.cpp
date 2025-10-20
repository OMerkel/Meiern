/**
 * @file test_aiplayersimple.cpp
 * @brief Unit tests for the AIPlayerSimple class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the AIPlayerSimple class,
 * including constructor, getters, and other player-related methods.
 *
 * @author Oliver Merkel
 * 
 */
#include <gtest/gtest.h>
#include "Announcement.h"
#include "AIPlayerSimple.h"

TEST(AIPlayerSimpleTest, ConstructorAndGetters) {
    AIPlayerSimple p("TestPlayer", 5);
    EXPECT_EQ(p.getName(), "TestPlayer (AI)");
    EXPECT_EQ(p.getLives(), 5);
    EXPECT_EQ(p.getLivesAsString(), "5 lives");
}

TEST(AIPlayerSimpleTest, IncreaseLives) {
    AIPlayerSimple p("TestPlayer", 1);
    p.increaseLives();
    EXPECT_EQ(p.getLives(), 2);
    p.increaseLives(3);
    EXPECT_EQ(p.getLives(), 5);
}

TEST(AIPlayerSimpleTest, DecreaseLives) {
    AIPlayerSimple p("TestPlayer", 4);
    p.decreaseLives();
    EXPECT_EQ(p.getLives(), 3);
    p.decreaseLives(2);
    EXPECT_EQ(p.getLives(), 1);
    p.decreaseLives(2); // Should not go below 0
    EXPECT_EQ(p.getLives(), 0);
}

TEST(AIPlayerSimpleTest, GetLivesAsStringSingularPlural) {
    AIPlayerSimple p("TestPlayer", 1);
    EXPECT_EQ(p.getLivesAsString(), "1 life");
    p.increaseLives();
    EXPECT_EQ(p.getLivesAsString(), "2 lives");
}

TEST(AIPlayerSimpleTest, AnnounceValueOutputsCorrectly) {
    std::string expected = "[INFO] [TestPlayer (AI)] announces value: 42\n";
    AIPlayerSimple p("TestPlayer", 3);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    Announcement ann(4, 2); // Encoded value 42
    p.announceValue(ann);
    std::cout.rdbuf(old);
    EXPECT_NE(buffer.str().find(expected), std::string::npos);
}

TEST(AIPlayerSimpleTest, TrustPreviousAnnouncementOutputsCorrectly) {
    std::string expected = "[INFO] [TestPlayer (AI)] trusts the previous announcement.\n";
    AIPlayerSimple p("TestPlayer", 3);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    bool result = p.trustPreviousAnnouncement();
    std::cout.rdbuf(old);
    EXPECT_TRUE(result);
    std::string actual = buffer.str();
    std::cout << "Actual output: " << actual << std::endl;
    EXPECT_NE(actual.find(expected), std::string::npos);
}

TEST(AIPlayerSimpleTest, DoubtPreviousAnnouncementOutputsCorrectly) {
    std::string expected = "[INFO] [TestPlayer (AI)] doubts the previous announcement.\n";
    AIPlayerSimple p("TestPlayer", 3);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    bool result = p.doubtPreviousAnnouncement();
    std::cout.rdbuf(old);
    EXPECT_TRUE(result);
    EXPECT_NE(buffer.str().find(expected), std::string::npos);
}

TEST(AIPlayerSimpleTest, PerformTurnWithDiceCupReturnsAnnouncedValue) {
    AIPlayerSimple player("TestPlayer", 3);
    MeiernDiceCup cup;
    player.setDiceCup(&cup);
    Announcement result = player.performTurn(Announcement(0, 0));
    // The result should be the value announced (which is the combined dice value)
    EXPECT_GE(result.getEncodedValue(), 0); // Minimum possible sum for two dice
    EXPECT_LE(result.getEncodedValue(), 20); // Maximum possible sum for two dice
}

TEST(AIPlayerSimpleTest, PerformTurnWithoutDiceCupReturnsZero) {
    AIPlayerSimple player("TestPlayer", 3);
    Announcement result = player.performTurn(Announcement(0, 0));
    EXPECT_EQ(result, Announcement(0, 0));
}

TEST(AIPlayerSimpleTest, GetDiceCupReturnsAssignedPointer) {
    AIPlayerSimple player("TestPlayer", 3);
    MeiernDiceCup diceCup;
    player.setDiceCup(&diceCup);
    EXPECT_EQ(player.getDiceCup(), &diceCup);
}

TEST(AIPlayerSimpleTest, GetDiceCupReturnsNullIfNotAssigned) {
    AIPlayerSimple player("TestPlayer", 3);
    EXPECT_EQ(player.getDiceCup(), nullptr);
}

TEST(AIPlayerSimpleTest, PerformTurnChoosesHigherAnnouncement) {
    AIPlayerSimple player("TestPlayer", 3);
    MeiernDiceCup cup;
    player.setDiceCup(&cup);
    Announcement previousAnnouncement(3, 4); // Encoded value 34
    Announcement result = player.performTurn(previousAnnouncement);
    EXPECT_GT(result.getEncodedValue(), previousAnnouncement.getEncodedValue());
}

TEST(AIPlayerSimpleTest, PerformTurnHandlesAnnouncingMeier) {
    AIPlayerSimple player("TestPlayer", 3);
    MeiernDiceCup cup;
    player.setDiceCup(&cup);
    Announcement meierAnnouncement(2, 1); // Encoded value 21
    Announcement previousAnnouncement(6, 6);
    Announcement result = player.performTurn(previousAnnouncement);
    EXPECT_EQ(result, meierAnnouncement);
}

TEST(AIPlayerSimpleTest, PerformTurnHandlesNoHigherAnnouncement) {
    AIPlayerSimple player("TestPlayer", 3);
    MeiernDiceCup cup;
    player.setDiceCup(&cup);
    Announcement previousAnnouncement(2, 1); // Encoded value 21
    Announcement result = player.performTurn(previousAnnouncement);
    EXPECT_EQ(result, Announcement(0, 0)); // Error case
}
