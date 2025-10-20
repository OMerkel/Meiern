/**
 * @file Die.cpp
 * @brief Implementation of the Die class for simulating dice rolls.
 *
 * This file contains the implementation of the Die class, which represents
 * a die with a configurable number of sides.
 * It provides functionality to roll the die and retrieve its current value.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 */
#include "Die.h"


/**
 * @brief A static seeded random number generator for die rolls.
 */
std::mt19937 Die::rng(static_cast<unsigned int>(std::time(nullptr)));


/**
 * @brief Constructs a Die with a specified number of sides.
 * @param sides Number of sides on the die (default is 6).
 */
Die::Die(int sides) : sides_(sides) {
	roll();
}


/**
 * @brief Rolls the die to generate a new random value.
 * @return The new value of the die after rolling.
 */
int Die::roll() {
	std::uniform_int_distribution<int> dist(1, sides_);
	value_ = dist(rng);
	return value_;
}


/**
 * @brief Retrieves the current value of the die.
 * @return The current value of the die.
 */
int Die::getValue() const {
	return value_;
}
