/**
 * @file MeiernDiceCup.cpp
 * @brief Implementation of the MeiernDiceCup class for the Meiern dice game.
 *
 * This file contains the constructor and member functions for the MeiernDiceCup class,
 * which represents a specialized dice cup used in the Meiern game. The cup is initialized
 * with two six-sided dice and provides functionality to retrieve their values as an Announcement.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 */
#include "MeiernDiceCup.h"


/**
 * @brief Constructor for the MeiernDiceCup class.
 * Initializes the cup with two six-sided dice.
 */
MeiernDiceCup::MeiernDiceCup() : DiceCup(0) {
	addDie(6);
	addDie(6);
}


/**
 * @brief Retrieves the current dice values as an Announcement.
 * @return An Announcement representing the values of the two dice.
 */
Announcement MeiernDiceCup::getDiceValue() const {
    if (getDiceCount() != 2) return Announcement( 0, 0); // Error case
    int die1 = getDie(0)->getValue();
    int die2 = getDie(1)->getValue();
    return Announcement(die1, die2);
}
