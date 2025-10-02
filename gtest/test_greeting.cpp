/**
 * @file test_greeting.cpp
 * @brief Unit tests for the Greeting class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the Greeting class,
 * including different name inputs and expected greeting outputs.
 *
 * @author Oliver Merkel
 * 
 */
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
