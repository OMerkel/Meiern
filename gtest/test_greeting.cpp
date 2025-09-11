#include <gtest/gtest.h>
#include "Greeting.h"

TEST(GreetingTest, ReturnsCorrectGreeting) {
    Greeting g("Alice");
    EXPECT_EQ(g.get_greeting(), "Hello, Alice!");
}

TEST(GreetingTest, EmptyName) {
    Greeting g("");
    EXPECT_EQ(g.get_greeting(), "Hello, !");
}
