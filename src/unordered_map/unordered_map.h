#pragma once

#include <functional>
#include <utility>
#include <vector>

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
struct UnorderedMap {
    UnorderedMap();

   public:
    const Value* get(const Key& key) const;
    void set(const Key& key, Value value);
    void remove(const Key& key);

    size_t size() const;

    std::vector<std::vector<std::pair<Key, Value>>> buckets;

   private:
    Hash hash;
    KeyEqual equal;
    size_t size_;

    void refresh();
};

#include "unordered_map.tpp"
