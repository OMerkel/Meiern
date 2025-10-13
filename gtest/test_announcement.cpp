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

TEST(AnnouncementTest, Inequality) {
    Announcement a1(5, 2);
    Announcement a2(3, 4);
    EXPECT_NE(a1, a2);
}

TEST(AnnouncementTest, LessThanOperator) {
    Announcement a1(3, 1); // 31
    Announcement a2(3, 2); // 32
    EXPECT_LT(a1, a2);
}

TEST(AnnouncementTest, LessThanOrEqualOperator) {
    Announcement a1(4, 4); // 44
    Announcement a2(4, 4); // 44
    Announcement a3(5, 1); // 51
    EXPECT_LE(a1, a2);
    EXPECT_LE(a3, a1);
}

TEST(AnnouncementTest, GreaterThanOperator) {
    Announcement a1(5, 5); // 55
    Announcement a2(5, 4); // 54
    EXPECT_GT(a1, a2);
}

TEST(AnnouncementTest, GreaterThanOrEqualOperator) {
    Announcement a1(6, 6); // 66
    Announcement a2(6, 6); // 66
    Announcement a3(5, 3); // 53
    Announcement a4(2, 2); // 22
    EXPECT_GE(a1, a2);
    EXPECT_GE(a1, a3);
    EXPECT_GE(a4, a3);
}

TEST(AnnouncementTest, InvalidAnnouncement) {
    Announcement invalid(0, 0);
    EXPECT_EQ(invalid.getValue(), 0);
    EXPECT_EQ(invalid.getEncodedValue(), -1);
    Announcement valid(3, 4);
    EXPECT_LT(invalid, valid);
    EXPECT_LE(invalid, valid);
    EXPECT_NE(invalid, valid);
    EXPECT_FALSE(invalid > valid);
    EXPECT_FALSE(invalid >= valid);
}

TEST(AnnouncementTest, ComparisonWithInvalidAnnouncement) {
    Announcement invalid(0, 0);
    Announcement valid(2, 1); // Meier
    EXPECT_LT(invalid, valid);
    EXPECT_LE(invalid, valid);
    EXPECT_NE(invalid, valid);
    EXPECT_FALSE(invalid > valid);
    EXPECT_FALSE(invalid >= valid);
}

TEST(AnnouncementTest, ComparisonWithItself) {
    Announcement ann(4, 5);
    EXPECT_EQ(ann, ann);
    EXPECT_LE(ann, ann);
    EXPECT_GE(ann, ann);
    EXPECT_FALSE(ann < ann);
    EXPECT_FALSE(ann > ann);
}

TEST(AnnouncementTest, NextHigherReturnsInvalidForHighest) {
    Announcement highest(2, 1); // Meier is highest
    Announcement next = highest.nextHigher();
    EXPECT_EQ(next.getEncodedValue(), -1); // Invalid
    EXPECT_EQ(next.getValue(), 0);
}

TEST(AnnouncementTest, NextHigherReturnsValidForNormal) {
    Announcement ann(3, 1); // 31, lowest
    Announcement next = ann.nextHigher();
    EXPECT_EQ(next.getValue(), 32);
    EXPECT_GT(next.getEncodedValue(), ann.getEncodedValue());
}

TEST(AnnouncementTest, NextHigherReturnsInvalidForInvalidAnnouncement) {
    Announcement invalid(0, 0);
    Announcement next = invalid.nextHigher();
    EXPECT_EQ(next.getEncodedValue(), -1);
    EXPECT_EQ(next.getValue(), 0);
}

TEST(AnnouncementTest, AllHigherReturnsEmptyForHighest) {
    Announcement highest(2, 1); // Meier
    auto higher = highest.allHigher();
    EXPECT_TRUE(higher.empty());
}

TEST(AnnouncementTest, AllHigherReturnsEmptyForInvalidAnnouncement) {
    Announcement invalid(0, 0);
    auto higher = invalid.allHigher();
    EXPECT_TRUE(higher.empty());
}

TEST(AnnouncementTest, AllHigherReturnsAllHigherAnnouncements) {
    Announcement ann(3, 1); // 31, lowest
    auto higher = ann.allHigher();
    EXPECT_FALSE(higher.empty());
    EXPECT_EQ(higher.front().getValue(), 32);
    EXPECT_EQ(higher.back().getValue(), 21); // Meier
    EXPECT_EQ(higher.size(), 20);
}

TEST(AnnouncementTest, AllHigherReturnsNonEmpty) {
    Announcement a(3, 1); // Not the highest
    auto higher = a.allHigher();
    EXPECT_FALSE(higher.empty());
    // Optionally, check contents
    EXPECT_EQ(higher.front().getValue(), 32);
}

TEST(AnnouncementTest, ClearAnnouncements) {
    Announcement ann(3, 4);
    ann.clear();
    Announcement newAnn(5, 6); // Should reinitialize announcements
    EXPECT_EQ(newAnn.getValue(), 65);
}

TEST(AnnouncementTest, IndexOutOfBoundsAccess) {
    Announcement ann(3, 4);
    EXPECT_THROW(ann[100], std::out_of_range);
}

TEST(AnnouncementTest, ValidIndexAccess) {
    Announcement ann(3, 4);
    EXPECT_NO_THROW({
        int val = ann[0]; // Should be 31
        EXPECT_EQ(val, 31);
    });
}
