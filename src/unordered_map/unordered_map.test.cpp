#include "unordered_map.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

TEST(UnorderedMap, InsertUpdateAndGet) {
    UnorderedMap<int, int> m;
    EXPECT_EQ(m.size(), 0u);

    m.set(1, 100);
    const int* v1 = m.get(1);
    ASSERT_NE(v1, nullptr);
    EXPECT_EQ(*v1, 100);
    EXPECT_EQ(m.size(), 1u);
    m.set(1, 200);

    const int* v2 = m.get(1);
    ASSERT_NE(v2, nullptr);
    EXPECT_EQ(*v2, 200);
    EXPECT_EQ(m.size(), 1u);
}

TEST(UnorderedMap, BulkUniqueInsertAndPresence) {
    UnorderedMap<int, int> m;

    const int N = 500;
    for (int i = 0; i < N; ++i) {
        m.set(i, i * 3 + 7);
    }

    EXPECT_EQ(m.size(), static_cast<size_t>(N));
    for (int i = 0; i < N; ++i) {
        const int* p = m.get(i);
        ASSERT_NE(p, nullptr);
        EXPECT_EQ(*p, i * 3 + 7);
    }
}

struct BadHash {
    size_t operator()(int x) const { return static_cast<size_t>(x % 3); }
};

TEST(UnorderedMap, HandlesCollisions) {
    UnorderedMap<int, int, BadHash> m;

    const int M = 100;
    for (int i = 0; i < M; ++i) {
        m.set(i, i + 1000);
    }
    EXPECT_EQ(m.size(), static_cast<size_t>(M));

    for (int i = 0; i < M; ++i) {
        const int* p = m.get(i);
        ASSERT_NE(p, nullptr);
        EXPECT_EQ(*p, i + 1000);
    }
}

TEST(UnorderedMap, BucketsGrowOnManyInserts) {
    UnorderedMap<int, int> m;

    const int K = 2000;
    for (int i = 0; i < K; ++i) {
        m.set(i, i);
    }

    EXPECT_EQ(m.size(), static_cast<size_t>(K));
}

TEST(UnorderedMap, CopyConstructorCreatesIndependentCopy) {
    UnorderedMap<int, int> a;
    for (int i = 0; i < 50; ++i) {
        a.set(i, i * 2);
    }

    UnorderedMap<int, int> b = a;
    a.set(0, 999);
    a.set(1000, 7);
    EXPECT_EQ(b.size(), 50u);

    const int* bv0 = b.get(0);
    ASSERT_NE(bv0, nullptr);
    EXPECT_EQ(*bv0, 0);
    EXPECT_EQ(a.size(), 51u);
    EXPECT_EQ(b.get(1000), nullptr);
}

TEST(UnorderedMap, IterateBucketsContainsAllEntries) {
    UnorderedMap<int, int> m;
    for (int i = 1; i <= 100; ++i) {
        m.set(i, i + 5);
    }

    std::vector<std::pair<int, int>> found;
    for (const auto& bucket : m.buckets) {
        for (const auto& p : bucket) {
            found.push_back(p);
        }
    }
    EXPECT_EQ(found.size(), m.size());

    for (int i = 1; i <= 100; ++i) {
        auto it = std::find_if(found.begin(), found.end(),
                               [i](const std::pair<int, int>& p) { return p.first == i; });
        ASSERT_NE(it, found.end());
        EXPECT_EQ(it->second, i + 5);
    }
}

TEST(UnorderedMap, RepeatedInsertsKeepLastValueAndSizeStable) {
    UnorderedMap<int, int> m;

    m.set(42, 1);
    for (int i = 0; i < 100; ++i) {
        m.set(42, i);
    }
    EXPECT_EQ(m.size(), 1u);

    const int* v = m.get(42);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(*v, 99);
}

TEST(UnorderedMap, AssignmentCopiesAllEntries) {
    UnorderedMap<int, int> left;
    for (int i = 0; i < 30; ++i) {
        left.set(i, i * 3);
    }

    UnorderedMap<int, int> right;
    right = left;
    EXPECT_EQ(right.size(), left.size());

    for (int i = 0; i < 30; ++i) {
        const int* rv = right.get(i);
        ASSERT_NE(rv, nullptr);
        EXPECT_EQ(*rv, i * 3);
    }
}
