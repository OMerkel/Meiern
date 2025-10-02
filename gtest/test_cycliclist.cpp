/**
 * @file test_cycliclist.cpp
 * @brief Unit tests for the CyclicList class using Google Test framework.
 *
 * This file contains tests to verify the functionality of the CyclicList class,
 * including push_back, size, and cyclic behavior.
 *
 * @author Oliver Merkel
 * 
 */
#include <gtest/gtest.h>
#include <string>
#include "CyclicList.h"

TEST(CyclicListTest, PushBackAndSize) {
    CyclicList<int> cl;
    EXPECT_TRUE(cl.empty());
    cl.push_back(1);
    cl.push_back(2);
    cl.push_back(3);
    EXPECT_EQ(cl.size(), 3);
}

TEST(CyclicListTest, CyclicNext) {
    CyclicList<int> cl;
    cl.push_back(10);
    cl.push_back(20);
    cl.push_back(30);
    auto it = cl.begin();
    EXPECT_EQ(*it, 10);
    it = cl.next(it);
    EXPECT_EQ(*it, 20);
    it = cl.next(it);
    EXPECT_EQ(*it, 30);
    it = cl.next(it);
    EXPECT_EQ(*it, 10); // Cyclic
}

TEST(CyclicListTest, CyclicPrev) {
    CyclicList<int> cl;
    cl.push_back(100);
    cl.push_back(200);
    cl.push_back(300);
    auto it = cl.begin();
    EXPECT_EQ(*it, 100);
    it = cl.prev(it);
    EXPECT_EQ(*it, 300); // Cyclic
    it = cl.prev(it);
    EXPECT_EQ(*it, 200);
    it = cl.prev(it);
    EXPECT_EQ(*it, 100);
}

TEST(CyclicListTest, EmptyList) {
    CyclicList<int> cl;
    EXPECT_EQ(cl.next(cl.begin()), cl.end());
    EXPECT_EQ(cl.prev(cl.begin()), cl.end());
}

TEST(CyclicListTest, StringType) {
    CyclicList<std::string> cl;
    cl.push_back("a");
    cl.push_back("b");
    auto it = cl.begin();
    EXPECT_EQ(*it, "a");
    it = cl.next(it);
    EXPECT_EQ(*it, "b");
    it = cl.next(it);
    EXPECT_EQ(*it, "a");
}
