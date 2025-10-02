#pragma once
#include <random>
#include <ctime>

class Die {
private:
    int sides;
    int value;
    static std::mt19937 rng;
public:
    Die(int sides = 6);
    int roll();
    int getValue() const;
};
