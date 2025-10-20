/**
 * @file DiceCup.h
 * @brief Declaration of the DiceCup class.
 *
 * This file contains the definition of the DiceCup class,
 * which represents a collection of dice in the Meiern game.
 *
 * @author Oliver Merkel
 * @date 2025-10-14
 */
#pragma once
#include <vector>
#include <memory>
#include "Die.h"

class DiceCup {
private:
    std::vector<std::unique_ptr<Die>> dice;
public:
    DiceCup(int initialDice = 5);
    void shake();
    void addDie(int sides = 6);
    void removeDie(size_t index);
    size_t getDiceCount() const;
    const Die* getDie(size_t index) const;
};
