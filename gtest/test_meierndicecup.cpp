/**
 * @file test_meierndicecup.cpp
 * @brief Unit tests for the MeiernDiceCup class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the MeiernDiceCup class,
 * including dice count, die values, and shake behavior.
 *
 * @author Oliver Merkel
 * 
 */
#include "gtest/gtest.h"
#include "MeiernDiceCup.h"

TEST(MeiernDiceCupTest, AlwaysHasTwoSixSidedDice) {
    MeiernDiceCup cup;
    EXPECT_EQ(cup.getDiceCount(), 2);
    for (size_t i = 0; i < 2; ++i) {
        const Die* die = cup.getDie(i);
        EXPECT_NE(die, nullptr);
        EXPECT_GE(die->getValue(), 1);
        EXPECT_LE(die->getValue(), 6);
    }
}

TEST(MeiernDiceCupTest, ShakeRollsBothDice) {
    MeiernDiceCup cup;
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
