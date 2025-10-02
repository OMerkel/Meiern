/**
 * @file test_die.cpp
 * @brief Unit tests for the Die class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the Die class,
 * including default construction, custom number of sides, and the roll behavior.
 *
 * @author Oliver Merkel
 * 
 */
#include <gtest/gtest.h>
#include "Die.h"

TEST(DieTest, DefaultConstructorRollsRandomValue) {
    Die die;
    int value = die.getValue();
    EXPECT_GE(value, 1);
    EXPECT_LE(value, 6);
}

TEST(DieTest, CustomSidesRollsWithinRange) {
    Die die(20);
    int value = die.getValue();
    EXPECT_GE(value, 1);
    EXPECT_LE(value, 20);
}

TEST(DieTest, RollChangesValue) {
    Die die;
    int initial = die.getValue();
    bool changed = false;
    for (int i = 0; i < 10; ++i) {
        int newValue = die.roll();
        if (newValue != initial) {
            changed = true;
            break;
        }
    }
    EXPECT_TRUE(changed);
}
