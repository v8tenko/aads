#pragma once

#include <algorithm>

#include "unordered_map.h"

template <typename Key, typename Value, typename Hash, typename KeyEqual>
UnorderedMap<Key, Value, Hash, KeyEqual>::UnorderedMap()
    : buckets(16), hash(Hash()), equal(KeyEqual()), size_(0) {}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void UnorderedMap<Key, Value, Hash, KeyEqual>::set(const Key& key, Value value) {
    size_t hashed = hash(key);
    size_t index = hashed % buckets.size();

    auto& localBucket = buckets[index];
    auto previousValueIterator = std::find_if(
        localBucket.begin(), localBucket.end(),
        [&key, this](std::pair<Key, Value>& entry) { return equal(entry.first, key); });

    if (previousValueIterator == localBucket.end()) {
        localBucket.push_back({key, std::move(value)});
        size_++;
    } else {
        previousValueIterator->second = value;
    }

    float localFactor = static_cast<float>(size_) / buckets.size();

    if (localFactor > 0.75) {
        refresh();
    }
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void UnorderedMap<Key, Value, Hash, KeyEqual>::refresh() {
    size_t nextBucketsSize = buckets.size() * 2;
    std::vector<std::vector<std::pair<Key, Value>>> nextBuckets(nextBucketsSize);

    for (const auto& localBucket : buckets) {
        for (const auto& pair : localBucket) {
            size_t hashed = hash(pair.first);
            size_t nextIndex = hashed % nextBucketsSize;

            nextBuckets[nextIndex].push_back(pair);
        }
    }

    buckets = nextBuckets;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
const Value* UnorderedMap<Key, Value, Hash, KeyEqual>::get(const Key& key) const {
    size_t hashed = hash(key);
    size_t index = hashed % buckets.size();

    auto& localBucket = buckets[index];
    auto valueIterator =
        std::find_if(localBucket.begin(), localBucket.end(),
                     [&key, this](const std::pair<Key, Value>& entry) { return equal(entry.first, key); });

    return valueIterator == localBucket.end() ? nullptr : &valueIterator->second;
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
void UnorderedMap<Key, Value, Hash, KeyEqual>::remove(const Key& key) {
    size_t hashed = hash(key);
    size_t index = hashed % buckets.size();

    auto& localBucket = buckets[index];

    auto valueIterator =
        std::find_if(localBucket.begin(), localBucket.end(),
                     [&key, this](const std::pair<Key, Value>& entry) { return equal(entry.first, key); });
    
    if (valueIterator != localBucket.end()) {
        localBucket.erase(valueIterator);
        size_--;
    }
}

template <typename Key, typename Value, typename Hash, typename KeyEqual>
size_t UnorderedMap<Key, Value, Hash, KeyEqual>::size() const {
    return size_;
}
