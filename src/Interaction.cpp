/**
 * @file Interaction.cpp
 * @brief Implementation of the Interaction class for user input and output.
 *
 * This file contains the definitions for methods that handle user interaction,
 * including prompting for a name and displaying messages to the console.
 * The Interaction class provides static methods to facilitate communication
 * between the game and the player.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 */
#include "Interaction.h"
#include <iostream>
#include <string>


/**
 * @brief Prompts the user to enter their name.
 * @return The name entered by the user as a std::string.
 */
std::string Interaction::ask_name() {
    std::cout << "Enter your name: ";
    std::string name;
    std::getline(std::cin, name);
    return name;
}


/**
 * @brief Outputs a message to the console.
 * @param message The message to be displayed.
 */
void Interaction::output(const std::string& message) {
    std::cout << message << std::endl;
}
