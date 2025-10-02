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
