/**
 * @file test_interaction.cpp
 * @brief Unit tests for the Interaction class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the Interaction class,
 * including ask_name, output, and other interaction-related methods.
 *
 * Test ask_name and output are not easily unit-testable due to I/O,
 * but we can test output with stringstream redirection.
 *
 * @author Oliver Merkel
 * 
 */
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "Interaction.h"


// Inside the ask_name method,
// which handles user input and returns a string (e.g., the entered name).
// We'll simulate std::cin using stringstream for testing.
TEST(InteractionTest, AskNameReturnsInput) {
    std::istringstream input("Oliver\n");
    std::streambuf* old_in = std::cin.rdbuf(input.rdbuf());
    std::stringstream output;
    std::streambuf* old_out = std::cout.rdbuf(output.rdbuf());

    std::string name = Interaction::ask_name();

    std::cin.rdbuf(old_in);
    std::cout.rdbuf(old_out);

    EXPECT_EQ(name, "Oliver");
    EXPECT_NE(output.str().find("Enter your name"), std::string::npos);
}
