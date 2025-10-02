/**
 * @file test_announcement.cpp
 * @brief Unit tests for the Announcement class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the Announcement class,
 * including comparison operators and equality checks.
 * These tests verify Meier is highest, doubles outrank non-doubles,
 * normal combinations are ordered correctly, doubles are ordered,
 * and equality works for equivalent dice pairs.
 * 
 * @author Oliver Merkel
 * 
 */
#include "gtest/gtest.h"
#include "Announcement.h"

TEST(AnnouncementTest, ValueAndValueEncoding) {
    Announcement meier(1, 2);
    Announcement doubleSix(6, 6);
    Announcement normal(6, 5);
    EXPECT_EQ(meier.getValue(), 21);
    EXPECT_EQ(doubleSix.getValue(), 66);
    EXPECT_EQ(normal.getValue(), 65);
    EXPECT_EQ(meier.getEncodedValue(), 20);
    EXPECT_EQ(doubleSix.getEncodedValue(), 19);
    EXPECT_EQ(normal.getEncodedValue(), 13);
}

TEST(AnnouncementTest, MeierIsHighest) {
    Announcement meier(1, 2);
    Announcement doubleSix(6, 6);
    Announcement normal(6, 5);
    EXPECT_GT(meier, doubleSix);
    EXPECT_GT(meier, normal);
}

TEST(AnnouncementTest, DoublesAreHigherThanNonDoubles) {
    Announcement doubleFour(4, 4);
    Announcement normal(6, 5);
    EXPECT_GT(doubleFour, normal);
}

TEST(AnnouncementTest, NormalCombinationsOrder) {
    Announcement a31(3, 1);
    Announcement a32(3, 2);
    Announcement a41(4, 1);
    EXPECT_LT(a31, a32);
    EXPECT_LT(a32, a41);
}

TEST(AnnouncementTest, DoublesOrder) {
    Announcement doubleOne(1, 1);
    Announcement doubleSix(6, 6);
    EXPECT_LT(doubleOne, doubleSix);
}

TEST(AnnouncementTest, Equality) {
    Announcement a1(5, 2);
    Announcement a2(2, 5);
    EXPECT_EQ(a1, a2);
}
