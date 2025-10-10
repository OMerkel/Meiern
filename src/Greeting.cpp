/**
 * @file Greeting.cpp
 * @brief Implementation of the Greeting class.
 *
 * This file contains the implementation of the Greeting class,
 * which provides functionality to generate a personalized greeting message.
 *
 * @author Oliver Merkel
 * @date 2025-10-10
 */
#include "Greeting.h"
#include <string>


/**
 * @brief Constructs a Greeting object with the specified name.
 * @param name The name to be used in the greeting message.
 */
Greeting::Greeting(const std::string& name) : name_(name) {}


/**
 * @brief Generates a greeting message.
 * @return A personalized greeting string.
 */
std::string Greeting::get_greeting() const {
    return "Hello, " + name_ + "!";
}
