#include <gtest/gtest.h>
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
    EXPECT_EQ(buffer.str(), "TestPlayer announces value: 42\n");
}

TEST(PlayerTest, TrustPreviousAnnouncementOutputsCorrectly) {
    Player p("TestPlayer", 3);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    bool result = p.trustPreviousAnnouncement();
    std::cout.rdbuf(old);
    EXPECT_TRUE(result);
    EXPECT_EQ(buffer.str(), "TestPlayer trusts the previous announcement.\n");
}

TEST(PlayerTest, DoubtPreviousAnnouncementOutputsCorrectly) {
    Player p("TestPlayer", 3);
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    bool result = p.doubtPreviousAnnouncement();
    std::cout.rdbuf(old);
    EXPECT_TRUE(result);
    EXPECT_EQ(buffer.str(), "TestPlayer doubts the previous announcement!\n");
}