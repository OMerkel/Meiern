/**
 * @file DiceCup.cpp
 * @brief Implementation of the DiceCup class, which manages a collection of dice.
 *
 * The DiceCup class provides functionality to hold, shake, add, and remove dice.
 * Each die is represented by a unique pointer to a Die object.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 */

#include "DiceCup.h"


/**
 * @class DiceCup
 * @brief Represents a cup containing multiple dice.
 *
 * Provides methods to shake all dice, add or remove dice, and access individual dice.
 */


 /**
 * @brief Constructs a DiceCup with a specified number of dice.
 * @param initialDice Number of dice to initialize in the cup.
 */
DiceCup::DiceCup(int initialDice) {
	for (int i = 0; i < initialDice; ++i) {
		dice.push_back(std::make_unique<Die>());
	}
}


/**
 * @brief Rolls all dice in the cup.
 */
void DiceCup::shake() {
	for (auto& die : dice) {
		die->roll();
	}
}


/**
 * @brief Adds a new die with a specified number of sides to the cup.
 * @param sides Number of sides for the new die.
 */
void DiceCup::addDie(int sides) {
	dice.push_back(std::make_unique<Die>(sides));
}


/**
 * @brief Removes a die from the cup at the specified index.
 * @param index Position of the die to remove.
 */
void DiceCup::removeDie(size_t index) {
	if (index < dice.size()) {
		dice.erase(dice.begin() + index);
	}
}


/**
 * @brief Returns the number of dice currently in the cup.
 * @return Number of dice.
 */
size_t DiceCup::getDiceCount() const {
	return dice.size();
}


/**
 * @brief Retrieves a constant pointer to the die at the specified index.
 * @param index Position of the die to retrieve.
 * @return Pointer to the Die object, or nullptr if index is out of range.
 */
const Die* DiceCup::getDie(size_t index) const {
	if (index < dice.size()) {
		return dice[index].get();
	}
	return nullptr;
}
