/**
 * @file Die.h
 * @brief Declaration of the Die class.
 *
 * @author Oliver Merkel
 * @date 2025-10-14
 */
#pragma once
#include <random>
#include <ctime>

class Die {
private:
    /// @brief Number of sides on the die.
    int sides_;
    int value_;
    static std::mt19937 rng;
public:
    Die(int sides = 6);
    int roll();
    int getValue() const;
};
