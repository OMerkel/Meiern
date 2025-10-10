/**
 * @file Announcement.cpp
 * @brief Implementation file for the Announcement class.
 *
 * This file contains the static member initialization for the announcements vector,
 * which stores announcement identifiers for the Announcement class.
 * The Announcement class represents a player's announcement in the game,
 * providing functionality to compare announcements, retrieve higher announcements,
 * and manage the list of possible announcements.
 * The announcements are encoded as two-digit integers, where the tens place
 * represents the higher die and the units place represents the lower die.
 * The class supports comparison operators to determine the ranking of announcements.
 * The announcements are initialized in a specific order, with "Meier" (21) being the highest.
 * The class also provides methods to get the next higher announcement and
 * to retrieve all higher announcements than the current one.
 * The class includes error handling for invalid announcements.
 * This implementation uses C++17 features and standard library components.
 * 
 * @author Oliver Merkel
 * @date 2025-10-10
 */
#include "Announcement.h"

/**
 * @brief Static member initialization for the announcements vector.
 */
std::vector<int> Announcement::announcements;
