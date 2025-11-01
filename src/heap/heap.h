#pragma once

#include <functional>
#include <optional>
#include <vector>

template <typename Value, typename Compare = std::less<Value>>
struct Heap {
   public:
    Heap();
    void push(Value value);
    std::optional<Value> pop();

    void debug(size_t start = 0);
    const std::vector<Value>& values();

   private:
    Compare compare;
    void bubble(size_t index);
    void sink(size_t index);
    std::vector<Value> _values;
};


#include "heap.tpp"