#include "heap.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <random>

TEST(Heap, PushPopSingle) {
    Heap<int> h;
    h.push(42);

    ASSERT_EQ(h.values().size(), 1);
    EXPECT_EQ(h.pop().value(), 42);
    EXPECT_TRUE(h.values().empty());
}

TEST(Heap, PopsInAscendingOrder) {
    Heap<int> h;
    std::vector<int> input = {5, 3, 8, 1, 4, 7, 2, 6, 0, 9};
    for (int v : input) {
        h.push(v);
    }

    std::vector<int> out;
    while (!h.values().empty()) {
        out.push_back(h.pop().value());
    }
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(out, expected);
}

TEST(Heap, HandlesDuplicatesAndNegatives) {
    Heap<int> h;
    std::vector<int> input = {5, -1, 5, -1, 0};
    for (int v : input) {
        h.push(v);
    }

    std::vector<int> out;
    while (!h.values().empty()) {
        out.push_back(h.pop().value());
    }
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(out, expected);
}

TEST(Heap, LargeRandom) {
    Heap<int> h;
    const int N = 1000;
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(-10000, 10000);
    std::vector<int> input;
    input.reserve(N);
    for (int i = 0; i < N; ++i) {
        int v = dist(rng);
        input.push_back(v);
        h.push(v);
    }

    std::vector<int> out;
    out.reserve(N);
    while (!h.values().empty()) {
        out.push_back(h.pop().value());
    }
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(out, expected);
}

TEST(HeapMax, PushPopSingle) {
    Heap<int, std::greater<int>> h;
    h.push(42);

    ASSERT_EQ(h.values().size(), 1);
    EXPECT_EQ(*h.pop(), 42);
    EXPECT_TRUE(h.values().empty());
}

TEST(HeapMax, PopsInDescendingOrder) {
    Heap<int, std::greater<int>> h;
    std::vector<int> input = {5, 3, 8, 1, 4, 7, 2, 6, 0, 9};
    for (int v : input) {
        h.push(v);
    }

    std::vector<int> out;
    while (!h.values().empty()) {
        out.push_back(h.pop().value());
    }
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end(), std::greater<int>());

    EXPECT_EQ(out, expected);
}

TEST(HeapMax, HandlesDuplicatesAndNegatives) {
    Heap<int, std::greater<int>> h;
    std::vector<int> input = {5, -1, 5, -1, 0};
    for (int v : input) {
        h.push(v);
    }

    std::vector<int> out;
    while (!h.values().empty()) {
        out.push_back(h.pop().value());
    }
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end(), std::greater<int>());

    EXPECT_EQ(out, expected);
}

TEST(HeapMax, LargeRandom) {
    Heap<int, std::greater<int>> h;
    const int N = 1000;
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(-10000, 10000);
    std::vector<int> input;
    input.reserve(N);
    for (int i = 0; i < N; ++i) {
        int v = dist(rng);
        input.push_back(v);
        h.push(v);
    }

    std::vector<int> out;
    out.reserve(N);
    while (!h.values().empty()) {
        out.push_back(h.pop().value());
    }
    std::vector<int> expected = input;
    std::sort(expected.begin(), expected.end(), std::greater<int>());

    EXPECT_EQ(out, expected);
}

TEST(Heap, PopOnEmptyReturnsNullopt) {
    Heap<int> h;
    auto v = h.pop();

    EXPECT_FALSE(v.has_value());
}