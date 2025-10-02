/*
 * @file test_dicecup.cpp
 * @brief Unit tests for the DiceCup class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the DiceCup class,
 * including default construction, custom initial dice count, and dice rolling.
 *
 * @author Oliver Merkel
 *
 */
#include <gtest/gtest.h>
#include "DiceCup.h"

TEST(DiceCupTest, DefaultConstructorHasFiveDice) {
    DiceCup cup;
    EXPECT_EQ(cup.getDiceCount(), 5);
    for (size_t i = 0; i < cup.getDiceCount(); ++i) {
        const Die* die = cup.getDie(i);
        EXPECT_NE(die, nullptr);
        EXPECT_GE(die->getValue(), 1);
        EXPECT_LE(die->getValue(), 6);
    }
}

TEST(DiceCupTest, CustomInitialDiceCount) {
    DiceCup cup(3);
    EXPECT_EQ(cup.getDiceCount(), 3);
}

TEST(DiceCupTest, AddDieIncreasesCount) {
    DiceCup cup(2);
    cup.addDie();
    EXPECT_EQ(cup.getDiceCount(), 3);
}

TEST(DiceCupTest, RemoveDieDecreasesCount) {
    DiceCup cup(3);
    cup.removeDie(1);
    EXPECT_EQ(cup.getDiceCount(), 2);
}

TEST(DiceCupTest, ShakeRollsAllDice) {
    DiceCup cup(2);
    int v1 = cup.getDie(0)->getValue();
    int v2 = cup.getDie(1)->getValue();
    bool changed = false;
    for (int i = 0; i < 10; ++i) {
        cup.shake();
        if (cup.getDie(0)->getValue() != v1 || cup.getDie(1)->getValue() != v2) {
            changed = true;
            break;
        }
    }
    EXPECT_TRUE(changed);
}

TEST(DiceCupTest, GetDieReturnsNullptrForInvalidIndex) {
    DiceCup cup(2);
    EXPECT_EQ(cup.getDie(2), nullptr); // index out of range
    EXPECT_EQ(cup.getDie(100), nullptr); // index way out of range
}

TEST(DiceCupTest, GetDieReturnsValidPointerForValidIndex) {
    DiceCup cup(2);
    EXPECT_NE(cup.getDie(0), nullptr);
    EXPECT_NE(cup.getDie(1), nullptr);
}
