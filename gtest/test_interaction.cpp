/**
 * @file test_interaction.cpp
 * @brief Unit tests for the Interaction class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the Interaction class,
 * including ask_name, output, and other interaction-related methods.
 *
 * @author Oliver Merkel
 * 
 */
#include <gtest/gtest.h>
#include "Interaction.h"

// Test ask_name and output are not easily unit-testable due to I/O, but we can test output with stringstream
#include <sstream>
#include <iostream>

TEST(InteractionTest, OutputPrintsMessage) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    Interaction::output("Test message");
    std::cout.rdbuf(old);
    EXPECT_EQ(buffer.str(), "Test message\n");
}
